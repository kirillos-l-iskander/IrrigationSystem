#ifndef SOIL_SENSOR_H
#define	SOIL_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"

typedef enum
{
	SOIL_SENSOR1_ID
}SOIL_SENSOR_t;

void SoilSensor_init( Id_t id, Id_t xGpioId, uint8_t xPin );
uint8_t SoilSensor_getState( Id_t id );

#endif	/* SOIL_SENSOR_H */
