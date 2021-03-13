#ifndef CONFIG_H
#define CONFIG_H

//--------------------------------------------------------------------------------------------------------------------

#include "SchedulerConfig.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//--------------------------------------------------------------------------------------------------------------------
#define SERG ( * ( uint8_t * ) ( 0x20 + 0x3F ) )
#define GIE() sei()
#define GID() cli()
//--------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------
typedef uint8_t					Id_t;
#define LED_NUMBER				( 1 )
#define LCD_NUMBER				( 1 )
#define LCD_ROW_NUMBER			( 4 )
#define LCD_COL_NUMBER			( 16 )
#define SOIL_SENSOR_NUMBER		( 1 )
#define WATER_SENSOR_NUMBER		( 1 )
#define MOTOR_NUMBER			( 1 )
#define IRRIGATION_NUMBER		( 1 )
//--------------------------------------------------------------------------------------------------------------------

//LED---------------------
#define LED0_GPIO		( GPIOD_ID )
#define LED0_PIN		( 7 )
//LED---------------------

//LCD---------------------
#define LCD0_GPIO_RS		( GPIOD_ID )
#define PIN_RS				( 2 )	//0 -> command, 1 -> data
#define LCD0_GPIO_RW		( GPIOD_ID )
#define PIN_RW				( 0 )	//0 -> write, 1 -> read
#define LCD0_GPIO_E			( GPIOD_ID )
#define PIN_E				( 3 )	//0 -> disable LCD, 1 -> enable LCD

#define LCD0_GPIO_D0		( GPIOC_ID )
#define PIN_D0				( 0 )
#define LCD0_GPIO_D1		( GPIOC_ID )
#define PIN_D1				( 1 )
#define LCD0_GPIO_D2		( GPIOC_ID )
#define PIN_D2				( 2 )
#define LCD0_GPIO_D3		( GPIOC_ID )
#define PIN_D3				( 3 )
#define LCD0_GPIO_D4		( GPIOC_ID )
#define PIN_D4				( 4 )
#define LCD0_GPIO_D5		( GPIOC_ID )
#define PIN_D5				( 5 )
#define LCD0_GPIO_D6		( GPIOC_ID )
#define PIN_D6				( 6 )
#define LCD0_GPIO_D7		( GPIOC_ID )
#define PIN_D7				( 7 )
//LCD---------------------

//SOIL_SENSOR---------------------
#define SOILSENSOR0_GPIO		( GPIOA_ID )
#define SOILSENSOR0_PIN			( 0 )
//SOIL_SENSOR---------------------

//WATER_SENSOR---------------------
#define WATERSENSOR0_GPIO		( GPIOA_ID )
#define WATERSENSOR0_PIN		( 1 )
//WATER_SENSOR---------------------

//MOTOR---------------------
#define MOTOR0_GPIO		( GPIOB_ID )
#define MOTOR0_PIN		( 3 )
#define MOTOR0_TIMER	( TIMER0_ID )
//MOTOR---------------------

#endif /* CONFIG_H */
