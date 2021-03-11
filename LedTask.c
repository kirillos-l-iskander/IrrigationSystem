#include "LedTask.h"

typedef struct
{
	uint8_t State;
	uint8_t Blink;
	uint16_t Period;
	uint16_t Delay;
}LedTask_t;

static LedTask_t LedTask[ LED_TASK_NUMBER ];

void LedTask_Init( void )
{
	size_t Id = 0;
	for ( Id = 0; Id < LED_TASK_NUMBER; Id++ )
	{
		LedTask[ Id ].State = LOW;
		LedTask[ Id ].Blink = 0;
		LedTask[ Id ].Period = 0;
		LedTask[ Id ].Delay = 0;
	}
	Led_Init();
}

void LedTask_SetState( Id_t Id, uint8_t State, uint16_t Period )
{
	LedTask[ Id ].State = State;
	LedTask[ Id ].Period = C_MS_TO_TICKS( Period ) / C_MS_TO_TICKS( 100 );
}

void LedTask_Update( void *Paramter )
{
	size_t Id = 0;
	for ( Id = 0; Id < LED_TASK_NUMBER; Id++ )
	{
		if( LedTask[ Id ].Delay )
		{
			LedTask[ Id ].Delay--;
		}else if( LedTask[ Id ].Period )
		{
			LedTask[ Id ].Blink ^= LedTask[ Id ].State;
			LedTask[ Id ].Delay = LedTask[ Id ].Period;
		}else
		{
			LedTask[ Id ].Blink = 0;
		}
		Led_SetState( Id, !( LedTask[ Id ].State & !LedTask[ Id ].Blink ) );
	}
}
