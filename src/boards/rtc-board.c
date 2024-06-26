#include <math.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "rtc-board.h"
#include "utilities.h"


struct timespec boot_time;


void RtcInit( void )
{
    RtcSetTimerContext();
    
}


void RtcDelayMs( uint32_t delay)
{

}

void RtcBkupRead( uint32_t *data0, uint32_t *data1 )
{
    *data0 = 0;
    *data1 = 0;
}

pthread_t thread;
uint32_t alarm_timeout;

void *callback(void *arg) {
    struct timespec alarmTime;
    clock_gettime(CLOCK_BOOTTIME, &alarmTime);
    alarmTime.tv_sec += alarm_timeout / 1000000;
    alarmTime.tv_nsec += (alarm_timeout % 1000000) * 1000;
    clock_nanosleep(CLOCK_BOOTTIME, TIMER_ABSTIME, &alarmTime, NULL);
    TimerIrqHandler( );
    pthread_exit(NULL);
}

void RtcSetAlarm( uint32_t timeout )
{
    alarm_timeout = timeout;
    pthread_cancel(thread);
    pthread_create(&thread, NULL, callback, NULL);

}

void RtcStopAlarm( void )
{
    pthread_cancel(thread);
}

uint32_t RtcGetTimerElapsedTime( void )
{
    struct timespec boot_time_now;
    clock_gettime(CLOCK_BOOTTIME, &boot_time_now);
    int64_t rtc_timer = (boot_time_now.tv_sec * 1000000) + boot_time_now.tv_nsec / 1000;
    int64_t rtc_timer_context = (boot_time.tv_sec * 1000000) + boot_time.tv_nsec / 1000;
    return (rtc_timer - rtc_timer_context);
   
}


uint32_t RtcSetTimerContext( void )
{   
    clock_gettime(CLOCK_BOOTTIME, &boot_time);
    uint64_t rtc_timer_context = (boot_time.tv_sec * 1000000) + boot_time.tv_nsec / 1000;
    return  rtc_timer_context;
}


uint32_t RtcGetTimerContext( void )
{
    uint64_t rtc_timer_context = (boot_time.tv_sec * 1000000) + boot_time.tv_nsec / 1000;
    return rtc_timer_context;  
}

uint32_t RtcGetMinimumTimeout( void )
{
    return 1;
}

uint32_t RtcGetCalendarTime( uint16_t *milliseconds )
{

    struct timespec tp;
    clock_gettime(CLOCK_BOOTTIME, &tp);
    uint32_t seconds = tp.tv_sec;
    uint32_t now = (tp.tv_sec * 1000) + (tp.tv_nsec/ 1000000);
    *milliseconds = now;
    return seconds;

}

uint32_t RtcGetTimerValue() {    
       
    struct timespec tp;
    clock_gettime(CLOCK_BOOTTIME, &tp);
    uint64_t now = (uint64_t)tp.tv_sec * 1000000 + tp.tv_nsec / 1000;
    return now;

}

TimerTime_t RtcTick2Ms( uint32_t tick )
{
    /* The ticks are in microseconds */
    return tick / 1000;
}

uint32_t RtcMs2Tick( TimerTime_t milliseconds )
{
    /* The ticks are in microseconds */
    return milliseconds * 1000; 
}



void RtcBkupWrite( uint32_t data0, uint32_t data1 )
{
}

void RtcProcess( void )
{
    /* Not used on this platform. */
}

TimerTime_t RtcTempCompensation( TimerTime_t period, float temperature )
{
    float k = RTC_TEMP_COEFFICIENT;
    float kDev = RTC_TEMP_DEV_COEFFICIENT;
    float t = RTC_TEMP_TURNOVER;
    float tDev = RTC_TEMP_DEV_TURNOVER;
    float interim = 0.0f;
    float ppm = 0.0f;

    if( k < 0.0f )
    {
        ppm = ( k - kDev );
    }
    else
    {
        ppm = ( k + kDev );
    }
    interim = ( temperature - ( t - tDev ) );
    ppm *=  interim * interim;

    /* Calculate the drift in time */
    interim = ( ( float ) period * ppm ) / 1000000.0f;
    /* Calculate the resulting time period */
    interim += period;
    interim = floor( interim );

    if( interim < 0.0f )
    {
        interim = ( float )period;
    }

    /* Calculate the resulting period */
    return ( TimerTime_t ) interim;
}