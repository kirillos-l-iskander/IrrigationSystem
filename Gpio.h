#ifndef GPIO_H
#define GPIO_H

#include "SchedulerConfig.h"

#define INPUT		( 0 )
#define OUTPUT		( 1 )
#define OUTPUT_AF	( 1 )
#define LOW			( 0 )
#define HIGH		( 1 )

typedef enum
{
	GPIOA_ID,
	GPIOB_ID,
	GPIOC_ID,
	GPIOD_ID
}GPIO_t;

void Gpio_initPin( Id_t id, UBaseType_t pin, UBaseType_t mode );
void Gpio_setPinState( Id_t id, UBaseType_t pin, UBaseType_t state );
UBaseType_t Gpio_getPinState( Id_t id, UBaseType_t pin );
void Gpio_setPortState( Id_t Id, UBaseType_t pins, UBaseType_t state );
UBaseType_t Gpio_getPortState( Id_t id, UBaseType_t pins );

#endif /* GPIO_H */
