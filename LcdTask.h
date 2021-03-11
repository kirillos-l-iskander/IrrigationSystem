#ifndef LCD_TASK_H
#define	LCD_TASK_H

#include "SchedulerConfig.h"
#include "Lcd.h"

void LcdTask_Init( void );
void LcdTask_SetCharacter( Id_t Id, uint8_t Character, uint8_t Row, uint8_t Col );
void LcdTask_SetString( Id_t Id, uint8_t* pString, uint8_t Row, uint8_t Col );
void LcdTask_Clear( Id_t Id );
void LcdTask_Update( void *Paramter );

#endif	/* LCD_TASK_H */
