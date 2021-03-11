#ifndef IRRIGATION_H
#define IRRIGATION_H

#include "SchedulerConfig.h"
#include "SoilSensor.h"
#include "WaterSensor.h"
#include "Motor.h"
#include "LcdTask.h"

void IrrigationTask_Init( void );
void IrrigationTask_Update( void *Paramter );

#endif /* IRRIGATION_H */
