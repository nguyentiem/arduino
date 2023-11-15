#include <Arduino_FreeRTOS.h>

#include <avr/io.h>

void blinkLED(void* parameter)
{
  DDRB |= (1 << PB5);   // PB.5 as output
  for (;;)
  {
    PORTB &= ~(1 << PB5); // Turn LED on
    vTaskDelay(1000);  // Wait
    PORTB |= (1 << PB5);  // Turn LED off
    vTaskDelay(1000);  // Wait
  }
}

int main(void)
{
    
    blinkLED(10);
    return 0;
}
