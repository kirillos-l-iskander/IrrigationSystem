#include "Watersnsr.h"

typedef struct
{
	GPIO_ID_t gpioId;
	GPIO_PIN_t gpioPin;
	WATERSNSR_STATE_t state;
}Watersnsr_t;

static Watersnsr_t watersnsr[ WATERSNSR_ID_MAX ];

void initWatersnsrHardware( WATERSNSR_ID_t id );
WATERSNSR_STATE_t getWatersnsrHardwareState( WATERSNSR_ID_t id );

void Watersnsr_init( WATERSNSR_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin )
{
	watersnsr[ id ].gpioId = gpioId;
	watersnsr[ id ].gpioPin = gpioPin;
	watersnsr[ id ].state = GPIO_STATE_LOW;
	initWatersnsrHardware( id );
}

void Watersnsr_update( void *paramter )
{
	WATERSNSR_ID_t id = (WATERSNSR_ID_t) paramter;
	watersnsr[ id ].state = getWatersnsrHardwareState( id );
}

WATERSNSR_STATE_t Watersnsr_getState( WATERSNSR_ID_t id )
{
	return watersnsr[ id ].state;
}

void initWatersnsrHardware( WATERSNSR_ID_t id )
{
	Gpio_initPin( watersnsr[ id ].gpioId, watersnsr[ id ].gpioPin, GPIO_MODE_INPUT, GPIO_TYPE_FLOATING );
}

WATERSNSR_STATE_t getWatersnsrHardwareState( WATERSNSR_ID_t id )
{
	if( Gpio_getPinState( watersnsr[ id ].gpioId, watersnsr[ id ].gpioPin ) == GPIO_STATE_LOW )
	{
		return WATERSNSR_STATE_LOW;
	}
	else if( Gpio_getPinState( watersnsr[ id ].gpioId, watersnsr[ id ].gpioPin ) == GPIO_STATE_HIGH )
	{
		return WATERSNSR_STATE_HIGH;
	}else
	{
		return WATERSNSR_STATE_ERROR;
	}
}
