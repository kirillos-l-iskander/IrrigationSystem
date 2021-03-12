#ifndef LED_H
#define	LED_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void Led_Init( Id_t Id, Id_t GpioId, uint8_t Pin );
void Led_SetState( Id_t Id, uint8_t State );

#endif	/* LED_H */
