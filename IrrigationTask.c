#include "IrrigationTask.h"

void IrrigationTask_init( Id_t id )
{
}

void IrrigationTask_update( void *paramter )
{
	Id_t id = (Id_t) paramter;
	uint8_t soilSensor = 0;
	uint8_t waterSensor = 0;
	soilSensor = SoilSensor_getState( id );
	waterSensor = WaterSensor_getState( id );
	LcdTask_clear( id );
	if( soilSensor == HIGH )
	{
		LcdTask_setString( id, ( uint8_t* ) "Humidity:HIGH", 0, 0 );
	}else
	{
		LcdTask_setString( id, ( uint8_t* ) "Humidity:LOW", 0, 0 );
	}
	if( waterSensor == HIGH )
	{
		LcdTask_setString( id, ( uint8_t* ) "Tank Level:HIGH", 1, 0 );
	}else
	{
		LcdTask_setString( id, ( uint8_t* ) "Tank Level:LOW", 1, 0 );
		LcdTask_setString( id, ( uint8_t* ) "Warning", 3, 9 );
	}
	if( soilSensor == LOW && waterSensor == HIGH )
	{
		LcdTask_setString( id, ( uint8_t* ) "Pump:ON", 2, 0 );
		Motor_setSpeed( id, 255 );
	}else
	{
		LcdTask_setString( id, ( uint8_t* ) "Pump:OFF", 2, 0 );
		Motor_setSpeed( id, 0 );
	}
}
