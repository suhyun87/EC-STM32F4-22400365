/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Suhyun Son
Created          : 05-03-2021
Modified         : 07-10-2026
Language/ver     : C++ in VS Code

Description      : Third LAB _ Problem 1
/----------------------------------------------------------------*/


#include "ecSTM32F4v2_22400365.h"

#define LED0_PIN   PB_12 		//EVAL board JKIT LED0
#define SW2_PIN    PA_4			//EVAL board JKIT SW2
#define SW1_PIN    PD_2         //EVAL board JKIT SW1


// void led_toggle(PinName_t pinName);  // in ecGPIO2.h

// Pin Definition
PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4] = {PA_10, PA_11, PC_4, PC_3};

// Initialization 
void setup(void)
{
    RCC_PLL_init();                 // System Clock = 84MHz
    SysTick_init();                 // SysTick Timer Initialization
    // Initialize GPIOB_12 for Output
    GPIO_init(LED0_PIN, OUTPUT);    // LED0 for EVAL board	

    // Initialize GPIOA_4 for Input Button
    GPIO_init(SW2_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW2_PIN, PU);  // PULL-UP for EVAL board

    // Initialize EXTI PA_4
    EXTI_init(SW2_PIN, FALL, 10);
    
    // Initialize GPIOD_2 for Input Button
    GPIO_init(SW1_PIN, INPUT);  // INPUT for EVAL board
    GPIO_pupd(SW1_PIN, PU);  // PULL-UP for EVAL board

    // Initialize EXTI PD_2
    EXTI_init(SW1_PIN, FALL, 10);
    
    // Initialize 7-Segment Display
    FND_init(pinFND);
    FND_select_init(selectFND);
}


// Initialization
volatile int count = 0;
volatile int pause = 0;

// MAIN  ----------------------------------------
int main(void) {
	setup();
	while (1){

        // 7-Segment Display Setting
        FND_select(0);
        FND_display(count);

        // Count Up When Not Paused
        if (pause == 0){
            count++;
            if (count > 9){
                count = 0;
            }
    }

    // Value changes every second
    delay_ms(1000);

    }
}

// SW2 Interrupt: Pause/Resume Counting
void EXTI4_IRQHandler(void) {
	if (is_pending_EXTI(SW2_PIN)) {   
        pause = !pause;
        clear_pending_EXTI(SW2_PIN);
	}
}

// SW1 Interrupt: Reset Counter
void EXTI2_IRQHandler(void) {
    if(is_pending_EXTI(SW1_PIN)){
    count=0;
    clear_pending_EXTI(SW1_PIN);
    }
}