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
	LedTask_Init( 0, LED0_GPIO, LED0_PIN );

	LcdTask_Init( 0, LCD0_GPIO_RS, PIN_RS, LCD0_GPIO_E, PIN_E, LCD0_GPIO_D0, PIN_D0 );

	SoilSensor_Init( 0, SOILSENSOR0_GPIO, SOILSENSOR0_PIN );

	WaterSensor_Init( 0, WATERSENSOR0_GPIO, WATERSENSOR0_PIN );

	Motor_Init( 0, MOTOR0_GPIO, MOTOR0_PIN, MOTOR0_TIMER );

	IrrigationTask_Init();

	Scheduler_init();
	Scheduler_addTask( LedTask_Update, (void *) 0, 0, 100 );
	Scheduler_addTask( IrrigationTask_Update, (void *) 0, 1, 100 );
	Scheduler_addTask( LcdTask_Update, (void *) 0, 2, 5 );
	systickInterrupt = Scheduler_update;
	Scheduler_start();
	while( 1 )
	{
		Scheduler_dispatchTasks();
	}
	return SCH_RETURN_NORMAL;
}
