#define __ADJUSTIR


#include"adjustIR.h"
#include "global.h"
#include "config.h"
#include "led.h"
#include "KeyScan.h"
#include "Driver\DrvUART.h"
#include "Driver\DrvGPIO.h"
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvTIMER.h"
#include "performance.h"
#include <ucos_ii.h>
uint8_t  flag_blank_ctr = 0 ; 



void Timer1_Callback (void)  //模拟PWM输出CUT_B2 控制940 
{
	
    if(flag_blank_ctr++ >= 12) flag_blank_ctr = 0 ; 
    if(System.Led.Pwm_IR850.flag == TRUE)
    { 
       TOP_IR850 = flag_blank_ctr < System.Led.Pwm_IR850.Duty ? 0: 1 ; 
	}
	if(System.Led.Pwm_IR940.flag == TRUE)
	{
       TOP_IR940 = flag_blank_ctr < System.Led.Pwm_IR940.Duty ? 0: 1 ;    
	} 	
}

void TIMER1_Configuration()				   
{
	
  DrvTIMER_Init();														
	
	DrvSYS_SelectIPClockSource(E_SYS_TMR1_CLKSRC,0);					

	DrvTIMER_Open(E_TMR1,50000,E_PERIODIC_MODE);								
	
 	DrvTIMER_SetTimerEvent(E_TMR1,1,(TIMER_CALLBACK) Timer1_Callback,0);

	DrvTIMER_EnableInt(E_TMR1);											

	DrvTIMER_Start(E_TMR1);												
}
void AdjustIRLight() 
{
	uint8_t key=0,i;	
	key = KeyScan();
	Key_Led_Init(); 
	switch(key)
	{
	    case 1      :
				{
//					K1_LED = 1 ; 
					{
						if((System.Dsp.Mode ==CHECK_MODE)
						   ||(System.Dsp.Mode ==PCCAM_MODE))
						{
							if(System.Dsp.Sensor == SENSOR1)
							{
								Sensor2(); 							
							}
							else
							{
								Sensor1() ; 
							}
						}
						else if(System.Dsp.Mode ==VIEW_MODE)
						{
						  	PhotoZoomUp();     
						}
					}
				}break ;  
		case 4      :
                    {
    			         if(System.Led.Pwm_IR940.Duty <12)
    		             {
    			            System.Led.Pwm_IR940.Duty +=1 ;//940加1
							 SystemWriteBCKData() ; 
    		             } 
						 else
						 {
	    		              for(i=0;i<5;i++)
	    					  { 
//	    					  	 K4_LED = 0; 
	    						 OSTimeDly(20) ; 
//	    						 K4_LED = 1; 
	                             OSTimeDly(20) ; 
	    					  }						 
						 }
		            }break ;
		case 5      :
                    {
    			         if(System.Led.Pwm_IR940.Duty >0)
    		             {
    			            System.Led.Pwm_IR940.Duty -=1 ;//940减1
							 SystemWriteBCKData() ; 
    		             } 
						 else
						 {
	    		              for(i=0;i<3;i++)
	    					  { 
//	    					  	 K5_LED = 0; 
	    						 OSTimeDly(20) ; 
//	    						 K5_LED = 1; 
	                             OSTimeDly(20) ; 
	    					  }						 
						 }		   
		            }break ;
		case 6      :	if(System.Led.Pwm_IR850.Duty <12)
    		             {
    			            System.Led.Pwm_IR850.Duty +=1 ; //850加1
							 SystemWriteBCKData() ; 
    		             }
						 else
						 {
	    		              for(i=0;i<3;i++)
	    					  { 
//	    					  	 K6_LED = 0; 
	    						 OSTimeDly(20) ; 
//	    						 K6_LED = 1; 
	                             OSTimeDly(20) ; 
	    					  }						 
						 }						 
						 
						 break ;
		case 7      :
			         {
    			         if(System.Led.Pwm_IR850.Duty >0)
    		             {
    			            System.Led.Pwm_IR850.Duty -=1 ; //850减1 
							 SystemWriteBCKData() ; 
    		             }
						 else
						 {
	    		              for(i=0;i<3;i++)
	    					  { 
//	    					  	 K7_LED = 0; 
	    						 OSTimeDly(20) ; 
//	    						 K7_LED = 1; 
	                             OSTimeDly(20) ; 
	    					  }						 
						 }						  
		             }break ;
		case 8      :
        			{
    				    SystemWriteBCKData() ; 
    		              for(i=0;i<3;i++)
    					  { 
//    					  	 K8_LED = 0; 
    						 OSTimeDly(20) ; 
//    						 K8_LED = 1; 
                             OSTimeDly(20) ; 
    					  }
        		    }break ;
		default     :break ; 
	}
	
} 
