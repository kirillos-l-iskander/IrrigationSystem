#include "Timer.h"

static uint16_t timer0Prescale[] = { 0, 1, 8, 64, 256, 1024 };
static uint16_t timer1Prescale[] = { 0, 1, 8, 64, 256, 1024 };
static uint16_t timer2Prescale[] = { 0, 1, 8, 32, 64, 128, 256, 1024 };

static void Timer0_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event );
static void Timer1_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event );
static void Timer2_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event );
static void Timer0_setPwmDutyCycle( TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle );
static void Timer1_setPwmDutyCycle( TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle );
static void Timer2_setPwmDutyCycle( TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle );
static TIMER_PWM_t Timer0_getPwmDutyCycle( TIMER_CHANNEL_t channel );
static TIMER_PWM_t Timer1_getPwmDutyCycle( TIMER_CHANNEL_t channel );
static TIMER_PWM_t Timer2_getPwmDutyCycle( TIMER_CHANNEL_t channel );

void Timer_init( TIMER_ID_t id, TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
	switch( id )
	{
		case TIMER_ID_0:
			Timer0_init( mode, period, channel, event );
			break;
		case TIMER_ID_1:
			Timer1_init( mode, period, channel, event );
			break;
		case TIMER_ID_2:
			Timer2_init( mode, period, channel, event );
			break;
		default:
			return;
		}
}

void Timer_setPwmDutyCycle( TIMER_ID_t id, TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle )
{
	switch( id )
	{
		case 0:
			Timer0_setPwmDutyCycle( channel, pwmDutyCycle );
			break;
		case 1:
			Timer1_setPwmDutyCycle( channel, pwmDutyCycle );
			break;
		case 2:
			Timer2_setPwmDutyCycle( channel, pwmDutyCycle );
			break;
		default:
			return;
		}
}

TIMER_PWM_t Timer_getPwmDutyCycle( TIMER_ID_t id, TIMER_CHANNEL_t channel )
{
	switch( id )
	{
		case 0:
			return Timer0_getPwmDutyCycle( channel );
			break;
		case 1:
			return Timer1_getPwmDutyCycle( channel );
			break;
		case 2:
			return Timer2_getPwmDutyCycle( channel );
			break;
		default:
			return 0;
		}
}

void Timer_enableInterrupt( TIMER_ID_t id )
{
	switch( id )
	{
		case TIMER_ID_0:
			TIMSK |= BV(OCIE0);
			break;
		case TIMER_ID_1:
			TIMSK |= BV(OCIE1A);
			break;
		case TIMER_ID_2:
			TIMSK |= BV(OCIE2);
			break;
		default:
			return;
		}
}

static void Timer0_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
	TCCR0 &= ~( BV(FOC0) | BV(WGM01) | BV(WGM00) );
/*
	TCCR0 |= BV(FOC0);
	TIMSK |= BV(TOIE0);
	TCNT0 = tickNumber;
*/
	switch( mode )
	{
		case TIMER_MODE_NORMAL:
		case TIMER_MODE_COUNTUP:
			if( event == TIMER_EVENT_PWM_NONINVERT || event == TIMER_EVENT_PWM_INVERT )
			{
				TCCR0 |= BV(WGM01) | BV(WGM00);
				OCR0 = 0;
			}else
			{
				TCCR0 |= BV(FOC0) | BV(WGM01);
			}
			break;
		default:
			break;
	}

	TCCR0 &= ~( BV(COM01) | BV(COM00) );
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			TCCR0 &= ~( BV(COM01) | BV(COM00) );
			break;
		case TIMER_CHANNEL_1:
			switch( event )
			{
				case TIMER_EVENT_NORMAL:
					TCCR0 &= ~( BV(COM01) | BV(COM00) );
					break;
				case TIMER_EVENT_COMPARE_TOGGLE:
					TCCR0 |=  BV(COM00);
					break;
				case TIMER_EVENT_COMPARE_RESET:
				case TIMER_EVENT_PWM_NONINVERT:
					TCCR0 |= BV(COM01);
					break;
				case TIMER_EVENT_COMPARE_SET:
				case TIMER_EVENT_PWM_INVERT:
					TCCR0 |= BV(COM01) | BV(COM00);
					break;
				default:
					break;
			}
			break;
		case TIMER_CHANNEL_2:
			break;
		default:
			break;
	}

	for( size_t prescale = 1; prescale < 6; prescale++)
	{
		uint16_t tickNumber = ( uint16_t ) ( ( ( ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / timer0Prescale[ prescale ] ) / 1000 ) * period ) - 1 );
		if( tickNumber < UINT8_MAX )
		{
			OCR0 = ( uint8_t ) tickNumber;
			TCCR0 &= ~( BV(CS02) | BV(CS01) | BV(CS00) );
			TCCR0 |= prescale;
			break;
		}
	}
}

static void Timer1_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
	TCCR1A &= ~( BV(FOC1B) | BV(FOC1A) | BV(WGM11) | BV(WGM10) );
	TCCR1B &= ~( BV(WGM13) | BV(WGM12) );
/*
	TCCR1A |= BV(FOC1B) | BV(FOC1A);
	TIMSK |= BV(TOIE1);
	TCNT1 = tickNumber;
 */
	switch( mode )
	{
		case TIMER_MODE_NORMAL:
		case TIMER_MODE_COUNTUP:
			if( event == TIMER_EVENT_PWM_NONINVERT || event == TIMER_EVENT_PWM_INVERT )
			{
				TCCR1A |= BV(WGM11);
				TCCR1B |= BV(WGM13) | BV(WGM12);
				OCR1A = 0;
				OCR1B = 0;
			}else
			{
				TCCR1A |= BV(FOC1B) | BV(FOC1A);
				TCCR1B |= BV(WGM12);
			}
			break;
		default:
			break;
	}

	TCCR1A &= ~( BV(COM1A1) | BV(COM1A0) );
	TCCR1A &= ~( BV(COM1B1) | BV(COM1B0) );
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			TCCR1A &= ~( BV(COM1A1) | BV(COM1A0) );
			TCCR1A &= ~( BV(COM1B1) | BV(COM1B0) );
			break;
		case TIMER_CHANNEL_1:
			switch( event )
			{
				case TIMER_EVENT_NORMAL:
					break;
				case TIMER_EVENT_COMPARE_TOGGLE:
					TCCR1A |=  BV(COM1A0);
					break;
				case TIMER_EVENT_COMPARE_RESET:
				case TIMER_EVENT_PWM_NONINVERT:
					TCCR1A |= BV(COM1A1);
					break;
				case TIMER_EVENT_COMPARE_SET:
				case TIMER_EVENT_PWM_INVERT:
					TCCR1A |= BV(COM1A1) | BV(COM1A0);
					break;
				default:
					break;
			}
			break;
		case TIMER_CHANNEL_2:
			switch( event )
			{
				case TIMER_EVENT_NORMAL:
					break;
				case TIMER_EVENT_COMPARE_TOGGLE:
					TCCR1A |=  BV(COM1B0);
					break;
				case TIMER_EVENT_COMPARE_RESET:
				case TIMER_EVENT_PWM_NONINVERT:
					TCCR1A |= BV(COM1B1);
					break;
				case TIMER_EVENT_COMPARE_SET:
				case TIMER_EVENT_PWM_INVERT:
					TCCR1A |= BV(COM1B1) | BV(COM1B0);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	for( size_t prescale = 1; prescale < 6; prescale++)
	{
		uint32_t tickNumber = ( uint32_t ) ( ( ( ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / timer1Prescale[ prescale ] ) / 1000 ) * period ) - 1 );
		if( tickNumber < UINT16_MAX )
		{
			ICR1 = ( uint16_t ) tickNumber;
			OCR1A = ( uint16_t ) tickNumber;
			OCR1B = ( uint16_t ) tickNumber;
			TCCR1B &= ~( BV(CS12) | BV(CS11) | BV(CS10) );
			TCCR1B |= prescale;
			break;
		}
	}
}

static void Timer2_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
	TCCR2 &= ~( BV(FOC2) | BV(WGM21) | BV(WGM20) );
/*
	TCCR2 |= BV(FOC2);
	TIMSK |= BV(TOIE2);
	TCNT2 = tickNumber;
*/
	switch( mode )
	{
		case TIMER_MODE_NORMAL:
		case TIMER_MODE_COUNTUP:
			if( event == TIMER_EVENT_PWM_NONINVERT || event == TIMER_EVENT_PWM_INVERT )
			{
				TCCR2 |= BV(WGM21) | BV(WGM20);
				OCR2 = 0;
			}else
			{
				TCCR2 |= BV(FOC2) | BV(WGM21);
			}
			break;
		default:
			break;
	}

	TCCR2 &= ~( BV(COM21) | BV(COM20) );
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			TCCR2 &= ~( BV(COM21) | BV(COM20) );
			break;
		case TIMER_CHANNEL_1:
			switch( event )
			{
				case TIMER_EVENT_NORMAL:
					break;
				case TIMER_EVENT_COMPARE_TOGGLE:
					TCCR2 |=  BV(COM20);
					break;
				case TIMER_EVENT_COMPARE_RESET:
				case TIMER_EVENT_PWM_NONINVERT:
					TCCR2 |= BV(COM21);
					break;
				case TIMER_EVENT_COMPARE_SET:
				case TIMER_EVENT_PWM_INVERT:
					TCCR2 |= BV(COM21) | BV(COM20);
					break;
				default:
					break;
			}
			break;
		case TIMER_CHANNEL_2:
			break;
		default:
			break;
	}

	for( size_t prescale = 1; prescale < 8; prescale++)
	{
		uint16_t tickNumber = ( uint16_t ) ( ( ( ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / timer2Prescale[ prescale ] ) / 1000 ) * period ) - 1 );
		if( tickNumber < UINT8_MAX )
		{
			OCR0 = ( uint8_t ) tickNumber;
			TCCR2 &= ~( BV(CS22) | BV(CS21) | BV(CS20) );
			TCCR2 |= prescale;
			break;
		}
	}
}

void Timer0_setPwmDutyCycle( TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle )
{
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			break;
		case TIMER_CHANNEL_1:
			OCR0 = (uint8_t) ( (float) pwmDutyCycle / 100 * 255 );
			break;
		case TIMER_CHANNEL_2:
			break;
		default:
			break;
	}
}

void Timer1_setPwmDutyCycle( TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle )
{
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			break;
		case TIMER_CHANNEL_1:
			OCR1AH = (uint8_t) ( (uint16_t) ( (float) pwmDutyCycle / 100 * 65535 ) >> 8 );
			OCR1AL = (uint8_t) ( (uint16_t) ( (float) pwmDutyCycle / 100 * 65535 ) );
			break;
		case TIMER_CHANNEL_2:
			OCR1BH = (uint8_t) ( (uint16_t) ( (float) pwmDutyCycle / 100 * 65535 ) >> 8 );
			OCR1BL = (uint8_t) ( (uint16_t) ( (float) pwmDutyCycle / 100 * 65535 ) );
			break;
		default:
			break;
	}
}

void Timer2_setPwmDutyCycle( TIMER_CHANNEL_t channel, TIMER_PWM_t pwmDutyCycle )
{
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			break;
		case TIMER_CHANNEL_1:
			OCR2 = (uint8_t) ( (float) pwmDutyCycle / 100 * 255 );
			break;
		case TIMER_CHANNEL_2:
			break;
		default:
			break;
	}
}

TIMER_PWM_t Timer0_getPwmDutyCycle( TIMER_CHANNEL_t channel )
{
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			break;
		case TIMER_CHANNEL_1:
			return (TIMER_PWM_t) ( (float) OCR0 / 255 * 100 );
			break;
		case TIMER_CHANNEL_2:
			break;
		default:
			break;
	}
	return 0;
}

TIMER_PWM_t Timer1_getPwmDutyCycle( TIMER_CHANNEL_t channel )
{
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			break;
		case TIMER_CHANNEL_1:
			return (TIMER_PWM_t) ( (float) ( ( OCR1AH << 8 ) + OCR1AL ) / 65535 * 100 );
			break;
		case TIMER_CHANNEL_2:
			return (TIMER_PWM_t) ( (float) ( ( OCR1BH << 8 ) + OCR1BL ) / 65535 * 100 );
			break;
		default:
			break;
	}
	return 0;
}

TIMER_PWM_t Timer2_getPwmDutyCycle( TIMER_CHANNEL_t channel )
{
	switch( channel )
	{
		case TIMER_CHANNEL_NORMAL:
			break;
		case TIMER_CHANNEL_1:
			return (TIMER_PWM_t) ( (float) OCR2 / 255 * 100 );
			break;
		case TIMER_CHANNEL_2:
			break;
		default:
			break;
	}
	return 0;
}
