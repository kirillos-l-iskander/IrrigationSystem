#ifndef LCD_H
#define	LCD_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "LCD.h"
#include "IS.h"

#define ROW_NUM 4
#define COL_NUM 16

#define CLEAR_DISPLAY (0x01)
#define RETURN_HOME (0x02)
#define INCREMENT_CURSOR (0x06)
#define DISPLAY_ON_CURSOR_OFF (0x0C)
#define DISPLAY_2_LINES_5x7_MATRIX_4_BIT (0x28)
#define DISPLAY_2_LINES_5x7_MATRIX_8_BIT (0x38)
#define FORCE_CURSOR_HOME (0x80)

void LCD_Init(void);
void LCD_Update(void);
void LCD_SendCommand(uint8_t Comm);
void LCD_SendCharacter(uint8_t Char);
void LCD_SendString(uint8_t* Str_P);
void LCD_SetCursor(uint8_t Row, uint8_t Col);
void LCD_Clear(void);
void LCD_SetCharacterBuffer(uint8_t Char, uint8_t Row, uint8_t Col);
void LCD_SetStringBuffer(uint8_t* Str_P, uint8_t Row, uint8_t Col);
void LCD_ClearBuffer(void);

#endif	/* LCD_H */
