#include "WaterSensor.h"

typedef struct
{
	Id_t GpioId;
	uint8_t Pin;
}WaterSensor_t;

static WaterSensor_t WaterSensor[ WATER_SENSOR_NUMBER ];

void WaterSensor_Init( void )
{
	size_t Id = 0;
	for ( Id = 0; Id < WATER_SENSOR_NUMBER; Id++ )
	{
		Gpio_InitPin( WaterSensor[ Id ].GpioId, WaterSensor[ Id ].Pin, OUTPUT );
	}
}

uint8_t WaterSensor_GetState( Id_t Id )
{
	return Gpio_GetPinState( WaterSensor[ Id ].GpioId, WaterSensor[ Id ].Pin );
}

void WaterSensor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin )
{
	WaterSensor[ Id ].GpioId = GpioId;
	WaterSensor[ Id ].Pin = Pin;
}
