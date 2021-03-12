#include "Lcd.h"

typedef struct
{
	Id_t GpioIdRs;
	uint8_t PinRs;
	Id_t GpioIdRw;
	uint8_t PinRw;
	Id_t GpioIdE;
	uint8_t PinE;
	Id_t GpioIdD0;
	uint8_t PinD0;
}Lcd_t;

static Lcd_t Lcd[ LCD_NUMBER ];
static uint8_t Lcd_RowAddress[ 4 ] = { 0x80, 0xC0, 0x90, 0xD0 };

void Lcd_Init( Id_t Id, Id_t rsGpioId, uint8_t rsPin, Id_t eGpioId, uint8_t ePin, Id_t d0GpioId, uint8_t d0Pin )
{
	size_t Pin = 0;
	Lcd[ Id ].GpioIdRs = rsGpioId;
	Lcd[ Id ].PinRs = rsPin;
	Lcd[ Id ].GpioIdE = eGpioId;
	Lcd[ Id ].PinE = ePin;
	Lcd[ Id ].GpioIdD0 = d0GpioId;
	Lcd[ Id ].PinD0 = d0Pin;
	Gpio_InitPin( Lcd[ Id ].GpioIdRs, Lcd[ Id ].PinRs, OUTPUT );
	Gpio_InitPin( Lcd[ Id ].GpioIdE, Lcd[ Id ].PinE, OUTPUT );
	for ( Pin = Lcd[ Id ].PinD0; Pin < ( Lcd[ Id ].PinD0 + 8 ); Pin++ )
	{
		Gpio_InitPin( Lcd[ Id ].GpioIdD0, Pin, OUTPUT );
	}
	Lcd_SetCommand( Id, RETURN_HOME );
	DELAY_US( 100 );
	Lcd_SetCommand( Id, DISPLAY_2_LINES_5x7_MATRIX_8_BIT );
	DELAY_US( 100 );
	Lcd_SetCommand( Id, DISPLAY_ON_CURSOR_OFF );
	Lcd_SetCommand( Id, INCREMENT_CURSOR );
	DELAY_US( 100 );
	Lcd_Clear( Id );
}

void Lcd_SetCommand( Id_t Id, uint8_t Command )
{
	Gpio_SetPortState( Lcd[ Id ].GpioIdD0, ( 0xFF << Lcd[ Id ].PinD0 ), Command );
	Gpio_SetPinState( Lcd[ Id ].GpioIdRs, Lcd[ Id ].PinRs, LOW );
	Gpio_SetPinState( Lcd[ Id ].GpioIdE, Lcd[ Id ].PinE, HIGH );
	DELAY_US( 1 );
	Gpio_SetPinState( Lcd[ Id ].GpioIdE, Lcd[ Id ].PinE, LOW );
	DELAY_US( 50 );
}

void Lcd_SetCharacter( Id_t Id, uint8_t Character )
{
	Gpio_SetPortState( Lcd[ Id ].GpioIdD0, ( 0xFF << Lcd[ Id ].PinD0 ), Character );
	Gpio_SetPinState( Lcd[ Id ].GpioIdRs, Lcd[ Id ].PinRs, HIGH );
	Gpio_SetPinState( Lcd[ Id ].GpioIdE, Lcd[ Id ].PinE, HIGH );
	DELAY_US( 1 );
	Gpio_SetPinState( Lcd[ Id ].GpioIdE, Lcd[ Id ].PinE, LOW );
}

void Lcd_SetString( Id_t Id, uint8_t* pString )
{
	size_t Index = 0;
	for( Index = 0; pString[ Index ] != 0; Index++ )
	{
		Lcd_SetCharacter( Id, pString[ Index ] );
	}
}

void Lcd_SetCursor( Id_t Id, uint8_t Row, uint8_t Col )
{
	Lcd_SetCommand( Id, Lcd_RowAddress[ Row ] | Col );
}

void Lcd_Clear( Id_t Id )
{
	Lcd_SetCommand( Id, CLEAR_DISPLAY );
	Lcd_SetCommand( Id, FORCE_CURSOR_HOME );
	DELAY_US( 2000 );
}
