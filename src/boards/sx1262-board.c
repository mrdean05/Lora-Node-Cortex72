#include <stdlib.h>
#include "board.h"
#include "sx126x-board.h"
#include  "delay.h"
#include "sx126x.h"
#include "../include/board-config.h"
#include "../include/ioexpander.h"

//#define USE_RADIO_DEBUG

#if defined( USE_RADIO_DEBUG )

/*!
* \brief Writes new Tx debug pin state
*
* \param [IN] state Debug pin state
*/
static void SX126xDbgPinTxWrite ( uint8_t state);

/*!
* \brief Writes new Rx debug pin state
* 
* \param [IN] state Debug pin state
*/
static void SX126xDbgPinRxWrite( uint8_t state);

#endif

/*!
* \brief Holds the internal operating mode of the radio\
*/
static RadioOperatingModes_t OperatingMode;

/*!
* \brief SX1262 Lora Module enable gpio pin  
*/
Gpio_t LoraEnable;

/*!
* \brief Debug GPIO TX and RX pin objects 
*/
#if defined ( USE_RADIO_DEBUG )
Gpio_t DbgPinTx;
Gpio_t DbgPinRx;
#endif

void SX126xIoInit( void )
{    
    io_init();
    printf("Setting LORA EN HIGH\n");
    GpioInit(&LoraEnable, LORA_EN, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
    GpioInit(&SX126x.BUSY, LORA_BUSY, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&SX126x.DIO1, LORA_IO1, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
}

void SX126xIoDeInit( void )
{    
    GpioInit(&LoraEnable, LORA_EN, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
    GpioInit(&SX126x.BUSY, LORA_BUSY, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&SX126x.DIO1, LORA_IO1, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
}

void SX126xIoDbgInit( void )
{
#if defined ( USE_RADIO_DEBUG )  
    printf("I'm called\n");
    GpioInit(&DbgPinRx, LORA_RXEN, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    GpioInit(&DbgPinTx, LORA_TXEN, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
#endif
}

void SX126xIoIrqInit( DioIrqHandler dioIrq )
{
    GpioSetInterrupt(&SX126x.DIO1, IRQ_RISING_EDGE, IRQ_HIGH_PRIORITY, dioIrq);
}

void SX126xIoTcxoInit( void )
{
    // No TCXO component available on this board design.
}

uint32_t SX126xGetBoardTcxoWakeupTime( void )
{
    return BOARD_TCXO_WAKEUP_TIME;
}

void SX126xIoRfSwitchInit( void )
{
    
}
RadioOperatingModes_t SX126xGetOperatingMode( void )
{
    return OperatingMode;
}

void SX126xSetOperatingMode( RadioOperatingModes_t mode )
{
    OperatingMode = mode;

#if defined ( USE_RADIO_DEBUG )
    switch (mode)
    {
        case MODE_TX:
            SX126xDbgPinTxWrite (1);
            SX126xDbgPinRxWrite (0);
            break;
        case MODE_RX:
        case MODE_RX_DC:
            SX126xDbgPinRxWrite (1);
            SX126xDbgPinTxWrite (0);
            break;
        default:
            SX126xDbgPinRxWrite (0);
            SX126xDbgPinTxWrite (0);
            break;        
    }
#endif
}

void SX126xReset( void )
{
    DelayMs( 10 );
    GpioInit(&SX126x.Reset, LORA_RST, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0);
    DelayMs ( 20 );
    GpioInit(&SX126x.Reset, LORA_RST, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
    DelayMs( 10 );
}

void SX126xWaitOnBusy( void )
{
    while( GpioRead( &SX126x.BUSY ) == 1 );
}

void SX126xWakeup( void )
{
    CRITICAL_SECTION_BEGIN( );

    SpiInOut( &SX126x.Spi, RADIO_GET_STATUS );
    SpiInOut( &SX126x.Spi, 0x00 );
    set_spi_cs_high();

    // Wait for chip to be ready.
    SX126xWaitOnBusy( );

    // Update operating mode context variable
    SX126xSetOperatingMode( MODE_STDBY_RC );
    CRITICAL_SECTION_END( );  
}

void SX126xWriteCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    SpiInOut( &SX126x.Spi, ( uint8_t )command );

    for( uint16_t i = 0; i < size; i++ )
    {
        SpiInOut( &SX126x.Spi, buffer[i] );
    }

    set_spi_cs_high();

    if( command != RADIO_SET_SLEEP )
    {
        SX126xWaitOnBusy( );
    }    
}

uint8_t SX126xReadCommand( RadioCommands_t command, uint8_t *buffer, uint16_t size )
{
    uint8_t status = 0;

    SX126xCheckDeviceReady( );

    SpiInOut( &SX126x.Spi, ( uint8_t )command );
    status = SpiInOut( &SX126x.Spi, 0x00 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( &SX126x.Spi, 0 );
    } 

    set_spi_cs_high();

    SX126xWaitOnBusy( );
    return status;
}

void SX126xWriteRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    SpiInOut( &SX126x.Spi, RADIO_WRITE_REGISTER );
    SpiInOut( &SX126x.Spi, ( address & 0xFF00 ) >> 8 );
    SpiInOut( &SX126x.Spi, address & 0x00FF );
    
    for( uint16_t i = 0; i < size; i++ )
    {
        SpiInOut( &SX126x.Spi, buffer[i] );
    }

    set_spi_cs_high();

    SX126xWaitOnBusy( );
}

void SX126xWriteRegister( uint16_t address, uint8_t value )
{
    SX126xWriteRegisters( address, &value, 1 );
}

void SX126xReadRegisters( uint16_t address, uint8_t *buffer, uint16_t size )
{
    SX126xCheckDeviceReady( );

    SpiInOut( &SX126x.Spi, RADIO_READ_REGISTER );
    SpiInOut( &SX126x.Spi, ( address & 0xFF00 ) >> 8 );
    SpiInOut( &SX126x.Spi, address & 0x00FF );
    SpiInOut( &SX126x.Spi, 0 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( &SX126x.Spi, 0 );
    }

    set_spi_cs_high();

    SX126xWaitOnBusy( );
}

uint8_t SX126xReadRegister( uint16_t address )
{
    uint8_t data;
    SX126xReadRegisters( address, &data, 1 );
    return data;
}

void SX126xWriteBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    SpiInOut( &SX126x.Spi, RADIO_WRITE_BUFFER );
    SpiInOut( &SX126x.Spi, offset );
    for( uint16_t i = 0; i < size; i++ )
    {
        SpiInOut( &SX126x.Spi, buffer[i] );
    }
    set_spi_cs_high();
    SX126xWaitOnBusy( );
}

void SX126xReadBuffer( uint8_t offset, uint8_t *buffer, uint8_t size )
{
    SX126xCheckDeviceReady( );

    SpiInOut( &SX126x.Spi, RADIO_READ_BUFFER );
    SpiInOut( &SX126x.Spi, offset );
    SpiInOut( &SX126x.Spi, 0 );
    for( uint16_t i = 0; i < size; i++ )
    {
        buffer[i] = SpiInOut( &SX126x.Spi, 0 );
    }
    set_spi_cs_high();

    SX126xWaitOnBusy( );
}


void SX126xSetRfTxPower( int8_t power )
{
    SX126xSetTxParams( power, RADIO_RAMP_40_US );
}

uint8_t SX126xGetDeviceId( void )
{
    return SX1262;   
}

void SX126xAntSwOn( void )
{
}

void SX126xAntSwOff( void )
{
}

uint32_t SX126xGetDio1PinState( void )
{
    return GpioRead( &SX126x.DIO1 );
}

bool SX126xCheckRfFrequency( uint32_t frequency )
{
    // Implement check. Currently all frequencies are supported
    return true;
}

#if defined( USE_RADIO_DEBUG )
static void SX126xDbgPinTxWrite( uint8_t state )
{
    GpioWrite( &DbgPinTx, state );
}

static void SX126xDbgPinRxWrite( uint8_t state )
{
    GpioWrite( &DbgPinRx, state );
}
#endif