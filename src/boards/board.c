#include <stdint.h>
#include <string.h>

#include "board.h"


void BoardInitMcu( void )
{
}

void BoardInitPeriph( void )
{
}


void BoardLowPowerHandler( void )
{
}

uint8_t BoardGetBatteryLevel( void )
{
    return 0;
}

uint32_t BoardGetRandomSeed( void )
{
    uint8_t id[8];

    BoardGetUniqueId(id);

    return (id[3] << 24) | (id[2] << 16) | (id[1] << 1) | id[0];
}

void BoardGetUniqueId( uint8_t *id )
{
    //eui-70b3d57ed005a000
    uint8_t *board_id = "eui-70b3d57ed005ab62";
    memcpy(id, board_id, 8);
}

void BoardResetMcu( void )
{
}

void BoardCriticalSectionBegin(uint32_t *mask)
{

}

void BoardCriticalSectionEnd( uint32_t *mask )
{
    
}


