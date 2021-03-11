#ifndef LCD_H
#define	LCD_H

#include "SchedulerConfig.h"
#include "Gpio.h"

#define CLEAR_DISPLAY ( 0x01 )
#define RETURN_HOME ( 0x02 )
#define INCREMENT_CURSOR ( 0x06 )
#define DISPLAY_ON_CURSOR_OFF ( 0x0C )
#define DISPLAY_2_LINES_5x7_MATRIX_4_BIT ( 0x28 )
#define DISPLAY_2_LINES_5x7_MATRIX_8_BIT ( 0x38 )
#define FORCE_CURSOR_HOME ( 0x80 )

void Lcd_Init( void );
void Lcd_SetCommand( Id_t Id, uint8_t Command );
void Lcd_SetCharacter( Id_t Id, uint8_t Character );
void Lcd_SetString( Id_t Id, uint8_t* pString );
void Lcd_SetCursor( Id_t Id, uint8_t Row, uint8_t Col );
void Lcd_Clear( Id_t Id );
void Lcd_SetGpioRs( Id_t Id, Id_t GpioId, uint8_t Pin );
void Lcd_SetGpioE( Id_t Id, Id_t GpioId, uint8_t Pin );
void Lcd_SetGpioD0( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* LCD_H */
