#ifndef TIMER_H
#define TIMER_H

#include "SchedulerConfig.h"

#define TIMER0_ID ( 0 )
#define TIMER1_ID ( 1 )
#define TIMER2_ID ( 2 )

typedef uint16_t Timer_t;

void Timer_Init( Id_t Id, Timer_t TicksNumber );
void Timer_InitPwm( Id_t Id );
void Timer_SetPwmDutyCycle( Id_t Id, Timer_t DutyCycle );
Timer_t Timer_GetPwmDutyCycle( Id_t Id );

#endif /* TIMER_H */
