#ifndef GPIO_H
#define GPIO_H

#include "SchedulerConfig.h"

#define INPUT		( 0 )
#define OUTPUT		( 1 )
#define OUTPUT_AF	( 1 )
#define LOW			( 0 )
#define HIGH		( 1 )

#define GPIOA_ID	( 0 )
#define GPIOB_ID	( 1 )
#define GPIOC_ID	( 2 )
#define GPIOD_ID	( 3 )

void Gpio_InitPin( Id_t Id, UBaseType_t Pin, UBaseType_t Mode );
void Gpio_SetPinState( Id_t Id, UBaseType_t Pin, UBaseType_t State );
UBaseType_t Gpio_GetPinState( Id_t Id, UBaseType_t Pin );
void Gpio_SetPortState( Id_t Id, UBaseType_t Pins, UBaseType_t State );
UBaseType_t Gpio_GetPortState( Id_t Id, UBaseType_t Pins );

#endif /* GPIO_H */
