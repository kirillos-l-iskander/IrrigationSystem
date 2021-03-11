#ifndef LED_H
#define	LED_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void Led_Init( void );
void Led_SetState( Id_t Id, uint8_t State );
void Led_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* LED_H */
