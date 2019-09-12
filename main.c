#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "Timer.h"

#include <string.h>
#include <stdio.h>

char RxComByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give Red LED control input (Y = On, N = off):\r\n";
char buf[100];

int main(void){
	//char rxByte;
	int		a ;
	int		n ;
	int		i ;
	float b;
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
    /*
		
    putString("Type some characters\n\r");
	while (1){
        char c = getChar();
        putChar(c);
	}
    
    */
    
    initTIM2();
    while(1){
        sprintf(buf, "%d", getCNT());
        putString(buf);
        for(int i = 0; i < 5000000; i++);
    }
}

