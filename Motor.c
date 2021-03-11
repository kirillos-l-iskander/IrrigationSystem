#include "Motor.h"

typedef struct
{
	Id_t GpioId;
	uint8_t Pin;
	Id_t TimerId;
}Motor_t;

static Motor_t Motor[ MOTOR_NUMBER ];

void Motor_Init( void )
{
	size_t Id = 0;
	for ( Id = 0; Id < MOTOR_NUMBER; Id++ )
	{
		Gpio_InitPin( Motor[ Id ].GpioId, Motor[ Id ].Pin, OUTPUT_AF );
		Timer_InitPwm( Motor[ Id ].TimerId );
	}
}

void Motor_SetSpeed( Id_t Id, Timer_t Speed )
{
	Timer_SetPwmDutyCycle( Motor[ Id ].TimerId, Speed );
}

Timer_t Motor_GetSpeed( Id_t Id )
{
	return Timer_GetPwmDutyCycle( Motor[ Id ].TimerId );
}

void Motor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin )
{
	Motor[ Id ].GpioId = GpioId;
	Motor[ Id ].Pin = Pin;
}

void Motor_SetTimer( Id_t Id, Id_t TimerId )
{
	Motor[ Id ].TimerId = TimerId;
}
