/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : 손수현
Created          : 05-03-2021
Modified         : 17-09-2026
Language/ver     : C++ in VS Code

Description      : First Lab _ Problem 3
/----------------------------------------------------------------*/
#include "ecRCC2.h" 
#include "ecGPIO2_22400365.h" 
 
// SW2 
#define SW2_PIN     PA_4 
 
// LED0 ~ LED3 
#define LED0_PIN    PB_12 
#define LED1_PIN    PB_13 
#define LED2_PIN    PB_14 
#define LED3_PIN    PB_15 
 
void setup(void); 
 
int main(void) 
{ 
    setup(); 
 
    int ledState = 0; 
    int buttonState = 1; 
    int prevButtonState = 1; 
 
    while(1) 
    { 
        // Read SW2 
        buttonState = GPIO_read(SW2_PIN); 
 
        // Detect button press (HIGH -> LOW) 
        if(prevButtonState == 1 && buttonState == 0) 
        { 
            // Move to next LED 
            ledState++; 
 
            if(ledState > 3) 
                ledState = 0; 
 
            // Turn OFF all LEDs
            // Active-High : LOW = OFF
            GPIO_write(LED0_PIN, LOW); 
            GPIO_write(LED1_PIN, LOW); 
            GPIO_write(LED2_PIN, LOW); 
            GPIO_write(LED3_PIN, LOW); 
 
            // Turn ON only selected LED
            // Active-High : HIGH = ON
            if(ledState == 0) 
                GPIO_write(LED0_PIN, HIGH); 
            else if(ledState == 1) 
                GPIO_write(LED1_PIN, HIGH); 
            else if(ledState == 2) 
                GPIO_write(LED2_PIN, HIGH); 
            else if(ledState == 3) 
                GPIO_write(LED3_PIN, HIGH); 
 
            // Debouncing 
            delay_ms_HSI(100); 
        } 
 
        prevButtonState = buttonState; 
    } 
} 
 
 
// Initialization 
void setup(void) 
{ 
    RCC_HSI_init(); 
 
    // SW2 : PA4, Digital IN, Pull-Up 
    GPIO_init(SW2_PIN, INPUT); 
    GPIO_pupd(SW2_PIN, PU); 
 
    // LED0 : PB12 
    GPIO_init(LED0_PIN, OUTPUT); 
    GPIO_pupd(LED0_PIN, PU); 
    GPIO_otype(LED0_PIN, OPEN_DRAIN); 
    GPIO_ospeed(LED0_PIN, MEDIUM_SPEED); 
 
    // LED1 : PB13 
    GPIO_init(LED1_PIN, OUTPUT); 
    GPIO_pupd(LED1_PIN, PU); 
    GPIO_otype(LED1_PIN, OPEN_DRAIN); 
    GPIO_ospeed(LED1_PIN, MEDIUM_SPEED); 
 
    // LED2 : PB14 
    GPIO_init(LED2_PIN, OUTPUT); 
    GPIO_pupd(LED2_PIN, PU); 
    GPIO_otype(LED2_PIN, OPEN_DRAIN); 
    GPIO_ospeed(LED2_PIN, MEDIUM_SPEED); 
 
    // LED3 : PB15 
    GPIO_init(LED3_PIN, OUTPUT); 
    GPIO_pupd(LED3_PIN, PU); 
    GPIO_otype(LED3_PIN, OPEN_DRAIN); 
    GPIO_ospeed(LED3_PIN, MEDIUM_SPEED); 
 
    // Initial LED state : LED0 ON
    // Active-High : HIGH = ON, LOW = OFF
    GPIO_write(LED0_PIN, HIGH); 
    GPIO_write(LED1_PIN, LOW); 
    GPIO_write(LED2_PIN, LOW); 
    GPIO_write(LED3_PIN, LOW); 
}