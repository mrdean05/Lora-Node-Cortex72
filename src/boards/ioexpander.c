#include "../include/ioexpander.h"


/* The I2C address of the PCAL6416A */
#define PCAL6416A_ADDRESS 0x21 

/* File descriptor for the PCAL6416A */
int pcal6416a_fd; 

/* Open and initialize the I2C bus 1 */
static void pcal6416a_init() {
    pcal6416a_fd = open("/dev/i2c-1", O_RDWR); 
    ioctl(pcal6416a_fd, I2C_SLAVE, PCAL6416A_ADDRESS); 
}

/* Write and reading into the register of PCAL6416A I/O expander */
static void pcal6416a_write_register(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    write(pcal6416a_fd, data, 2);
}

static uint8_t pcal6416a_read_register(uint8_t reg) {
    write(pcal6416a_fd, &reg, 1);
    uint8_t value;
    read(pcal6416a_fd, &value, 1);
    return value;
}

void io_init(void)
{
    pcal6416a_init();
}

void io_set_direction(PinNames pin, gpio_dir direction)
{
    uint8_t value = pcal6416a_read_register(CONFIG_PORT_1)& ~(1 << pin);
    
    //in is 1 aand 0 is out
    if (direction == GPIO_IN)
    {
        value |= (1 << pin);
        printf("IO-IN-CONFIG: %d\n", value);
        pcal6416a_write_register(CONFIG_PORT_1, value);

    }
    else if (direction == GPIO_OUT)
    {
        printf ("%d\n", pin);
        value |= (0 << pin);
        printf("IO-OUT-CONFIG: %d\n", value);
        pcal6416a_write_register(CONFIG_PORT_1, value);
        
    }

}

void io_write(PinNames pin, uint8_t value)
{
    uint8_t output_value = pcal6416a_read_register(OUTPUT_PORT_1)& ~(1 << pin);
    output_value |= (value << pin);
    pcal6416a_write_register (OUTPUT_PORT_1, output_value);
    printf("IO-OUT-WRITE: pin: %d value: %d\n", pin, output_value);   
}

uint32_t io_read(PinNames pin)
{
    uint8_t output_value = pcal6416a_read_register(INPUT_PORT_1) & (1 << pin);
    printf("IO-OUT-READ: pin: %d value: %d\n", pin, output_value); 
    return  (output_value >> pin);
}

void io_interrupt_setup_p1_4(void)
{
    //enable P1_4 interrpt
    uint8_t value = 0xEF;
    pcal6416a_write_register (INTERRUPT_MASK_P0RT_1, value);

    //set input latch to zero
    value = 0x00; 
    pcal6416a_write_register (INPUT_LATCH_PORT_1, value);

}