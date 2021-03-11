#include "Timer.h"

static void Timer0Init( uint8_t TicksNumber );
static void Timer1Init( uint16_t TicksNumber );
static void Timer2Init( uint8_t TicksNumber );
static void Timer0InitPwm( void );
static void Timer1InitPwm( void );
static void Timer2InitPwm( void );
static void Timer0SetPwmDutyCycle( uint8_t DutyCycle );
static void Timer1SetPwmDutyCycle( uint16_t DutyCycle );
static void Timer2SetPwmDutyCycle( uint8_t DutyCycle );
static uint8_t Timer0GetPwmDutyCycle( void );
static uint16_t Timer1GetPwmDutyCycle( void );
static uint8_t Timer2GetPwmDutyCycle( void );

void Timer_Init( Id_t Id, Timer_t TicksNumber )
{
	switch( Id )
	{
		case 0:
			Timer0Init( ( uint8_t ) TicksNumber );
			break;
		case 1:
			Timer1Init( ( uint16_t ) TicksNumber );
			break;
		case 2:
			Timer2Init( ( uint8_t ) TicksNumber );
			break;
		default:
			return;
		}
}

void Timer_InitPwm( Id_t Id )
{
	switch( Id )
	{
		case 0:
			Timer0InitPwm();
			break;
		case 1:
			Timer1InitPwm();
			break;
		case 2:
			Timer2InitPwm();
			break;
		default:
			return;
	}
}

void Timer_SetPwmDutyCycle( Id_t Id, Timer_t DutyCycle )
{
	switch( Id )
	{
		case 0:
			Timer0SetPwmDutyCycle( ( uint8_t ) DutyCycle );
			break;
		case 1:
			Timer1SetPwmDutyCycle( ( uint16_t ) DutyCycle );
			break;
		case 2:
			Timer2SetPwmDutyCycle( ( uint8_t ) DutyCycle );
			break;
		default:
			return;
		}
}

Timer_t Timer_GetPwmDutyCycle( Id_t Id )
{
	switch( Id )
	{
		case 0:
			return Timer0GetPwmDutyCycle();
			break;
		case 1:
			return Timer1GetPwmDutyCycle();
			break;
		case 2:
			return Timer2GetPwmDutyCycle();
			break;
		default:
			return 0;
		}
}

void Timer0Init( uint8_t TicksNumber )
{
	//OC0 Normal Port Operation
	//TIM0 CTC mode, OCR0 Top
	//Prescaler CPU_F/64
	TCCR0 = 0x8B;

	//Counter Value
	TCNT0 = 0;

	//Compare Value
	OCR0 = TicksNumber;

	//OC0 Interrupt
	TIMSK = TIMSK | 0x02;
	//Set Timer0 overflow interrupt
	//TIMSK = TIMSK | 0x01;
}

void Timer1Init( uint16_t TicksNumber )
{
	//OC1A, OC1B Normal Port Operation
	//TIM1 CTC mode, OCR1A Top
	//Prescaler CPU_F/1
	TCCR1A = 0x00;
	TCCR1B = 0x0A;

	//TIM1 Value
	TCNT1H = 0;
	TCNT1L = 0;

	//Compare Match Value
	//ICR1 = 0;
	OCR1AH = TicksNumber >> 8;
	OCR1AL = TicksNumber;
	//OCR1B = 0;

	//OC1A Interrupt
	//TIMSK = TIMSK | 1<<TICIE1;
	TIMSK = TIMSK | ( 1 << 4 );
	//TIMSK = TIMSK | 1<<OCIE1B;
	//TIMSK = TIMSK | 1<<TOIE1;
}

void Timer2Init( uint8_t TicksNumber )
{
	//OC2 Normal Port Operation
	//TIM2 CTC mode, OCR2 Top
	//Prescaler CPU_F/8
	TCCR2 = 0x8A;

	//Counter Value
	TCNT2 = 0;

	//Compare Value
	OCR2 = TicksNumber;

	//OC2 Interrupt
	TIMSK = TIMSK | 0x80;
	//Set Timer2 overflow interrupt
	//TIMSK = pxTimerHandle->TIMSK | 0x40;
}

void Timer0InitPwm( void )
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR0 = 0x6C;
}

void Timer1InitPwm( void )
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR1A = 0xA1;
	TCCR1B = 0x0C;
}

void Timer2InitPwm( void )
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR2 = 0x6E;
}

void Timer0SetPwmDutyCycle( uint8_t DutyCycle )
{
	//PWM DutyCycle from 0 to 255
	OCR0 = DutyCycle;
}

void Timer1SetPwmDutyCycle( uint16_t DutyCycle )
{
	//PWM DutyCycle from 0 to 255
	OCR1AH = DutyCycle >> 8;
	OCR1AL = DutyCycle;
}

void Timer2SetPwmDutyCycle( uint8_t DutyCycle )
{
	//PWM DutyCycle from 0 to 255
	OCR2 = DutyCycle;
}

uint8_t Timer0GetPwmDutyCycle( void )
{
	return OCR0;
}

uint16_t Timer1GetPwmDutyCycle( void )
{
	return ( ( OCR1AH << 8 ) + OCR1AL );
}

uint8_t Timer2GetPwmDutyCycle( void )
{
	return OCR2;
}
