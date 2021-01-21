#include "TIM.h"

void TIM0_Init(void)
{
	//OC0 Normal Port Operation
	//TIM0 CTC mode, OCR0 Top
	//Prescaler CPU_F/64
	TCCR0 = TCCR0 | (0x8B);
	//Counter Value
	TCNT0 = 0;
	//Compare Value
	OCR0 = 0;
	//OC0 Interrupt
	TIMSK = TIMSK | 0x02;
	//Set Timer0 overflow interrupt
	//TIMSK = TIMSK | 0x01;
}

void TIM1_Init(uint16_t Ticks_N)
{
	//OC1A, OC1B Normal Port Operation
	//TIM1 CTC mode, OCR1A Top
	//Prescaler CPU_F/1
	TCCR1A = 0x00;
	TCCR1B = 0x09;
	//TIM1 Value
	TCNT1 = 0;
	//Compare Match Value
	//ICR1 = 0;
	OCR1A = Ticks_N;
	//OCR1B = 0;
	//OC1A Interrupt
	//TIMSK = TIMSK | 1<<TICIE1;
	TIMSK = TIMSK | 1<<OCIE1A;
	//TIMSK = TIMSK | 1<<OCIE1B;
	//TIMSK = TIMSK | 1<<TOIE1;
}

void TIM2_Init(void)
{
	//OC2 Normal Port Operation
	//TIM2 CTC mode, OCR2 Top
	//Prescaler CPU_F/8
	TCCR2 = 0x8A;
	//Counter Value
	TCNT2 = 0;
	//Compare Value
	OCR2 = 200;
	//OC2 Interrupt
	TIMSK = TIMSK | 0x80;
	//Set Timer2 overflow interrupt
	//TIMSK = TIMSK | 0x40;
}

void TIM0_InitPWM0(void)
{
	GPIO_InitPin(GPIOB, 3, OUTPUT);
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR0 = 0x6C;
}

void TIM1_InitPWM1(void)
{
	GPIO_InitPin(GPIOD, 5, OUTPUT);
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR1A = 0xA1;
	TCCR1B = 0x0C;
}

void TIM2_InitPWM2(void)
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR2 = 0x6E;
}

void TIM0_SetPWM0DutyCycle(uint8_t DutyCycle)
{
	//PWM DutyCycle from 0 to 255 */
	OCR0 = DutyCycle;
}

void TIM1_SetPWM1ADutyCycle(uint8_t DutyCycle)
{
	//PWM DutyCycle from 0 to 255
	OCR1A = DutyCycle;
}

void TIM1_SetPWM1BDutyCycle(uint8_t DutyCycle)
{
	//PWM DutyCycle from 0 to 255
	OCR1B = DutyCycle;
}

void TIM2__SetPWM2DutyCycle(uint8_t DutyCycle)
{
	//PWM DutyCycle from 0 to 255
	OCR2 = DutyCycle;
}
