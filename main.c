#include "SchedulerConfig.h"
#include "Scheduler.h"
#include "Config.h"

#include "Gpio.h"
#include "Timer.h"

#include "Led.h"
#include "Soilsnsr.h"
#include "Watersnsr.h"
#include "Motor.h"
#include "Lcd.h"
#include "Irrigation.h"

static void (*systickInterrupt)( void ) = NULL;

ISR(TIMER1_COMPA_vect)
{
	(*systickInterrupt)();
}

int main( void )
{
	Led_init( LED_ID_1, GPIO_ID_D, GPIO_PIN_7 );
	Soilsnsr_init( SOILSNSR_ID_1, GPIO_ID_A, GPIO_PIN_0 );
	Watersnsr_init( WATERSNSR_ID_1, GPIO_ID_A, GPIO_PIN_1 );
	Motor_init( MOTOR_ID_1, GPIO_ID_B, GPIO_PIN_3, TIMER_ID_0, TIMER_CHANNEL_1 );
	Lcd_init( LCD_ID_1, GPIO_ID_D, GPIO_PIN_2, GPIO_ID_D, GPIO_PIN_3, GPIO_ID_C, GPIO_PIN_0 );
	Irrigation_init( IRRIGATION_ID_1, SOILSNSR_ID_1, WATERSNSR_ID_1, MOTOR_ID_1, LCD_ID_1 );

	Scheduler_init();
	Scheduler_addTask( Led_update, (void *) LED_ID_1, MS_TO_TICKS( 0 ), MS_TO_TICKS( 100 ) );
	Scheduler_addTask( Soilsnsr_update, (void *) SOILSNSR_ID_1, MS_TO_TICKS( 1 ), MS_TO_TICKS( 100 ) );
	Scheduler_addTask( Watersnsr_update, (void *) WATERSNSR_ID_1, MS_TO_TICKS( 1 ), MS_TO_TICKS( 100 ) );
	Scheduler_addTask( Irrigation_update, (void *) IRRIGATION_ID_1, MS_TO_TICKS( 2 ), MS_TO_TICKS( 100 ) );
	Scheduler_addTask( Motor_update, (void *) MOTOR_ID_1, MS_TO_TICKS( 3 ), MS_TO_TICKS( 100 ) );
	Scheduler_addTask( Lcd_update, (void *) LCD_ID_1, MS_TO_TICKS( 3 ), MS_TO_TICKS( 5 ) );
	systickInterrupt = Scheduler_update;
	Scheduler_start();
	while( 1 )
	{
		Scheduler_dispatchTasks();
	}
	return SCH_RETURN_NORMAL;
}
