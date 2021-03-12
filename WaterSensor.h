#ifndef WATER_SENSOR_H
#define	WATER_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void WaterSensor_Init( Id_t Id, Id_t GpioId, uint8_t Pin );
uint8_t WaterSensor_GetState( Id_t Id );

#endif	/* SOIL_SENSOR_H */
