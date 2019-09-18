#include "Timer.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>
char buf[100];


void initTIM2(){
    //TODO Enable TIM2 Clock
    RCC->APB1ENR1 |= (RCC_APB1ENR1_TIM2EN);
    //Load Prescaler
    TIM2->PSC = 79;
    //Generate event
    TIM2->EGR |= TIM_EGR_UG;
    
    //Disable Timer
    TIM2->CCER &= (~TIM_CCER_CC1E);
    
    //Enable input capture
    TIM2->CCMR1 |= (TIM_CCMR1_CC1S & 1);
    
    //Select edge of active transition
    TIM2->CCER &= (~TIM_CCER_CC1NP);
    TIM2->CCER &= (~TIM_CCER_CC1P);
    
    TIM2->CCMR1 &= (~TIM_CCMR1_IC1PSC);
   
    
    //enable timer
    TIM2->CCER |= (TIM_CCER_CC1E);
    
    TIM2->CR1 |= TIM_CR1_CEN;

    
    
    
}

uint32_t getCCR1(){
    return TIM2->CCR1;
}

uint32_t getCNT(){
    TIM2->SR &= (~TIM_SR_CC1IF);
    return TIM2->CNT;
}



void TIM2_IRQHandler(void){
    sprintf(buf, "%d\n\r", getCNT());
    putString(buf);
}