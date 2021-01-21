#include "GPIO.h"

void GPIO_InitPin(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t Mode)
{
	GPIOx->DDR = (GPIOx->DDR & ~(1<<PINx)) | (Mode<<PINx);
}

void GPIO_SetPinState(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t State)
{
	GPIOx->PORT = (GPIOx->PORT & ~(1<<PINx)) | (State<<PINx);
}

uint8_t GPIO_GetPinState(GPIO_TypeDef* GPIOx, uint8_t PINx)
{
	return (GPIOx->PIN & (1<<PINx))>>PINx;
}

void GPIO_SetPortState(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t State)
{
	GPIOx->PORT = (GPIOx->PORT & ~PINx) | (State & PINx);
}

uint8_t GPIO_GetPortState(GPIO_TypeDef* GPIOx)
{
	return GPIOx->PIN;
}
