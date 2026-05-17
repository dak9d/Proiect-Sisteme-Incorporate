#include <stdint.h>
#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "drivers/adc/adc.h"
#include "bsp/nano.h"
#include "utils/delay.h"

#define LED_GREEN   D11
#define LED_YELLOW  D9
#define LED_RED     D10
#define BUZZER D6
#define TEMP_CHANNEL 0

uint16_t temp_value;

// praguri
#define COLD_THRESHOLD   500
#define HOT_THRESHOLD    560

int main(void)
{
    ADC_Init();
    GPIO_Init(BUZZER, GPIO_OUTPUT);
    PWM_Init(LED_GREEN, 1000);
    PWM_Init(LED_YELLOW, 1000);
    PWM_Init(LED_RED, 1000);

    while(1)
    {
        temp_value = ADC_Read(TEMP_CHANNEL);
        GPIO_Write(BUZZER, 0);
        PWM_SetDutyCycle(LED_GREEN, 0);
        PWM_SetDutyCycle(LED_YELLOW, 0);
        PWM_SetDutyCycle(LED_RED, 0);

        if(temp_value < COLD_THRESHOLD)
        {
            PWM_SetDutyCycle(LED_GREEN, 255);
        }
        else if(temp_value < HOT_THRESHOLD)
        {
            PWM_SetDutyCycle(LED_YELLOW, 255);
        }
        else
        {
            PWM_SetDutyCycle(LED_RED, 255);
            GPIO_Write(BUZZER, 1);
        }
        Delay(200);
    }
}
