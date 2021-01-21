#include "SCH_CONFIG.h"

uint8_t SysTick_Init(volatile const uint32_t TicksPeriod_ms)
{
	volatile uint32_t Ticks_N = (((CPU_F/CPU_INSTRUCTION)/1000)*TicksPeriod_ms)-1;
	if(Ticks_N < SCH_SYSTICK_MAX)
	{
		GIE();
		TIM1_Init((uint16_t)Ticks_N);
		return RETURN_NORMAL;
	}else
	{
		return RETURN_ERROR;
	}
}

ISR(TIMER1_COMPA_vect)
{
	SCH_Update();
}

void HW_Delay_ms(volatile uint32_t Delay_ms)
{

}

void HW_Delay_us(volatile uint32_t Delay_us)
{

}

void SW_Delay_ms(volatile uint32_t Delay_ms)
{
	while(Delay_ms-- > 0)
	{
		SW_Delay_us(1000);
	}
}

void SW_Delay_us(volatile uint32_t Delay_us)
{
	volatile uint8_t Delay;
	while(Delay_us-- > 0)
	{
		Delay = 255;
		while(Delay--);
	}
}
