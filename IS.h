#ifndef IS_H
#define IS_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "LCD.h"
#include "IS.h"

#define LED_UPDATE 1
#define IS_UPDATE 10
#define LCD_UPDATE 5

void IS_Update(void);

#endif /* IS_H */
