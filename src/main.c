#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "bsp/nano.h"
#include "utils/delay.h"
#define BUTTON D2
#define LED_GREEN D9
#define LED_YELLOW D5
#define LED_RED D6
uint8_t mode = 0;
uint8_t state = 0;
void wait_button()
{
    Delay(200);
    while (GPIO_Read(BUTTON) == 0);
}
int main(void)
{
    GPIO_Init(BUTTON, GPIO_INPUT);
    GPIO_Write(BUTTON, GPIO_HIGH);
    GPIO_Init(LED_GREEN, GPIO_OUTPUT);
    GPIO_Init(LED_YELLOW, GPIO_OUTPUT);
    GPIO_Init(LED_RED, GPIO_OUTPUT);
    while (1)
    {
        if (GPIO_Read(BUTTON) == 0)
        {
            mode = !mode;
            wait_button();
        }
        GPIO_Write(LED_GREEN, GPIO_LOW);
        GPIO_Write(LED_YELLOW, GPIO_LOW);
        GPIO_Write(LED_RED, GPIO_LOW);
        //SEMAFOR
        if (mode == 0)
        {
            GPIO_Write(LED_GREEN, GPIO_HIGH);
            Delay(1000);
            GPIO_Write(LED_GREEN, GPIO_LOW);
            GPIO_Write(LED_YELLOW, GPIO_HIGH);
            Delay(500);
            GPIO_Write(LED_YELLOW, GPIO_LOW);
            GPIO_Write(LED_RED, GPIO_HIGH);
            Delay(1000);
            GPIO_Write(LED_RED, GPIO_LOW);
        }
        //GALBEN INTERMITENT
        else
        {
            GPIO_Write(LED_RED, GPIO_LOW);
            GPIO_Write(LED_GREEN, GPIO_LOW);
            GPIO_Write(LED_YELLOW, GPIO_HIGH);
            Delay(500);
            GPIO_Write(LED_YELLOW, GPIO_LOW);
            Delay(100);
        }
    }
}