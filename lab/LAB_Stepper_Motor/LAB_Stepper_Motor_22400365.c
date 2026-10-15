/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : Suhyun Son
Created          : 05-03-2021
Modified         : 09-10-2026
Language/ver     : C++ in VS Code

Description      : Fourth LAB _ Problem
/----------------------------------------------------------------*/


#include "stm32f411xe.h"
#include "ecSTM32F4v2_22400365.h"

// ( A, B,  AN,  BN)
PinName_t pinStepper[4] = {PB_10,PB_4,PB_5,PB_3};

// Emergency Stop
volatile uint8_t emergencyStop = 0;

// Motor setting
uint32_t mode = FULL;
uint32_t speedRPM = 1;

// Initialiization
void setup(void){
    RCC_PLL_init();                                 // System Clock = 84MHz
    SysTick_init();                                 // Systick init

    GPIO_init(BUTTON_PIN, INPUT);                   // GPIOC pin13 initialization
    EXTI_init(BUTTON_PIN, FALL,0);                  // External Interrupt Setting

    stepper_init(mode, pinStepper);                 // Stepper GPIO pin initialization
    stepper_speed(speedRPM);                        // set stepper motor speed
}


int main(void) {
    // Initialiization --------------------------------------------------------
    setup();
    uint32_t rev=1;

    // Set steps according to stepping mode
    uint32_t steps=STEP_PER_REV*rev;

    if(mode == HALF){
        steps=STEP_PER_REV*2*rev;
    }

    // Inifinite Loop ----------------------------------------------------------
    while(1){

        // Emergency Stop
        if(emergencyStop){
            stepper_stop();
            while(1);
        }

        stepper_step(steps, DIR_CW);  // Direction : 0 or 1, Mode : FULL or HALF

        if(emergencyStop){
            stepper_stop();
            while(1);
        }

        delay_ms(2000);

        stepper_step(steps, DIR_CCW); // Direction : 0 or 1, Mode : FULL or HALF

        if(emergencyStop){
            stepper_stop();
            while(1);
        }

        delay_ms(2000);
    }
}


void EXTI15_10_IRQHandler(void) {
    if (is_pending_EXTI(BUTTON_PIN)) {
        emergencyStop = 1;
        stepper_stop();
        clear_pending_EXTI(BUTTON_PIN); // cleared by writing '1'
    }
}
