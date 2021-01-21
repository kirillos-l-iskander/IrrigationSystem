#include "LED.h"

volatile static LED_t LED_G[2];

void LED_Init(void)
{
    LED_G[0].State = 0;
    LED_G[1].State = 0;
    GPIO_InitPin(LED_REG, LED0, OUTPUT);
    GPIO_InitPin(LED_REG, LED1, OUTPUT);
}

void LED_Update(void)
{
    GPIO_SetPinState(LED_REG, LED0, LED_G[0].State);
    GPIO_SetPinState(LED_REG, LED1, LED_G[1].State);
}

void LED_SetState(uint8_t LEDx, uint8_t State)
{
    switch(LEDx)
    {
        case LED0:
            LED_G[0].State = State;
            break;
        case LED1:
            LED_G[1].State = State;
            break;
    }
}
