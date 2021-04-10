#include "Soilsnsr.h"

typedef struct
{
	GPIO_ID_t gpioId;
	GPIO_PIN_t gpioPin;
	SOILSNSR_STATE_t state;
}	Soilsnsr_t;

static Soilsnsr_t soilsnsr[ SOILSNSR_ID_MAX ];

void initSoilsnsrHardware( SOILSNSR_ID_t id );
SOILSNSR_STATE_t getSoilsnsrHardwareState( SOILSNSR_ID_t id );

void Soilsnsr_init( SOILSNSR_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin )
{
	soilsnsr[ id ].gpioId = gpioId;
	soilsnsr[ id ].gpioPin = gpioPin;
	soilsnsr[ id ].state = GPIO_STATE_LOW;
	initSoilsnsrHardware( id );
}

void Soilsnsr_update( void *paramter )
{
	SOILSNSR_ID_t id = (SOILSNSR_ID_t) paramter;
	soilsnsr[ id ].state = getSoilsnsrHardwareState( id );
}

SOILSNSR_STATE_t Soilsnsr_getState( SOILSNSR_ID_t id )
{
	return soilsnsr[ id ].state;
}

void initSoilsnsrHardware( SOILSNSR_ID_t id )
{
	Gpio_initPin( soilsnsr[ id ].gpioId, soilsnsr[ id ].gpioPin, GPIO_MODE_INPUT, GPIO_TYPE_FLOATING );
}

SOILSNSR_STATE_t getSoilsnsrHardwareState( SOILSNSR_ID_t id )
{
	if( Gpio_getPinState( soilsnsr[ id ].gpioId, soilsnsr[ id ].gpioPin ) == GPIO_STATE_LOW )
	{
		return SOILSNSR_STATE_LOW;
	}
	else if( Gpio_getPinState( soilsnsr[ id ].gpioId, soilsnsr[ id ].gpioPin ) == GPIO_STATE_HIGH )
	{
		return SOILSNSR_STATE_HIGH;
	}else
	{
		return SOILSNSR_STATE_ERROR;
	}
}
