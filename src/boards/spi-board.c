#include <spi-board.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "../include/board-config.h"

struct spi_ioc_transfer transaction;

int fd;
int ret;

unsigned char mode = SPI_MODE_0;
uint32_t spi_speed = 1000000;


void SpiInit( Spi_t *obj, SpiId_t spiId, PinNames mosi, PinNames miso, PinNames sclk, PinNames nss )
{
     
    const char* spi_device= "/dev/spidev0.0";

    /* open the SPI device */
    fd = open(spi_device, O_RDWR);
    if (ret < 0)
    {
        perror("Failed to open SPI device\n");
        exit(EXIT_FAILURE);
    }
    
    /* Configure the SPI settings */  
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret < 0)
    {
        perror("Failed to set SPI write mode\n");
        exit(EXIT_FAILURE);
    }

    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret < 0)
    {
        perror("Failed to set SPI read mode\n");
        exit(EXIT_FAILURE);        
    }
      
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
    if (ret < 0)
    {
        perror("Failed to set SPI write speed\n");
        exit(EXIT_FAILURE);
    }

    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
    if (ret < 0)
    {
        perror("Failed to set SPI read speed\n");
        exit(EXIT_FAILURE);
    }

}

void set_spi_cs_high(void)
{
    transaction.cs_change= 0;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &transaction);
}

uint16_t SpiInOut(Spi_t *obj, uint16_t outData)
{
    const uint8_t outDataB = (outData & 0xff);
    uint8_t inDataB =0x00;

    transaction.tx_buf = (unsigned long)&outDataB;
    transaction.rx_buf = (unsigned long)&inDataB;
    transaction.len = sizeof(uint8_t);
    transaction.speed_hz = spi_speed;
    transaction.bits_per_word = 8;
    transaction.cs_change= 1;
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &transaction);
    return inDataB;
}