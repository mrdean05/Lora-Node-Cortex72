#include <unistd.h>
#include "delay-board.h"

void DelayMsMcu( uint32_t ms )
{
   usleep(ms * 1000);
}