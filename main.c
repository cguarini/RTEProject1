#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Timer.h"
#include "GPIOINP.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[100];
uint32_t results[10];
int buckets[100];


void printBuckets(){
    for(int i = 0; i < 100; i++){
        if(buckets[i]){
            sprintf(str, "%d %d\r\n", 950 + i, buckets[i]);
            putString(str);
        }
    }
}

void initializeBuckets(){
    for(int i = 0; i < 100; i++){
        buckets[i] = 0;
    }
}

int main(void){

	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	UART2_Init();
    initGPIOA();
    initTIM2();

    int previousTime = 0;
    putString("Start\n\r");
    int count = 0;
    while(count < 1000){
        if(TIM2->SR & TIM_SR_CC1IF){//Check for rising edge flag
            uint32_t currentTime = getCCR1();
            if(previousTime > 0){//if there is a previous time (not the first measurement)
                //find the actual time and increment its bucket
                buckets[(currentTime - previousTime) - 950]++;
            }
            previousTime = currentTime;
            count++;
        }
    }
    printBuckets();
}



