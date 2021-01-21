#ifndef GPIO_H
#define GPIO_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "LCD.h"
#include "IS.h"

#define INPUT (0)
#define OUTPUT (1)
#define LOW (0)
#define HIGH (1)

#define GPIOA ((GPIO_TypeDef*)&PINA)
#define GPIOB ((GPIO_TypeDef*)&PINB)
#define GPIOC ((GPIO_TypeDef*)&PINC)
#define GPIOD ((GPIO_TypeDef*)&PIND)

typedef struct
{
	uint8_t PIN;
	uint8_t DDR;
	uint8_t PORT;
}GPIO_TypeDef;

void GPIO_InitPin(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t Mode);
void GPIO_SetPinState(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t State);
uint8_t GPIO_GetPinState(GPIO_TypeDef* GPIOx, uint8_t PINx);
void GPIO_SetPortState(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t State);
uint8_t GPIO_GetPortState(GPIO_TypeDef* GPIOx);

#endif /* GPIO_H */
