#include "Gpio.h"

#define GPIOA ( ( Gpio_t * ) &PINA )
#define GPIOB ( ( Gpio_t * ) &PINB )
#define GPIOC ( ( Gpio_t * ) &PINC )
#define GPIOD ( ( Gpio_t * ) &PIND )

typedef struct
{
	uint8_t PIN;
	uint8_t DDR;
	uint8_t PORT;
}	Gpio_t;

static Gpio_t *gpio[ GPIO_ID_MAX ] = { GPIOA, GPIOB, GPIOC, GPIOD };

void Gpio_initPin( GPIO_ID_t id, GPIO_PIN_t pin, GPIO_MODE_t mode, GPIO_TYPE_t type )
{
	gpio[ id ]->DDR = ( gpio[ id ]->DDR & ~( 1 << pin ) ) | ( mode << pin );
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~( 1 << pin ) ) | ( type << pin );
}

void Gpio_setPinState( GPIO_ID_t id, GPIO_PIN_t pin, GPIO_STATE_t state )
{
	state &= 0x1;
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~( 1 << pin ) ) | ( state << pin );
}

GPIO_STATE_t Gpio_getPinState( GPIO_ID_t id, GPIO_PIN_t pin )
{
	return ( gpio[ id ]->PIN & ( 1<< pin ) ) >> pin;
}

void Gpio_setPortState( GPIO_ID_t id, GPIO_PIN_t pins, GPIO_STATE_t state )
{
	state &= pins;
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~pins ) | ( state );
}

GPIO_STATE_t Gpio_getPortState( GPIO_ID_t id, GPIO_PIN_t pins )
{
	return ( gpio[ id ]->PIN & pins );
}
