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

static Gpio_t *Gpio[ 4 ] = { GPIOA, GPIOB, GPIOC, GPIOD };

void Gpio_InitPin( Id_t Id, UBaseType_t Pin, UBaseType_t Mode )
{
	Gpio[ Id ]->DDR = ( Gpio[ Id ]->DDR & ~( 1 << Pin ) ) | ( Mode << Pin );
}

void Gpio_SetPinState( Id_t Id, UBaseType_t Pin, UBaseType_t State )
{
	Gpio[ Id ]->PORT = ( Gpio[ Id ]->PORT & ~( 1 << Pin ) ) | ( State << Pin );
}

UBaseType_t Gpio_GetPinState( Id_t Id, UBaseType_t Pin )
{
	return ( Gpio[ Id ]->PIN & ( 1<< Pin ) ) >> Pin;
}

void Gpio_SetPortState( Id_t Id, UBaseType_t Pins, UBaseType_t State )
{
	Gpio[ Id ]->PORT = ( Gpio[ Id ]->PORT & ~Pins ) | ( State & Pins );
}

UBaseType_t Gpio_GetPortState( Id_t Id, UBaseType_t Pins )
{
	return ( Gpio[ Id ]->PIN & Pins );
}
