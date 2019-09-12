#include "Timer.h"


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
    TIM2->CCMR1 |= (TIM_CCMR1_CC1S & 0x01);
    
    //Select edge of active transition
    TIM2->CCER &= (~TIM_CCER_CC1NP);
    TIM2->CCER &= (~TIM_CCER_CC1P);
    
    //enable capture mode
    TIM2->CCER |= TIM_CCER_CC1E;
    
    //enable interrupt
    //TIM2->DIER |= TIM_DIER_CC1IE;
    
    //enable timer
    TIM2->CCER |= (TIM_CCER_CC1E);
    
    TIM2->CR1 |= TIM_CR1_CEN;
    
}

unsigned int getCNT(){
    return TIM2->CNT;
}