#include "Timer.h"

void initTimer2(){
    //Set as upcounting direction
    TIM2->CR1 &= (~TIM_CR1_CMS);
    TIM2->CR1 &= (~TIM_CR1_DIR);
    
    //Setup Timer Interrupt
    TIM2->DIER |= (TIM_DIER_CC1IE);
    TIM2->EGR |= (TIM_EGR_CC1G);
    
    TIM2->CCMR1 |= (TIM_CCMR1_CC1S_0);
}