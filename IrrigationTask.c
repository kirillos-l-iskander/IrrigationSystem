#include "IrrigationTask.h"

void IrrigationTask_Init( void )
{
}

void IrrigationTask_Update( void *Paramter )
{
	Id_t Id = (Id_t) Paramter;
	uint8_t SoilSensor = 0;
	uint8_t WaterSensor = 0;
	SoilSensor = SoilSensor_GetState( Id );
	WaterSensor = WaterSensor_GetState( Id );
	LcdTask_Clear( Id );
	if( SoilSensor == HIGH )
	{
		LcdTask_SetString( Id, ( uint8_t* ) "Humidity:HIGH", 0, 0 );
	}else
	{
		LcdTask_SetString( Id, ( uint8_t* ) "Humidity:LOW", 0, 0 );
	}
	if( WaterSensor == HIGH )
	{
		LcdTask_SetString( Id, ( uint8_t* ) "Tank Level:HIGH", 1, 0 );
	}else
	{
		LcdTask_SetString( Id, ( uint8_t* ) "Tank Level:LOW", 1, 0 );
		LcdTask_SetString( Id, ( uint8_t* ) "Warning", 3, 9 );
	}
	if( SoilSensor == LOW && WaterSensor == HIGH )
	{
		LcdTask_SetString( Id, ( uint8_t* ) "Pump:ON", 2, 0 );
		Motor_SetSpeed( Id, 255 );
	}else
	{
		LcdTask_SetString( Id, ( uint8_t* ) "Pump:OFF", 2, 0 );
		Motor_SetSpeed( Id, 0 );
	}
}
