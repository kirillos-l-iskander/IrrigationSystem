#include "IrrigationTask.h"

typedef struct
{
	Id_t SoilSensorId;
	Id_t WaterSensorId;
	Id_t MotorId;
}IrrigationTask_t;

static IrrigationTask_t IrrigationTask[ 1 ];

void IrrigationTask_Init( void )
{
	SoilSensor_Init();
	WaterSensor_Init();
	Motor_Init();
}

void IrrigationTask_SetSoilSensorId( Id_t Id, Id_t SoilSensorId )
{
	IrrigationTask[ Id ].SoilSensorId = SoilSensorId;
}

void IrrigationTask_SetWaterSensorId( Id_t Id, Id_t WaterSensorId )
{
	IrrigationTask[ Id ].WaterSensorId = WaterSensorId;
}

void IrrigationTask_SetMotorId( Id_t Id, Id_t MotorId )
{
	IrrigationTask[ Id ].MotorId = MotorId;
}

void IrrigationTask_Update( void *Paramter )
{
	size_t Id = 0;
	for( Id = 0; Id < IRRIGATION_TASK_NUMBER; Id++ )
	{
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
}
