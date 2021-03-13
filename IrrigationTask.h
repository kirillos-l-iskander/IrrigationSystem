#ifndef IRRIGATION_H
#define IRRIGATION_H

#include "SchedulerConfig.h"
#include "SoilSensor.h"
#include "WaterSensor.h"
#include "Motor.h"
#include "LcdTask.h"

typedef enum
{
	IRRIGATION1_ID
}IRRIGATION_t;

void IrrigationTask_init( Id_t id );
void IrrigationTask_update( void *paramter );

#endif /* IRRIGATION_H */
