#include "SchedulerConfig.h"
#include "Timer.h"
#include "Led.h"

void Scheduler_initSysTick( TickType_t systickPeriod )
{
	GIE();
	Timer_enableInterrupt( TIMER_ID_1 );
	Timer_init( TIMER_ID_1, TIMER_MODE_NORMAL, systickPeriod, TIMER_CHANNEL_NORMAL, TIMER_EVENT_NORMAL );
}

void Scheduler_displayError( UBaseType_t errorCode )
{
	if( errorCode )
	{
		Led_setState( LED_ID_1, LED_STATE_OFF, LED_BLINK_0MS );
	}else
	{
		Led_setState( LED_ID_1, LED_STATE_ON, LED_BLINK_0MS );
	}
}

void Scheduler_sleepHardware( void )
{

}

void Scheduler_delayHardwareMs( volatile uint32_t msDelay )
{

}

void Scheduler_delayHardwareUs( volatile uint32_t usDelay )
{

}

void Scheduler_delaySoftwareMs( volatile uint32_t msDelay )
{
	while( msDelay-- )
	{
		Scheduler_delaySoftwareUs( 1000 );
	}
}

void Scheduler_delaySoftwareUs( volatile uint32_t usDelay )
{
	volatile uint8_t delay;
	while( usDelay-- )
	{
		delay = ( uint8_t ) ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / 1000000 );
		while( delay-- );
	}
}
