#ifndef SOIL_SENSOR_H
#define	SOIL_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void SoilSensor_Init( void );
uint8_t SoilSensor_GetState( Id_t Id );
void SoilSensor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* SOIL_SENSOR_H */
