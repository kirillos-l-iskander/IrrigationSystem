#ifndef PORT_H
#define PORT_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "LED.h"

#include "GPIO.h"

//LED---------------------
#define LED_REG (GPIOD)
#define LED0 (7)
#define LED1 (6)
//LED---------------------

//LCD---------------------
#define LCD_COM_REG (GPIOD)
#define RS (2)	//0 -> command, 1 -> data
//#define RW (0)	//0 -> write, 1 -> read
#define E (3)	//0 -> disable LCD, 1 -> enable LCD

#define LCD_DAT_REG (GPIOC)
#define D0 (0)
#define D1 (1)
#define D2 (2)
#define D3 (3)
#define D4 (4)
#define D5 (5)
#define D6 (6)
#define D7 (7)
#define DPINS (0xFF)
//LCD---------------------

#endif /* PORT_H */
