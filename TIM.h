#ifndef TIM_H
#define TIM_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "LCD.h"
#include "IS.h"

void TIM0_Init(void);
void TIM1_Init(uint16_t Ticks_N);
void TIM2_Init(void);

void TIM0_InitPWM0(void);
void TIM1_InitPWM1(void);
void TIM2_InitPWM2(void);
void TIM0_SetPWM0DutyCycle(uint8_t DutyCycle);
void TIM1_SetPWM1ADutyCycle(uint8_t DutyCycle);
void TIM1_SetPWM1BDutyCycle(uint8_t DutyCycle);
void TIM2_SetPWM2DutyCycle(uint8_t DutyCycle);

#endif /* TIM_H */
