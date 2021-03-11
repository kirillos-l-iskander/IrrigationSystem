#ifndef MOTOR_H
#define	MOTOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"
#include "Timer.h"

void Motor_Init( void );
void Motor_SetSpeed( Id_t Id, Timer_t Speed );
Timer_t Motor_GetSpeed( Id_t Id );
void Motor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin );
void Motor_SetTimer( Id_t Id, Id_t TimerId );

#endif	/* MOTOR_H */
