
/***************************************************************************************
****************************************************************************************
* FILE		: keydispose.c
* Description	:  	A 老化程序
 						1,正常老化
 						2,拍照老化				
					B 正常程序
					C 校正程序 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* History:
* Version		Name       		Date			Description
   0.1		XXX	2013/08/20	Initial Version
****************************************************************************************
****************************************************************************************/
#define __KEYDISPOSE

#include "Keydispose.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "global.h"
#include "KeyScan.h"
#include "performance.h"
#include "Led.h"
#include "communication.h" 
#include "V6MDebug.h"
#include "Adjustir.h"

//#include"DS1307.h"
//#include "time.h"
#include "config.h"

volatile uint8_t KS=0 ,KS_button = 0 ; 
const uint32_t SysVersion[3]={0x56312E31,0x342E3035,0x36000000};
const uint8_t  SysVersion1[]="1.xx.xxx"; 	//System.Sys.Data.info.SoftwareVer[0]		此2处+说明+程序文件名称需要修改

ENUM_LED_STATU LedTemp ; 
/*=================================================================================
* Function	: UsbInfoDispose
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
=================================================================================*/
void UsbInfoDispose()
{
	if(ptr != NULL)
	{	
		System.Key.NoKeyTime = 0 ;

		if(System.Dsp.Mode == SLEEP_MODE)		// 在USB通信过程中不休眠
		{	
			CheckMode(); 
		}
		ptr(); 
	 	MCU_Status.Struct_Status=0x01;	
		ptr = NULL ;
	}	
	return ; 
}

uint8_t BoxOpenCheck()
{
	KS = (uint8_t) DrvGPIO_GetBit(E_GPE, 5); 
	if(KS != KS_button)
	{
		KS_button = KS ; 
	    if( KS_button == 0 ) //闭合
		   	{ 
				 switch(LedTemp)
				 {
					case 	TOP_WHITE_ON  : Top_W_On();    		break ;  
					case 	TOP_IR850_ON  : Top_IR850_On( );	break ; 
					case 	TOP_IR940_ON  : Top_IR940_On( );	break ; 

					case 	LEFT_W_ON     : Left_W_On( );   	break ; 
					case 	RIGHT_W_ON 	  : Right_W_On( );	    break ; 
					case 	LEFT_IR850_ON : Left_IR850_On();	break ; 
					case 	RIGHT_IR850_ON:	Right_IR850_On();	break ; 
                                                                      
					case 	BOT_W_ON   	  : Bot_W_On();			break ; 
					case 	BOT_IR_ON  	  : Bot_IR_On(); 		break ; 
					case 	RIGHT_UV_ON   : Right_UV_On(); 		break ; 
					case 	DB_UV_ON      : Double_UV_On(); 	break ; 
					case 	RIGHT_IR770_ON: Right_IR770_On();	break ;  
					case 	RIGHT_LASER_ON:	Right_Laser_On(); 	break ; 
					case 	C608_PWR_ON   :	C608_On(); 			break ;
					case 	DB_WT_UV_ON	  :	Double_WT_UV_On(); 	break ; 
					case    DB_UV_EXPOSURE1_ON : Double_UV_Exposure1_On();break ;
					case 	DB_UV_EXPOSURE2_ON : Double_UV_Exposure2_On();break ;
					
				 	default :	break ; 
				 }
		   	}
		   else
		   	{
				 LedTemp = System.Led.Statu ; 
			 	Light_Init() ; 
		    }				
	}
	if( KS ) return 0x01 ;
	else	return 0x00 ; 
}
void USbInCheck()
{
	System.Usb.NewUsbStatu = USB_STATUS ; 							
	if(System.Usb.OldUsbStatu != System.Usb.NewUsbStatu)
	{
		System.Usb.UsbStatuLabel = 1 ; 
		if(System.Usb.NewUsbStatu == USB_IN)
		{
			//插入USB操作
	 	//	  SHOW_SCREEN(0xE3,"USB READY\n");
			TfMode(); 
		//	  OSTimeDly(200) ; 
		}
		else if(System.Usb.NewUsbStatu == USB_OUT)
		{
			//拔出USB操作
			  OSTimeDly(150) ; 
			  SHOW_SCREEN(0xE3,"USB NOT READY\n");
			  OSTimeDly(100) ; 
			 
			if((System.Dsp.Mode == PCCAM_MODE)||(System.Dsp.Mode == TF_MODE))
			{
				CheckMode(); 
			}
			OSTimeDly(100) ;
		}
		System.Usb.OldUsbStatu = System.Usb.NewUsbStatu ; 
		OSTimeDly(10); 
	}	
}
void KeyDispose()
{
	UsbInfoDispose();
	USbInCheck() ; 
    KeyInfoDispose();		
}

void TESTA()	//正常老化
{
	uint32_t i = 120 ; 
	uint8_t m = 0 ; 
	OSTimeDly(500) ; 
TESTAG:
	i = 120 ; 
	while(i--)
	{
		Top_W_On();
		OSTimeDly(200);     	
		Select_Send(0x21);  
		OSTimeDly(400); 
		Top_IR940_On( ); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

		Left_W_On( );  
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400);   

		Right_IR850_On( ); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

		Left_IR850_On(); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

		Right_IR850_On(); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400);   
		                                            
		Bot_W_On();	
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 
			 
		Bot_IR_On(); 
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 	 
	 
		Double_UV_On();  
		OSTimeDly(200);     	
		Select_Send(0x21); 
		OSTimeDly(400); 

	} 
   	 SHOW_SCREEN(0xE8, "Press K1 To Run Again\n");       

	 Light_Init();
	 while(1)
	 {
	  	 m = 0 ; 
	 	 m = KeyScan() ; 	 
		 if(m) 
		 {	
		 	GR_DBG_PRINTF("\nm  Value is %d\n",m);
		 	Select_Send(0xE9);  
		 	 if(m == 1)
			 {
			 	 goto  TESTAG ;
			 }
			 else
			 {
			 	 break ; 
			 }
		 }	
		 OSTimeDly(10); 
	 }
}

void TESTB()
{
	// 老化测试 --各个灯条循环亮。 
//	TestHardWareInit(); 
}

void TESTC()
{ 
	
}
void TESTD()
{ 
	
}

void TESTE()
{
	Top_IR850_940_Blink();
	for(;;)
	{
		AdjustIRLight() ; 		 
		OSTimeDly(5); 	
	}
}
