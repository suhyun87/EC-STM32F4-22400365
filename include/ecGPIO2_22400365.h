/*----------------------------------------------------------------\
@ Embedded Controller by Young-Keun Kim - Handong Global University
Author           : 손수현
Created          : 05-03-2021
Modified         : 14-09-2026
Language/ver     : C++ in VS Code

Description      : GPIO Library. Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"

#define INPUT  0x00
#define OUTPUT 0x01
#define AF     0x02
#define ANALOG 0x03

#define HIGH 1
#define LOW  0

#define LED_PIN 	PA_5
#define BUTTON_PIN  PC_13

/*---------------------------------------------------------------- 
                    [EXERCISE]
---------------------------------------------------------------- */
// ADD MORE  MACRO related to GPIO 
// GPIO Pull-up / Pull-down
#define NO_PUPD     0x00
#define PU          0x01
#define PD          0x02

// GPIO Output Type
#define PUSH_PULL   0x00
#define OPEN_DRAIN  0x01

// GPIO Output Speed
#define LOW_SPEED       0x00
#define MEDIUM_SPEED    0x01
#define FAST_SPEED      0x02
#define HIGH_SPEED      0x03



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, uint32_t speed);
void GPIO_otype(PinName_t pinName, uint32_t type);
void GPIO_pupd(PinName_t pinName, uint32_t pupd);
void GPIO_write(PinName_t pinName, uint32_t Output);
uint32_t  GPIO_read(PinName_t pinName);

// ARDUINO Syntax  (Optional)
void pinMode(PinName_t pin, uint32_t mode);
void digitalWrite(PinName_t pin, uint32_t value);
uint32_t  digitalRead(PinName_t pin);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H