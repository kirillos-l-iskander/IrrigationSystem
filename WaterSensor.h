#ifndef WATER_SENSOR_H
#define	WATER_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"

typedef enum
{
	WATER_SENSOR1_ID
}WATER_SENSOR_t;

void WaterSensor_init( Id_t id, Id_t xGpioId, uint8_t xPin );
uint8_t WaterSensor_getState( Id_t id );

#endif	/* SOIL_SENSOR_H */
