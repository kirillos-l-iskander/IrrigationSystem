#ifndef WATER_SENSOR_H
#define	WATER_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void WaterSensor_Init( void );
uint8_t WaterSensor_GetState( Id_t Id );
void WaterSensor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* SOIL_SENSOR_H */
