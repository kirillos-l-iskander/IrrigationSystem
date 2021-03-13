#include "Timer.h"

static void Timer0_init( uint8_t tickNumber );
static void Timer1_init( uint16_t tickNumber );
static void Timer2_init( uint8_t tickNumber );
static void Timer0_initPwm( void );
static void Timer1_initPwm( void );
static void Timer2_initPwm( void );
static void Timer0_setPwmDutyCycle( uint8_t pwmDutyCycle );
static void Timer1_setPwmDutyCycle( uint16_t pwmDutyCycle );
static void Timer2_setPwmDutyCycle( uint8_t pwmDutyCycle );
static uint8_t Timer0_getPwmDutyCycle( void );
static uint16_t Timer1_getPwmDutyCycle( void );
static uint8_t Timer2_getPwmDutyCycle( void );

void Timer_init( Id_t id, Timer_t tickNumber )
{
	switch( id )
	{
		case 0:
			Timer0_init( ( uint8_t ) tickNumber );
			break;
		case 1:
			Timer1_init( ( uint16_t ) tickNumber );
			break;
		case 2:
			Timer2_init( ( uint8_t ) tickNumber );
			break;
		default:
			return;
		}
}

void Timer_initPwm( Id_t id )
{
	switch( id )
	{
		case 0:
			Timer0_initPwm();
			break;
		case 1:
			Timer1_initPwm();
			break;
		case 2:
			Timer2_initPwm();
			break;
		default:
			return;
	}
}

void Timer_setPwmDutyCycle( Id_t id, Timer_t pwmDutyCycle )
{
	switch( id )
	{
		case 0:
			Timer0_setPwmDutyCycle( ( uint8_t ) pwmDutyCycle );
			break;
		case 1:
			Timer1_setPwmDutyCycle( ( uint16_t ) pwmDutyCycle );
			break;
		case 2:
			Timer2_setPwmDutyCycle( ( uint8_t ) pwmDutyCycle );
			break;
		default:
			return;
		}
}

Timer_t Timer_getPwmDutyCycle( Id_t id )
{
	switch( id )
	{
		case 0:
			return Timer0_getPwmDutyCycle();
			break;
		case 1:
			return Timer1_getPwmDutyCycle();
			break;
		case 2:
			return Timer2_getPwmDutyCycle();
			break;
		default:
			return 0;
		}
}

void Timer0_init( uint8_t tickNumber )
{
	//OC0 Normal Port Operation
	//TIM0 CTC mode, OCR0 Top
	//Prescaler CPU_F/64
	TCCR0 = 0x8B;

	//Counter Value
	TCNT0 = 0;

	//Compare Value
	OCR0 = tickNumber;

	//OC0 Interrupt
	TIMSK = TIMSK | 0x02;
	//Set Timer0 overflow interrupt
	//TIMSK = TIMSK | 0x01;
}

void Timer1_init( uint16_t tickNumber )
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
	OCR1AH = tickNumber >> 8;
	OCR1AL = tickNumber;
	//OCR1B = 0;

	//OC1A Interrupt
	//TIMSK = TIMSK | 1<<TICIE1;
	TIMSK = TIMSK | ( 1 << 4 );
	//TIMSK = TIMSK | 1<<OCIE1B;
	//TIMSK = TIMSK | 1<<TOIE1;
}

void Timer2_init( uint8_t tickNumber )
{
	//OC2 Normal Port Operation
	//TIM2 CTC mode, OCR2 Top
	//Prescaler CPU_F/8
	TCCR2 = 0x8A;

	//Counter Value
	TCNT2 = 0;

	//Compare Value
	OCR2 = tickNumber;

	//OC2 Interrupt
	TIMSK = TIMSK | 0x80;
	//Set Timer2 overflow interrupt
	//TIMSK = pxTimerHandle->TIMSK | 0x40;
}

void Timer0_initPwm( void )
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR0 = 0x6C;
}

void Timer1_initPwm( void )
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR1A = 0xA1;
	TCCR1B = 0x0C;
}

void Timer2_initPwm( void )
{
	//Fast PWM Mode
	//None-inverting Mode
	//Prescaler CPU_F/256
	TCCR2 = 0x6E;
}

void Timer0_setPwmDutyCycle( uint8_t pwmDutyCycle )
{
	//PWM DutyCycle from 0 to 255
	OCR0 = pwmDutyCycle;
}

void Timer1_setPwmDutyCycle( uint16_t pwmDutyCycle )
{
	//PWM DutyCycle from 0 to 255
	OCR1AH = pwmDutyCycle >> 8;
	OCR1AL = pwmDutyCycle;
}

void Timer2_setPwmDutyCycle( uint8_t pwmDutyCycle )
{
	//PWM DutyCycle from 0 to 255
	OCR2 = pwmDutyCycle;
}

uint8_t Timer0_getPwmDutyCycle( void )
{
	return OCR0;
}

uint16_t Timer1_getPwmDutyCycle( void )
{
	return ( ( OCR1AH << 8 ) + OCR1AL );
}

uint8_t Timer2_getPwmDutyCycle( void )
{
	return OCR2;
}
