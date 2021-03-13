#include "SchedulerConfig.h"
#include "Scheduler.h"
#include "Config.h"

#include "Gpio.h"
#include "Timer.h"

#include "Led.h"
#include "LedTask.h"
#include "Lcd.h"
#include "LcdTask.h"
#include "SoilSensor.h"
#include "WaterSensor.h"
#include "Motor.h"
#include "IrrigationTask.h"

static void (*systickInterrupt)( void ) = NULL;

ISR(TIMER1_COMPA_vect)
{
	(*systickInterrupt)();
}

int main( void )
{
	LedTask_init( LED1_ID, LED0_GPIO, LED0_PIN );
	LcdTask_init( LCD1_ID, LCD0_GPIO_RS, PIN_RS, LCD0_GPIO_E, PIN_E, LCD0_GPIO_D0, PIN_D0 );
	SoilSensor_init( SOIL_SENSOR1_ID, SOILSENSOR0_GPIO, SOILSENSOR0_PIN );
	WaterSensor_init( WATER_SENSOR1_ID, WATERSENSOR0_GPIO, WATERSENSOR0_PIN );
	Motor_init( MOTOR1_ID, MOTOR0_GPIO, MOTOR0_PIN, MOTOR0_TIMER );
	IrrigationTask_init( IRRIGATION1_ID );

	Scheduler_init();
	Scheduler_addTask( LedTask_update, (void *) LED1_ID, 0, 100 );
	Scheduler_addTask( IrrigationTask_update, (void *) IRRIGATION1_ID, 1, 100 );
	Scheduler_addTask( LcdTask_update, (void *) LCD1_ID, 2, 5 );
	systickInterrupt = Scheduler_update;
	Scheduler_start();
	while( 1 )
	{
		Scheduler_dispatchTasks();
	}
	return SCH_RETURN_NORMAL;
}
