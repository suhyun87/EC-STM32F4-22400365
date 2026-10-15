/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : 손수현
Created          : 05-03-2021
Modified         : 23-09-2026
Language/ver     : C++ in VS Code

Description      : Second Lab _ Problem 1, 2
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecGPIO2_22400365.h"
#include "ecRCC2.h"

PinName_t pinFND[8]    = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
PinName_t selectFND[4]={PA_10, PA_11, PC_4, PC_3};

void setup(void){
    // Intialize System Clock
    RCC_HSI_init();    
    // Intialize FND pins and Others
    FND_init(pinFND);
    FND_select_init(selectFND);  
    GPIO_otype(selectFND[0], PUSH_PULL); //only problem 2
    // Intialize  Others
    for(int i = 0; i < 8; i++){
        GPIO_otype(pinFND[i], PUSH_PULL);
        GPIO_pupd(pinFND[i], NO_PUPD);  //only problem 2
        GPIO_ospeed(pinFND[i], MEDIUM_SPEED);
    }

    /*for(int i = 0; i < 4; i++){
        GPIO_otype(selectFND[i], PUSH_PULL);     only problem 1
    }*/

    GPIO_init(PA_4, INPUT);  //only problem 2
    GPIO_pupd(PA_4, PU);     //only problem 2

};

/*problem 1
int main(void) {
    setup();
    uint8_t numDisplay1  = 0;
    uint8_t numDisplay2  = 5;
    uint8_t selectFND1  = 0;
    uint8_t selectFND2  = 1;

    while (1) {
        FND_select(selectFND1);
        FND_display(numDisplay1);
        delay_ms_HSI(1);             		
        FND_select(selectFND2);
        FND_display(numDisplay2);
        delay_ms_HSI(1);	
    }
}
*/

//problem 2
int main(void){
    setup();
    //Define a variable for the number of button presses
    uint8_t increase_num =0;

    while(1){

        FND_select(0);
        FND_display(increase_num);

        if(GPIO_read(PA_4) == LOW){
            //Increase in the number of button presses
            increase_num++;
            //If increase_num reaches 10, reset increase_num to 0.
            if (increase_num>9){
                increase_num = 0;
            }

            delay_ms_HSI(200);
        }
    }

}

