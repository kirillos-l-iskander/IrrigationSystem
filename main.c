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
	Led_SetGpio( 0, LED0_GPIO, LED0_PIN );
	Led_Init();
	LedTask_Init();

	Lcd_SetGpioRs( 0, LCD0_GPIO_RS, PIN_RS );
	Lcd_SetGpioE( 0, LCD0_GPIO_E, PIN_E );
	Lcd_SetGpioD0( 0, LCD0_GPIO_D0, PIN_D0 );
	Lcd_Init();
	LcdTask_Init();

	SoilSensor_SetGpio( 0, SOILSENSOR0_GPIO, SOILSENSOR0_PIN );
	SoilSensor_Init();

	WaterSensor_SetGpio( 0, WATERSENSOR0_GPIO, WATERSENSOR0_PIN );
	WaterSensor_Init();

	Motor_SetGpio( 0, MOTOR0_GPIO, MOTOR0_PIN );
	Motor_SetTimer( 0, MOTOR0_TIMER );
	Motor_Init();

	IrrigationTask_Init();

	Scheduler_init();
	Scheduler_addTask( LedTask_Update, NULL, 0, 100 );
	Scheduler_addTask( IrrigationTask_Update, NULL, 1, 100 );
	Scheduler_addTask( LcdTask_Update, NULL, 2, 5 );
	systickInterrupt = Scheduler_update;
	Scheduler_start();
	while( 1 )
	{
		Scheduler_dispatchTasks();
	}
	return SCH_RETURN_NORMAL;
}
