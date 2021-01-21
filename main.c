#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "LCD.h"
#include "IS.h"

int main(void)
{
	SCH_Init();
	LED_Init();
	LCD_Init();
	TIM0_InitPWM0();
	SCH_Add_Task(LED_Update, 0/SCH_TICK_PERIOD_MS, LED_UPDATE/SCH_TICK_PERIOD_MS);
	SCH_Add_Task(IS_Update, 1/SCH_TICK_PERIOD_MS, IS_UPDATE/SCH_TICK_PERIOD_MS);
	SCH_Add_Task(LCD_Update, 2/SCH_TICK_PERIOD_MS, LCD_UPDATE/SCH_TICK_PERIOD_MS);
	SCH_Start();
	while(1)
	{
		SCH_Dispatch_Tasks();
	}
	return RETURN_NORMAL;
}
