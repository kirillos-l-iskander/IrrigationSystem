#include "LcdTask.h"

typedef struct
{
	uint8_t Buffer[ LCD_ROW_NUMBER ][ LCD_COL_NUMBER ];
	uint8_t ReadingRowIndex;
	uint8_t ReadingColumnIndex;
}LcdTask_t;

static LcdTask_t LcdTask[ LCD_TASK_NUMBER ];

void LcdTask_Init( void )
{
	size_t Id = 0;
	for ( Id = 0; Id < LCD_TASK_NUMBER; Id++ )
	{
		LcdTask_Clear( Id );
		LcdTask[ Id ].ReadingRowIndex = 0;
		LcdTask[ Id ].ReadingColumnIndex = 0;
	}
	Lcd_Init();
}

void LcdTask_SetCharacter( Id_t Id, uint8_t Character, uint8_t Row, uint8_t Col )
{
	LcdTask[ Id ].Buffer[ Row ][ Col ] = Character;
}

void LcdTask_SetString( Id_t Id, uint8_t* pString, uint8_t Row, uint8_t Col )
{
	size_t Index = 0;
	for( Index = 0; pString[ Index ] != 0; Index++ )
	{
		LcdTask[ Id ].Buffer[ Row ][ Col ] = pString[ Index ];
		Col++;
		if( Col == LCD_COL_NUMBER )
		{
			Col = 0;
			Row++;
			if( Row == LCD_ROW_NUMBER )
			{
					Row = 0;
			}
		}
	}
}

void LcdTask_Clear( Id_t Id )
{
	uint8_t Row = 0;
	uint8_t Col = 0;
	for( ; ; )
	{
		LcdTask[ Id ].Buffer[ Row ][ Col ] = ' ';
		Col++;
		if( Col == LCD_COL_NUMBER )
		{
			Col = 0;
			Row++;
			if( Row == LCD_ROW_NUMBER )
			{
				break;
			}
		}
	}
}

void LcdTask_Update( void *Paramter )
{
	size_t Id = 0;
	for ( Id = 0; Id < LCD_TASK_NUMBER; Id++ )
	{
		Lcd_SetCursor( Id, LcdTask[ Id ].ReadingRowIndex, LcdTask[ Id ].ReadingColumnIndex );
		Lcd_SetCharacter( Id, LcdTask[ Id ].Buffer[ LcdTask[ Id ].ReadingRowIndex ][ LcdTask[ Id ].ReadingColumnIndex ] );
		LcdTask[ Id ].ReadingColumnIndex++;
		if( LcdTask[ Id ].ReadingColumnIndex == LCD_COL_NUMBER )
		{
				LcdTask[ Id ].ReadingColumnIndex = 0;
				LcdTask[ Id ].ReadingRowIndex++;
				if( LcdTask[ Id ].ReadingRowIndex == LCD_ROW_NUMBER )
				{
						LcdTask[ Id ].ReadingRowIndex = 0;
				}
		}
	}
}
