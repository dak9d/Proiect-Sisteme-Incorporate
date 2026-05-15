#include <stdint.h>

#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h"
#include "drivers/adc/adc.h"

#include "bsp/nano.h"
#include "utils/delay.h"

// LED-uri
#define LED_GREEN   D11
#define LED_YELLOW  D9
#define LED_RED     D10

// Termistor pe ADC0
#define TEMP_CHANNEL 0

uint16_t temp_value;

/* praguri simple (calibratezi tu) */
#define COLD_THRESHOLD   500
#define HOT_THRESHOLD    560

int main(void)
{
    ADC_Init();

    PWM_Init(LED_GREEN, 1000);
    PWM_Init(LED_YELLOW, 1000);
    PWM_Init(LED_RED, 1000);

    while(1)
    {
        temp_value = ADC_Read(TEMP_CHANNEL);

        // reset LED-uri
        PWM_SetDutyCycle(LED_GREEN, 0);
        PWM_SetDutyCycle(LED_YELLOW, 0);
        PWM_SetDutyCycle(LED_RED, 0);

        // LOGICĂ SIMPLĂ
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
        }

        Delay(200);
    }
}
