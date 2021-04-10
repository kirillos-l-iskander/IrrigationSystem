#ifndef WATERSNSR_H
#define	WATERSNSR_H

#include "Config.h"
#include "Gpio.h"

typedef enum
{
	WATERSNSR_ID_1,
	WATERSNSR_ID_MAX,
}	WATERSNSR_ID_t;

typedef enum
{
	WATERSNSR_STATE_LOW = 0,
	WATERSNSR_STATE_HIGH,
	WATERSNSR_STATE_ERROR,
}	WATERSNSR_STATE_t;

void Watersnsr_init( WATERSNSR_ID_t id, GPIO_ID_t xGpioId, GPIO_PIN_t xPin );
void Watersnsr_update( void *paramter );
WATERSNSR_STATE_t Watersnsr_getState( WATERSNSR_ID_t id );

#endif	/* WATERSNSR_H */
