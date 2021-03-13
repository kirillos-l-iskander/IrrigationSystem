#ifndef TIMER_H
#define TIMER_H

#include "SchedulerConfig.h"

typedef enum
{
	TIMER0_ID,
	TIMER1_ID,
	TIMER2_ID
}TIMER_t;

typedef uint16_t Timer_t;

void Timer_init( Id_t id, Timer_t tickNumber );
void Timer_initPwm( Id_t id );
void Timer_setPwmDutyCycle( Id_t id, Timer_t dutyCycle );
Timer_t Timer_getPwmDutyCycle( Id_t id );

#endif /* TIMER_H */
