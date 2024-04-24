#ifndef GPIOEXPANDER_H
#define GPIOEXPANDER_H
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <pthread.h>
#include <linux/i2c-dev.h>


#include "gpio.h"

#define INPUT_PORT_0                  0x00
#define INPUT_PORT_1                  0x01
#define OUTPUT_PORT_0                 0x02
#define OUTPUT_PORT_1                 0x03
#define CONFIG_PORT_0                 0x06
#define CONFIG_PORT_1                 0x07
#define INTERRUPT_MASK_P0RT_1         0x4B
#define INPUT_LATCH_PORT_1            0x45


typedef enum
{
    GPIO_IN = 0,
    GPIO_OUT
}gpio_dir;

void io_init(void);
void io_set_direction(PinNames pin, gpio_dir direction);
void io_write(PinNames pin, uint8_t value);
uint32_t io_read(PinNames pin);
void io_interrupt_setup_p1_4(void);
#endif