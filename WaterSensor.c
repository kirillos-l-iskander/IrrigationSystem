#include "WaterSensor.h"

typedef struct
{
	Id_t GpioId;
	uint8_t Pin;
}WaterSensor_t;

static WaterSensor_t WaterSensor[ WATER_SENSOR_NUMBER ];

void WaterSensor_Init( Id_t Id, Id_t GpioId, uint8_t Pin )
{
	WaterSensor[ Id ].GpioId = GpioId;
	WaterSensor[ Id ].Pin = Pin;
	Gpio_InitPin( WaterSensor[ Id ].GpioId, WaterSensor[ Id ].Pin, OUTPUT );
}

uint8_t WaterSensor_GetState( Id_t Id )
{
	return Gpio_GetPinState( WaterSensor[ Id ].GpioId, WaterSensor[ Id ].Pin );
}
