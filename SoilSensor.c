#include "SoilSensor.h"

typedef struct
{
	Id_t GpioId;
	uint8_t Pin;
}SoilSensor_t;

static SoilSensor_t SoilSensor[ SOIL_SENSOR_NUMBER ];

void SoilSensor_Init( Id_t Id, Id_t GpioId, uint8_t Pin )
{
	SoilSensor[ Id ].GpioId = GpioId;
	SoilSensor[ Id ].Pin = Pin;
	Gpio_InitPin( SoilSensor[ Id ].GpioId, SoilSensor[ Id ].Pin, OUTPUT );
}

UBaseType_t SoilSensor_GetState( Id_t Id )
{
	return Gpio_GetPinState( SoilSensor[ Id ].GpioId, SoilSensor[ Id ].Pin );
}
