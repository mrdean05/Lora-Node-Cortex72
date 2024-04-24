#include "gpio-board.h"
#include "../include/board-config.h"
#include "../include/ioexpander.h"



static void *interrupt_handler(void *arg);

static void set_io_port_1_4_interrupt();


void GpioMcuInit( Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes type, uint32_t value )
{
    obj->pin = pin;

    if ( pin == NC )
    {
        return;
    }

    if (mode == PIN_INPUT)
    {
        io_set_direction(pin, GPIO_IN);
    }

    else if (mode == PIN_OUTPUT)
    {
        io_set_direction(pin, GPIO_OUT);
        io_write(pin, value);
        printf("pin number: %d value: %d\n", pin, value);
    }
}

void GpioMcuWrite( Gpio_t *obj, uint32_t value )
{
    io_write(obj->pin, (uint8_t)value);
}

uint32_t GpioMcuRead( Gpio_t *obj )
{
    uint32_t read_value = io_read(obj->pin);
    return read_value;
}

int f;
struct pollfd poll_fds[1];
int ret;
char value[4];
int n;

pthread_t event_thread;

GpioIrqHandler *receive_handler;

void GpioMcuSetInterrupt( Gpio_t *obj, IrqModes irqMode, IrqPriorities irqPriority, GpioIrqHandler *irqHandler )
{
    set_io_port_1_4_interrupt(); 

    
    receive_handler = irqHandler;

    f = open("/sys/class/gpio/gpio22/value", O_RDONLY);
    if (f == -1) {
            perror("Can't open gpio22");
    return;
    }
    n = read(f, &value, sizeof(value));
    if (n > 0) {
            printf("Initial value for interrupt =%c\n",
            value[0]);
            lseek(f, 0, SEEK_SET);
            }

    poll_fds[0].fd = f;
    poll_fds[0].events = POLLPRI | POLLERR;


    // create the event thread
    pthread_create(&event_thread, NULL, interrupt_handler, NULL); 
}

void GpioMcuRemoveInterrupt( Gpio_t *obj )
{
        pthread_join(event_thread, NULL);
        close(f);    
}

void GpioMcuToggle( Gpio_t *obj )
{

}

void GpioMcuSetContext( Gpio_t *obj, void* context )
{

}


// callback function
static void *interrupt_handler(void *arg) {
        while (1)
        {
            printf("Waiting\n");
            ret = poll(poll_fds, 1, -1);
            if (ret > 0) {
                n = read(f, &value, sizeof(value));
                printf("Button pressed: value=%c\n",
                value[0]);

                if (value[0]== '1')
                {
                        receive_handler(NULL);
                }
                lseek(f, 0, SEEK_SET);

                        }
        }
return NULL;
}

static void set_io_port_1_4_interrupt()
{
    //set interrupt for Port 1_4 of the io expander
    io_interrupt_setup_p1_4();
}


