#include "Gpio.h"

#define GPIOA ( ( Gpio_t * ) ( 0x20 + 0x19 ) )
#define GPIOB ( ( Gpio_t * ) ( 0x20 + 0x16 ) )
#define GPIOC ( ( Gpio_t * ) ( 0x20 + 0x13 ) )
#define GPIOD ( ( Gpio_t * ) ( 0x20 + 0x10 ) )

typedef struct
{
	uint8_t PIN;
	uint8_t DDR;
	uint8_t PORT;
}Gpio_t;

static Gpio_t *gpio[ 4 ] = { GPIOA, GPIOB, GPIOC, GPIOD };

void Gpio_initPin( Id_t id, UBaseType_t pin, UBaseType_t mode )
{
	gpio[ id ]->DDR = ( gpio[ id ]->DDR & ~( 1 << pin ) ) | ( mode << pin );
}

void Gpio_setPinState( Id_t id, UBaseType_t pin, UBaseType_t state )
{
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~( 1 << pin ) ) | ( state << pin );
}

UBaseType_t Gpio_getPinState( Id_t id, UBaseType_t pin )
{
	return ( gpio[ id ]->PIN & ( 1<< pin ) ) >> pin;
}

void Gpio_setPortState( Id_t id, UBaseType_t pins, UBaseType_t state )
{
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~pins ) | ( state & pins );
}

UBaseType_t Gpio_getPortState( Id_t id, UBaseType_t pins )
{
	return ( gpio[ id ]->PIN & pins );
}
