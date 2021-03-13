#ifndef MOTOR_H
#define	MOTOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"
#include "Timer.h"

typedef enum
{
	MOTOR1_ID
}MOTOR_t;

void Motor_init( Id_t id, Id_t xGpioId, uint8_t xPin, Id_t xTimerId );
void Motor_setSpeed( Id_t id, Timer_t speed );
Timer_t Motor_getSpeed( Id_t id );

#endif	/* MOTOR_H */
