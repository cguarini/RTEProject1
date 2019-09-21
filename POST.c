#include "POST.h"
#include <string.h>
#include <stdio.h>


char post[] = "Checking POST configuration\r\n";
char pfine[] = "POST works fine. Proceeding to the next steps\r\n\n";
 //int post_count =1;
 uint32_t postprev = 0;
 uint32_t  postcurr = 0;
 uint32_t timeint;
  char tbuff[300];
 
 
 
void POSTtest(void) {
    
  
    USART_Write(USART2, post, strlen(post));
    
          // need to include a delay function
    for(int i = 0; i < 20000000; i++);
    //check if the SR is set to 1 and the input pulse is captured

      postprev = 0;
        while(1)
            {
            if(TIM2->SR  &  TIM_SR_CC1IF){
              postcurr = getCCR1();
            
            if(postprev > 0)
            {
            timeint= postcurr - postprev;
            sprintf(tbuff, "The time interval is %d\r\n", timeint);
            putString(tbuff);
            }
            postprev = postcurr;
            
        
            
            if(timeint >= 100000)
            {
                USART_Write(USART2, pfine, strlen(pfine));
                break;
            }
                 
            else 
            {
                continue;
            }
    
            }
          }
}
            
    
        