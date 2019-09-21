#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Timer.h"
#include "GPIOINP.h"
#include "POST.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[100];
uint32_t results[10];
int buckets[100];
long lowerLimit = 1000;


void printBuckets(){
    for(int i = 0; i < 100; i++){
        if(buckets[i]){
            sprintf(str, "%ld %d\r\n", ((lowerLimit - 50) + i), buckets[i]);
            putString(str);
        }
    }
}

void initializeBuckets(){
    for(int i = 0; i < 100; i++){
        buckets[i] = 0;
    }
}

void runInterface(void){
  //Print introduction message
  putString("Welcome to the Timing Demo for Group 17!");
  char str[250];
  sprintf(str, "Default Lower Limit: %ld", lowerLimit);
  putString(str);
  putString("\n\rWould you like to set a new lower limit? (Y|N): ");

  
  //Get if user wants to change lower limit default
  char answer = 1;
  
  while((answer = getChar())){
    
    //Yes is selected, define a new lower limit
    if(answer == 'Y' || answer == 'y'){
      putChar(answer);

      while(1){//will loop until limit is correctly chosen
        putString("\r\nInput new lower limit (50-9950us): ");
        char * newLimit = getString();
        char * ptr;
        long i = strtol(newLimit, &ptr, 10);
        if(i >= 50 && i <= 9950){
          //limit correctly chosen, set limit and break loop
          lowerLimit = i;
          break;
        }
        else{
          //invalid limit, loop again
          putString("\r\nInvalid limit!");
        }
      }
      //break answer loop after correctly choosing response
      break;
    }
  
    
    //No is selected, proceed with default limit
     if(answer == 'N' || answer == 'n'){
       putChar(answer);
       putString("\n\r");
      break;
    }
    
  }
  

  sprintf(str, "Measuring with a lower limit of: %ld Upper limit of: %ld\n\r", lowerLimit, lowerLimit + 100);
  putString(str);
  
}

int runAgain(){
  putString("Would you like to run again? Y|N: ");
  
  char answer = 1;
  int retVal;
  while((answer = getChar())){
    if(answer == 'Y' || answer == 'y'){
      putChar(answer);
      retVal = 1;
      break;
    }
    else if(answer == 'N' || answer == 'n'){
      putChar(answer);
      retVal = 0;
      break;
    }
  }
  return retVal;
}

int main(void){

	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	UART2_Init();
  initGPIOA();
  initTIM2();
  
  //Run the post test
  POSTtest();
  
  
  
  while(1){
    //reset limit to default
    lowerLimit = 1000;
    
    //Run the CLI
    runInterface();
    
    //initialize buckets to empty
    initializeBuckets();

    int previousTime = 0;
    int count = 0;
    while(count < 1000){
        if(TIM2->SR & TIM_SR_CC1IF){//Check for rising edge flag
            uint32_t currentTime = getCCR1();
            if(previousTime > 0){//if there is a previous time (not the first measurement)
                //find the actual time and increment its bucket
                buckets[(currentTime - previousTime) - (lowerLimit - 50)]++;
            }
            previousTime = currentTime;
            count++;
        }
    }
    printBuckets();
    
    if(!runAgain()){
      putString("\n\rEnding Program!\n\r");
      break;
    }
    else{
      putString("\n\r");
    }
    
  }
}



