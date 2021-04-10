#include "Irrigation.h"

typedef struct
{
	SOILSNSR_ID_t soilsnsrId;
	WATERSNSR_ID_t watersnsrId;
	MOTOR_ID_t motorId;
	LCD_ID_t lcdId;
}	Irrigation_t;

static Irrigation_t irrigation[ IRRIGATION_ID_MAX ];

void Irrigation_init( IRRIGATION_ID_t id, SOILSNSR_ID_t soilsnsrId, WATERSNSR_ID_t watersnsrId, MOTOR_ID_t motorId, LCD_ID_t lcdId )
{
	irrigation[ id ].soilsnsrId = soilsnsrId;
	irrigation[ id ].watersnsrId = watersnsrId;
	irrigation[ id ].motorId = motorId;
	irrigation[ id ].lcdId = lcdId;
}

void Irrigation_update( void *paramter )
{
	IRRIGATION_ID_t id = (IRRIGATION_ID_t) paramter;
	SOILSNSR_STATE_t soilsnsr = Soilsnsr_getState( irrigation[ id ].soilsnsrId );
	WATERSNSR_STATE_t watersnsr = Watersnsr_getState( irrigation[ id ].watersnsrId );
	Lcd_clear( id );
	if( soilsnsr == SOILSNSR_STATE_HIGH )
	{
		Lcd_setString( irrigation[ id ].lcdId, "Humidity:HIGH", 0, 0 );
	}else
	{
		Lcd_setString( irrigation[ id ].lcdId, "Humidity:LOW", 0, 0 );
	}
	if( watersnsr == WATERSNSR_STATE_HIGH )
	{
		Lcd_setString( irrigation[ id ].lcdId, "Tank Level:HIGH", 1, 0 );
	}else
	{
		Lcd_setString( irrigation[ id ].lcdId, "Tank Level:LOW", 1, 0 );
		Lcd_setString( irrigation[ id ].lcdId, "Warning", 3, 9 );
	}
	if( soilsnsr == SOILSNSR_STATE_LOW && watersnsr == WATERSNSR_STATE_HIGH )
	{
		Lcd_setString( irrigation[ id ].lcdId, "Pump:ON", 2, 0 );
		Motor_setSpeed( irrigation[ id ].motorId, MOTOR_SPEED_100 );
	}else
	{
		Lcd_setString( irrigation[ id ].lcdId, "Pump:OFF", 2, 0 );
		Motor_setSpeed( irrigation[ id ].motorId, MOTOR_SPEED_0 );
	}
}
