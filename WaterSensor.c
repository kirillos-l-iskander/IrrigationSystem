#include "WaterSensor.h"

typedef struct
{
	Id_t xGpioId;
	uint8_t xPin;
}WaterSensor_t;

static WaterSensor_t waterSensor[ WATER_SENSOR_NUMBER ];

void WaterSensor_init( Id_t id, Id_t xGpioId, uint8_t xPin )
{
	waterSensor[ id ].xGpioId = xGpioId;
	waterSensor[ id ].xPin = xPin;
	Gpio_initPin( waterSensor[ id ].xGpioId, waterSensor[ id ].xPin, OUTPUT );
}

uint8_t WaterSensor_getState( Id_t id )
{
	return Gpio_getPinState( waterSensor[ id ].xGpioId, waterSensor[ id ].xPin );
}
