#include "IS.h"

void IS_Update(void)
{
	uint8_t SoilSensor;
	uint8_t WaterSensor;
	SoilSensor = GPIO_GetPinState(GPIOA, 0);
	WaterSensor = GPIO_GetPinState(GPIOA, 1);
	LCD_ClearBuffer();
	if(SoilSensor == HIGH)
	{
		LCD_SetStringBuffer((uint8_t*)"Humidity:HIGH", 0, 0);
	}else
	{
		LCD_SetStringBuffer((uint8_t*)"Humidity:LOW", 0, 0);
	}
	if(WaterSensor == HIGH)
	{
		LCD_SetStringBuffer((uint8_t*)"Tank Level:HIGH", 1, 0);
	}else
	{
		LCD_SetStringBuffer((uint8_t*)"Tank Level:LOW", 1, 0);
		LCD_SetStringBuffer((uint8_t*)"Warning", 3, 9);
	}
	if(SoilSensor == LOW && WaterSensor == HIGH)
	{
		LCD_SetStringBuffer((uint8_t*)"Pump:ON", 2, 0);
		TIM0_SetPWM0DutyCycle(255);
	}else
	{
		LCD_SetStringBuffer((uint8_t*)"Pump:OFF", 2, 0);
		TIM0_SetPWM0DutyCycle(0);
	}
}
