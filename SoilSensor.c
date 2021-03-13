#include "SoilSensor.h"

typedef struct
{
	Id_t xGpioId;
	uint8_t xPin;
}SoilSensor_t;

static SoilSensor_t soilSensor[ SOIL_SENSOR_NUMBER ];

void SoilSensor_init( Id_t id, Id_t xGpioId, uint8_t xPin )
{
	soilSensor[ id ].xGpioId = xGpioId;
	soilSensor[ id ].xPin = xPin;
	Gpio_initPin( soilSensor[ id ].xGpioId, soilSensor[ id ].xPin, OUTPUT );
}

UBaseType_t SoilSensor_getState( Id_t id )
{
	return Gpio_getPinState( soilSensor[ id ].xGpioId, soilSensor[ id ].xPin );
}
