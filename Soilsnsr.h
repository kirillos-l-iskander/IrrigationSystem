#ifndef SOILSNSR_H
#define	SOILSNSR_H

#include "Config.h"
#include "Gpio.h"

typedef enum
{
	SOILSNSR_ID_1 = 0,
	SOILSNSR_ID_MAX,
}	SOILSNSR_ID_t;

typedef enum
{
	SOILSNSR_STATE_LOW = 0,
	SOILSNSR_STATE_HIGH,
	SOILSNSR_STATE_ERROR,
}	SOILSNSR_STATE_t;

void Soilsnsr_init( SOILSNSR_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin );
void Soilsnsr_update( void *paramter );
SOILSNSR_STATE_t Soilsnsr_getState( SOILSNSR_ID_t id );

#endif	/* SOILSNSR_H */
