#include "SoilSensor.h"

typedef struct
{
	Id_t GpioId;
	uint8_t Pin;
}SoilSensor_t;

static SoilSensor_t SoilSensor[ SOIL_SENSOR_NUMBER ];

void SoilSensor_Init( void )
{
	size_t Id = 0;
	for ( Id = 0; Id < SOIL_SENSOR_NUMBER; Id++ )
	{
		Gpio_InitPin( SoilSensor[ Id ].GpioId, SoilSensor[ Id ].Pin, OUTPUT );
	}
}

UBaseType_t SoilSensor_GetState( Id_t Id )
{
	return Gpio_GetPinState( SoilSensor[ Id ].GpioId, SoilSensor[ Id ].Pin );
}

void SoilSensor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin )
{
	SoilSensor[ Id ].GpioId = GpioId;
	SoilSensor[ Id ].Pin = Pin;
}
