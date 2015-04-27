#define __KEYSCAN

#include "KeyScan.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "config.h"
#include "global.h"
#include <stdio.h>


uint32_t 	press_time = 0 ;

uint8_t Judge_press(void)
{
	OSTimeDly(1);
	press_time++;
	if(press_time>140)
		{
			press_time=0;
			Keylong = 1 ; 
			GR_DBG_PRINTF("IN KeyLong\n\n") ; 
		}
	else Keylong = 0 ; 
	return Keylong ; 
}


uint8_t KeyScan()
{	
	press_time = 0 ; 

  //	if(K1==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K1==0)
		//		{
		//			 while(K1==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is: 1 \n\n"); 
		//			 return 1  ;  
		//		}	
		//				    			 
		//}
  //	if(K2==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K2==0)
		//		{
		//			 while(K2==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is:2  \n\n"); 
		//			 return  2 ;  
		//		}	
		//				    			 
		//}
  //	if(K3==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K3==0)
		//		{
		//			 while(K3==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is: 3 \n\n"); 
		//			 return 3  ;  
		//		}	
		//				    			 
		//}
  //	if(K4==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K4==0)
		//		{
		//			 while(K4==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is:4  \n\n"); 
		//			 return 4  ;  
		//		}	
		//				    			 
		//}
  //	if(K5==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K5==0)
		//		{
		//			 while(K5==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is:5  \n\n"); 
		//			 return  5 ;  
		//		}	
		//				    			 
		//}
  //	if(K6==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K6==0)
		//		{
		//			 while(K6==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is: 6 \n\n"); 
		//			 return 6 ;  
		//		}	
		//				    			 
		//}
  //	if(K7==0) 
		//{   
		//	OSTimeDly(2);
		//	if(K7==0)
		//		{
		//			 while(K7==0)
		//				 { 
		//					if(Judge_press()) break;	 		
		//				 }	
		//		   	 GR_DBG_PRINTF("Key Value is:7  \n\n"); 
		//			 return 7  ;  
		//		}	
		//				    			 
		//}
	
/////////////////æÿ’Ûº¸≈Ã//////////////////	
	L1=1; L2=1;L3=0 ;
  	if(H1==0) 
		{   
//			K5_LED = 0 ; 
			OSTimeDly(2);
			if(H1==0)
				{
					 while(H1==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				    	GR_DBG_PRINTF("Key Value is:1 \n\n"); 
					return 1 ;  
				}	
						    			 
		}
  	if(H2==0) 
		{   
			OSTimeDly(2);
			if(H2==0)
				{
					 while(H2==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				   	 GR_DBG_PRINTF("Key Value is:2 \n\n"); 
					return 2 ;  
				}	
						    			 
		}
  	if(H3==0) 
		{   
			OSTimeDly(2);
			if(H3==0)
				{
					 while(H3==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				    	GR_DBG_PRINTF("Key Value is:3\n\n"); 
					return 3 ;  
				}	
						    			 
		}

	L1=1; L2=0;L3=1 ;
  	if(H1==0) 
		{   
//			K5_LED = 0 ; 
			OSTimeDly(2);
			if(H1==0)
				{
					 while(H1==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				    	GR_DBG_PRINTF("Key Value is:4 \n\n"); 
					return 4 ;  
				}	
						    			 
		}
  	if(H2==0) 
		{   
			OSTimeDly(2);
			if(H2==0)
				{
					 while(H2==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				   	 GR_DBG_PRINTF("Key Value is:5 \n\n"); 
					return 5 ;  
				}	
						    			 
		}
  	if(H3==0) 
		{   
			OSTimeDly(2);
			if(H3==0)
				{
					 while(H3==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				    	GR_DBG_PRINTF("Key Value is:6\n\n"); 
					return 6 ;  
				}	
						    			 
		}	
	L1=0; L2=1;L3=1 ;
  	if(H1==0) 
		{   
//			K5_LED = 0 ; 
			OSTimeDly(2);
			if(H1==0)
				{
					 while(H1==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				    	GR_DBG_PRINTF("Key Value is:7\n\n"); 
					return 7 ;  
				}	
						    			 
		}
  	if(H2==0) 
		{   
			OSTimeDly(2);
			if(H2==0)
				{
					 while(H2==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				   	 GR_DBG_PRINTF("Key Value is:8 \n\n"); 
					return 8 ;  
				}	
						    			 
		}
  	if(H3==0) 
		{   
			OSTimeDly(2);
			if(H3==0)
				{
					 while(H3==0)
						 { 
							if(Judge_press()) break;	 		
						 }	
				    	GR_DBG_PRINTF("Key Value is:9\n\n"); 
					return 9 ;  
				}	
						    			 
		}
//  	if(L2==0) 
//		{   
////			K3_LED = 0 ; 
//			OSTimeDly(2);
//			if(L2==0)
//				{
//					 while(L2==0)
//						 { 
//							if(Judge_press()) break;	 		
//						 }	
//				    	GR_DBG_PRINTF("Key Value is:16 \n\n"); 
//					return 16 ;  
//				}	
//						    			 
//		}	  
	return 0 ; 
}


