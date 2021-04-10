#ifndef IRRIGATION_H
#define IRRIGATION_H

#include "Config.h"
#include "Soilsnsr.h"
#include "Watersnsr.h"
#include "Motor.h"
#include "Lcd.h"

typedef enum
{
	IRRIGATION_ID_1 = 0,
	IRRIGATION_ID_MAX,
}	IRRIGATION_ID_t;

void Irrigation_init( IRRIGATION_ID_t id, SOILSNSR_ID_t xSoilsnsrId, WATERSNSR_ID_t xWatersnsrId, MOTOR_ID_t xMotorId, LCD_ID_t xLcdId );
void Irrigation_update( void *paramter );

#endif /* IRRIGATION_H */
