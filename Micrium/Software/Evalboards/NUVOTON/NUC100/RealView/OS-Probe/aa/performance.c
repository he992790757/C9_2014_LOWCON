#define __PERFORMANCE 

#include "performance.h"
#include "global.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "Led.h"
#include "communication.h"
#include "KeyScan.h"
//#include "DS1307.h"
//#include "time.h"
#include "DrvADC.h"
#include "stdio.h"
#include "config.h"
#include "Keydispose.h"
//#include "dspperf.h"
const uint8_t TW_Snr1EV_FB[] ={0xFB,G_SENCE_WT,0x08,0x08}	;	   //曝光时间
const uint8_t TW_Snr1EV_FC[] ={0xFC,G_SENCE_WT,0x16,0x16}	;

const uint8_t UV_Snr1EV_FB[] ={0xFB,G_SENCE_DB_UV,0x30,0x30}	;	
const uint8_t UV_Snr1EV_FC[] ={0xFC,G_SENCE_DB_UV,0x32,0x32}	;

const uint8_t L_IR_Snr1EV_FB[] ={0xFB,G_SENCE_L_IR,0x09,0x09}	;	   //曝光时间
const uint8_t L_IR_Snr1EV_FC[] ={0xFC,G_SENCE_L_IR,0x30,0x30}	;

const uint8_t UV_Snr2EV_FB[] ={0xFB,0x04,0x20,0x20}	;	
const uint8_t UV_Snr2EV_FC[] ={0xFC,0x04,0x70,0x70}	; 

const uint8_t UV_Snr3EV_FB[] ={0xFB,0x05,0x25,0x25}	;		
const uint8_t UV_Snr3EV_FC[] ={0xFC,0x05,0x20,0x20}	;

const uint8_t IR940_Snr1EV_FB[] ={0xFB,G_SENCE_T_IR940,0x0F,0x0F}	;	
const uint8_t IR940_Snr1EV_FC[] ={0xFC,G_SENCE_T_IR940,0x18,0x18}	;

//const uint8_t Zoom0X[]={0x2C,0x10,0x80,0x80};
const uint8_t Zoom1X[]={0x2C,0x10,0x80,0x80};
const uint8_t Zoom2X[]={0x2C,0x20,0x80,0x80};
const uint8_t Zoom3X[]={0x2C,0x30,0x80,0x80};



uint8_t* WcharToChar(wchar_t *p)
{
	 uint8_t i = 0 ; 

	 for(;i<=30;i++)
	 {
	 	char_array[i] = 0 ; 
	 }
	 for(i=0;;i++)
	 {
	 	 if(*(p+i) != NULL)
		 {
		    char_array[2*i] = *(p+i)>>8 ; 
			char_array[2*i+1] = *(p+i) ; 	 	
		 } 
		 else
		 {
		 	break ; 
		 }	  
	 }	
	 return &char_array[0]; 	
}



void SHOW_SCREEN_WC_NUM(uint8_t comm,/* uint8_t cnt,*/ wchar_t *p,uint16_t NUM)
{
    uint8_t i=0 ; 


	 for(;i<=20;i++)
	 {
	 	char_array[i] = 0 ; 
	 }
	 for(i=0;;i++)
	 {
	 	 if(*(p+i) != NULL)
		 {
		    char_array[2*i] = *(p+i)>>8 ; 
			char_array[2*i+1] = *(p+i) ; 	 	
		 } 
		 else
		 {
		 	break ; 
		 }	  
	 }
	 char_array[2*i] = 0x00 ;   
	 char_array[2*i+1] = NUM/100 +0x30 ;   
	 char_array[2*i+2] = 0x00 ; 
	 char_array[2*i+3] = NUM%100/10 +0x30 ;
	 char_array[2*i+4] = 0x00 ;
	 char_array[2*i+5] = NUM%100%10 +0x30 ;       
	 	
	 SHOW_SCREENW(comm, &char_array[0] );
}



void ShowChkPhotOne()
{
	SHOW_SCREENW(0xE8, WcharToChar(L"请进一步检查") ); 
}
void ShowChkPhotAgain()
{
	SHOW_SCREENW(0xE8, WcharToChar(L"可,请进一步检查") ); 	
}
void ExtBlackScreen()
{
     Select_Send(0xE9);
}
void Photo_SignAndCount()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		System.Process_TakePht  = 0 ; 
	 	SHOW_SCREENW(0xE8, WcharToChar(L"签发数据采集,请稍候") );	
		
		PhotographFour();  
		SignOutCount++ ; 	 
		System.Process_TakePht  = 1 ; 
		SHOW_SCREEN_WC_NUM(0xE2, L"签发",SignOutCount);
		if(System.PhotoNum != 4)
		{
	 		System.PhotoNum = 4 ;  //4张照片
			System.Sys.SaveInfoFlag  = 0x01  ;
		}
	}
}
void Photo_SignAndChk()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		System.Process_TakePht  = 0 ; 
		SHOW_SCREENW(0xE8, WcharToChar(L"数据采集中,请稍候...") );	
		PhotographFour_Sign();  	
	//	Select_Send(0xE9); 
		System.Process_TakePht  = 1 ; 

		if(System.PhotoNum != 5)
		{
	 		System.PhotoNum = 5 ;  //4张照片
			System.Sys.SaveInfoFlag  = 0x01  ;
		}
	}
}
/*==================================================================
* Function	: PhotoMvUp
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoMvUp()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom != X0 ))
	{
		Select_Send(0x17);
		OSTimeDly(10);	
	}
}


/*==================================================================
* Function		: PhotoMvDown
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value	: 
==================================================================*/
void PhotoMvDown()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom != X0 ))
	{
		Select_Send(0x18);
		OSTimeDly(10);	
	}
}


/*==================================================================
* Function		: PhotoMvLeft
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoMvLeft()
{
	if((System.Dsp.Mode == VIEW_MODE))
	{
		if(System.Dsp.ViewMode.Zoom != X0)
		{
			Select_Send(0x19);
			OSTimeDly(10);	
		}
		else
		{
			PhotoPrevious();
		}
	}
}

/*==================================================================
* Function		: PhotoMvRight
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoMvRight()
{
	if((System.Dsp.Mode == VIEW_MODE))
	{
		if(System.Dsp.ViewMode.Zoom != X0)
		{
			Select_Send(0x1A);
			OSTimeDly(10);		
		}
		else
		{
			PhotoNext();
		}


	}
}

/*==================================================================
* Function	: PhotoNext
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoNext()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom == X0 ))
	{
		Select_Send(0x2b);
		OSTimeDly(20);	
	}
}

void XyZoomFuc()
{
	if((System.Dsp.Mode == CHECK_MODE)||
	   (System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.XyZoom[0] == 0xAA) System.XyZoom[0] = 0xAB ; 
		if(System.XyZoom[0] == 0xF0) System.XyZoom[0] = 0xF1 ;

		if(System.XyZoom[1] == 0xAA) System.XyZoom[1] = 0xAB ; 
		if(System.XyZoom[1] == 0xF0) System.XyZoom[1] = 0xF1 ; 

		if(System.XyZoom[2] == 0xAA) System.XyZoom[2] = 0xAB ; 
		if(System.XyZoom[2] == 0xF0) System.XyZoom[2] = 0xF1 ; 
   		Dsp_Send_Data(0x2C,System.XyZoom[0],System.XyZoom[1],System.XyZoom[2],D_NON); 
	}	
}
/*==================================================================
* Function	: PhotoPrevious
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoPrevious()
{
	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom == X0 ))
	{
		Select_Send(0x2a);
		OSTimeDly(20);
	}
	
}

void Check_View_Zoom(ENUM_DSP_ZOOM NUM)	   // 照片放大
{
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		switch(NUM)
		{

			case X0 : if(System.Dsp.CheckMode.Zoom != X0 )
					  {
					    Select_Send(0x30); 
					//	Dsp_Send_Data(0x2C,0x22,20,150,D_NON); 	  
						System.Dsp.CheckMode.Zoom = X0 ;
						OSTimeDly(50); //DSP_SENDB(0xe2,NULL," "); 
					   } break ; 
			
			case X1 :  if(System.Dsp.CheckMode.Zoom != X1 )
					  {
					  	Scen_Send(0x2C,0x24);  
						//Scen_Send(0x2C,0x40);  	
						//Dsp_Send_Data(0x2C,0x40,20,150,D_NON); 	
						System.Dsp.CheckMode.Zoom = X1 ;		 	
						OSTimeDly(50);} break ;//DSP_SENDB(0xe2,NULL,"X3"); 		
						 
			case X2 : 	 if(System.Dsp.CheckMode.Zoom != X2 )
					  {
						Scen_Send(0x2C,0x24);  	
					    //Dsp_Send_Data(0x2C,0x52,20,150,D_NON); 
						System.Dsp.CheckMode.Zoom = X2 ;		 	
						OSTimeDly(10);}break ;
						//DSP_SENDB(0xe2,NULL,"X5");
						 	
						
 			case X3 :  	 if(System.Dsp.CheckMode.Zoom != X3 )
					  {
						 Scen_Send(0x2C,0x24);  
						//Dsp_Send_Data(0x2C,0x52,20,150,D_NON); 
					//	Dsp_Send_Data(0x2C,0x70,0,0,D_NON); 			
 		 				System.Dsp.CheckMode.Zoom = X3 ;		 	
 			 			OSTimeDly(10);}break ; //DSP_SENDB(0xe2,NULL,"X7"); 		

			default : 	break ; 
		}
	}
	else if(System.Dsp.Mode == VIEW_MODE)
	{
		switch(NUM)
		{
			case X0 :	Select_Send(0x3A); 
						System.Dsp.ViewMode.Zoom = X0 ;
						OSTimeDly(10); break ; //DSP_SENDB(0xe2,NULL,"  "); 		
						
			case X1 : 	Scen_Send(0x33,0x20);  		
						System.Dsp.ViewMode.Zoom = X1 ;		 	
						OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X3"); 		
						 
			case X2 : 	Scen_Send(0x33,0x50);  		
						System.Dsp.ViewMode.Zoom = X2 ;		 	
						OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X5"); 		
						
 			case X3 :   Scen_Send(0x33,0x70);  			
 			 			System.Dsp.ViewMode.Zoom = X3 ;		 	
 			 			OSTimeDly(10); break ;//DSP_SENDB(0xe2,NULL,"X7"); 		

			default : 	break ; 
		}
		
	} 
	//ShowZoom(); 
}


void PhotoZoomUp(void)	   // 照片放大
{


	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		switch(System.Dsp.CheckMode.Zoom)
		{
			case X0 : 	System.Dsp.CheckMode.Zoom = X1 ; break ;		 	
								
						 
			case X1 : 	System.Dsp.CheckMode.Zoom = X2 ; break ;			
						
//			case X2 :   System.Dsp.CheckMode.Zoom = X3 ; break ; 				

			default :  	System.Dsp.CheckMode.Zoom = X0 ; break ; 
		}
		Check_View_Zoom(System.Dsp.CheckMode.Zoom );
	}
	else if(System.Dsp.Mode == VIEW_MODE)
	{
		switch(System.Dsp.ViewMode.Zoom)
		{
			case X0 : 	System.Dsp.ViewMode.Zoom = X1 ;	break ; 		
						 
			case X1 : 	System.Dsp.ViewMode.Zoom = X2 ;	break ; 			
						
//			case X2 :   System.Dsp.ViewMode.Zoom = X3 ; break ; 			

			default : 	System.Dsp.ViewMode.Zoom = X0 ;	break ;
		}
		Check_View_Zoom(System.Dsp.ViewMode.Zoom);
	}
}
void PhotoZoomDown(void)   // 照片缩小
{
//	if(System.Dsp.Mode == VIEW_MODE)
//	{
//		switch(System.Dsp.ViewMode.Zoom)
//		{
//			case X3 :   Scen_Send(0x33,0x30);  		
//						System.Dsp.ViewMode.Zoom = X2 ;		 	
//						OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X3"); 		break ;
//
//			case X2 :   Scen_Send(0x33,0x20);  		
//						System.Dsp.ViewMode.Zoom = X1 ;		 	
//						OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X2"); 		break ;
//
//			case X1 :   Select_Send(0x3A);  		
//						System.Dsp.ViewMode.Zoom = X0 ;		 	
//						OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X1"); 		break ;
//						 
//			default : 	Select_Send(0x3A);   		
//			 			System.Dsp.ViewMode.Zoom = X0 ;		 	
//			 			OSTimeDly(20); DSP_SENDB(0xe2,NULL,"X1"); 		break ;
//		}
//	}
}

void ShowZoom(void)
{	if(System.Dsp.Mode == CHECK_MODE)
	{
		switch(System.Dsp.CheckMode.Zoom)
		{
		 	case X0 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"  "); System.Uart.PlayZom = 0x01 ;  break ;
			case X1 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X3"); System.Uart.PlayZom = 0x02 ; break ;
			case X2 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X5"); System.Uart.PlayZom = 0x02 ;  break ;	
			default :break ;
		}
	}
	if(System.Dsp.Mode == VIEW_MODE)
	{
		switch(System.Dsp.ViewMode.Zoom)
		{
		 	case X0 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"  "); System.Uart.PlayZom = 0x03 ;   break ;
			case X1 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X3"); System.Uart.PlayZom = 0x04 ;   break ;
			case X2 :	OSTimeDly(10);DSP_SENDB(0xe2,NULL,"X5"); System.Uart.PlayZom = 0x04 ;   break ;	
			default :break ;
		}		
	}
}


void PhotoAutoView(void)
{
	if(System.Dsp.ViewMode.CycleView == 0)
	{
	    System.Dsp.ViewMode.CycleView = 1 ; 
	}
	else
	{
		if(System.Dsp.ViewMode.CycleViewPause == 1)
		{
			System.Dsp.ViewMode.CycleViewPause	=0 ; 
		}
		else
		{
			System.Dsp.ViewMode.CycleViewPause	=1 ; 
		}
	}
}

void Zhuanfa(void)
{
		
}

void TimeSet(void)
{
		
}

void UV365_70ExpSet(void)
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Sensor1(); 
		Double_UV_On(); 
		
		Select_Send(0x96); 				 
		OSTimeDly(5);

		DSP_SEND(4, &ADJ_ExpSetFB[0]);
	    OSTimeDly(10); 
		DSP_SEND(4, &ADJ_ExpSetFC[0]);
		OSTimeDly(10); 
		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
		OSTimeDly(300);				
		Scen_Send(0xE6,G_SENCE_DB_UV); 														
		OSTimeDly(400);	
		
		Select_Send(0x96); 				 
		OSTimeDly(5);
		Scen_Send(G_SENCE_DB_UV,0x00);
		OSTimeDly(10);	
		Scen_Send(0xe5, G_SENCE_DB_UV);							
		OSTimeDly(100);	
		Scen_Send(0xE7, G_SENCE_DB_UV); 	
		OSTimeDly(300);
		SHOW_SCREEN(0xE3,"OK\n");
		OSTimeDly(350);
	}
}
void UV365_71ExpSet(void)
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
//		Sensor2(); 	
//	    Double_UV_On();
//
//		DSP_SEND(4, &ADJ_ExpSetFB[0]);
//	    OSTimeDly(10); 
//		DSP_SEND(4, &ADJ_ExpSetFC[0]);
//		OSTimeDly(10); 
//		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
//		OSTimeDly(300);	
//		
//		Select_Send(0x96); 			
//		OSTimeDly(5);	
//		Scen_Send(0xE6, PH_SENCE_TOP_UV_71); 														
//		OSTimeDly(400);		
//
//		Select_Send(0x96); 			
//		OSTimeDly(5);
//		Scen_Send(G_SENCE_DB_UV,0x00);		
//		OSTimeDly(10);	
//		Scen_Send(0xe5,PH_SENCE_TOP_UV_71);							
//		OSTimeDly(100);	
//		Scen_Send(0xE7,PH_SENCE_TOP_UV_71); 	
//		OSTimeDly(300);
//		
//		//DSP_SENDB(0xe2,NULL,"X3"); 	
//	    SHOW_SCREEN(0xE3,"OK\n");	
	}
}

void Format_SDcard(void)
{
	OSTimeDly(5);
	Dsp_Send_Data(0x2D,D_NON,D_NON,D_NON,D_NON);
//	OSTimeDly(200);
//	Dsp_Send_Data(0x28,D_NON,D_NON,D_NON,D_NON);
//	OSTimeDly(200);
//	Dsp_Send_Data(0x2F,D_NON,D_NON,D_NON,D_NON);	
}

void UV365_72ExpSet(void)
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Sensor3(); 	
	    Double_UV_On();
	
		DSP_SEND(4, &ADJ_ExpSetFB[0]);
	    OSTimeDly(10); 
		DSP_SEND(4, &ADJ_ExpSetFC[0]);
		OSTimeDly(10); 
		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
		OSTimeDly(300);	
		
		Select_Send(0x96); 			
		OSTimeDly(5);
		
		Scen_Send(0xE6, G_SENCE_DB_UV); 														
		OSTimeDly(400);		

		Select_Send(0x96); 			
		OSTimeDly(5);
		Scen_Send(G_SENCE_DB_UV,0x00);		
		OSTimeDly(10);	
		Scen_Send(0xe5,G_SENCE_DB_UV);							
		OSTimeDly(100);	
		Scen_Send(0xE7,G_SENCE_DB_UV); 	
		OSTimeDly(300);
		
		//DSP_SENDB(0xe2,NULL,"X3"); 	
	    SHOW_SCREEN(0xE3,"OK\n");
		OSTimeDly(350);	
	}
}
void IR770_72ExpSet(void)
{
//	Sensor3(); 
//	Right_IR770_On(); 
//	OSTimeDly(100);
//	DSP_SEND(4, &ADJ_ExpSetFB[0]);
//    OSTimeDly(10); 
//	DSP_SEND(4, &ADJ_ExpSetFC[0]);
//	OSTimeDly(10); 
//	Scen_Send(0x01,0x03 ) ; 
//	OSTimeDly(300);	
//	
//	Select_Send(0x96); 			
//	OSTimeDly(5);		
//	Scen_Send(0xE6, PH_SENCE_TOP_IR770_72); 														
//	OSTimeDly(400);	
//	
//	Select_Send(0x96); 			
//	OSTimeDly(5);
//	Scen_Send(0x01,0x02);		
//	OSTimeDly(10);	
//	Scen_Send(0xe5,PH_SENCE_TOP_IR770_72);							
//	OSTimeDly(100);	
//	Scen_Send(0xE7,PH_SENCE_TOP_IR770_72); 	
//	OSTimeDly(300);	
//	
//	SHOW_SCREEN(0xE3,"OK\n");
}
void QueryInfo(void)
{

	SystemReadBCKData();  //读取信息	

}

void ModifyInfo(void)
{
	SystemWriteBCKData() ; // 存储信息	   
	GR_DBG_PRINTF("\n\nSystemWriteBCKData \n\n");
}

void MacSleep(void)
{
	if(System.Dsp.Mode == CHECK_MODE||VIEW_MODE)
	{
		System.Dsp.Mode = SLEEP_MODE ; 
		Light_Init() ; 
	//	SHOW_SCREEN(0xE8,  " "); 
	}					  
}
void MacWakeup(void)
{
	System.Key.NoKeyTime = 0 ;	
	if(System.Dsp.Mode == SLEEP_MODE)
	{	
		CheckMode(); 
		OSTimeDly(200) ; 
	}	  		
}
void Slp_enable(void)
{

	System.SleepEnable = 1 ; 

}

void Slp_disable(void)
{

	System.SleepEnable = 0 ; 
	if(System.Dsp.Mode == SLEEP_MODE)
	{	
		CheckMode(); 
		OSTimeDly(200) ; 
	}
}

void Sensor_refresh()
{
    switch(System.Led.Statu)
    {
//    	case ALL_LED_OFF 	: :Light_Init();break ; 
    	//case TOP_WHITE_ON 	:Top_W_On();break ; 
    	//case LEFT_W_ON    	:Left_W_On(); break ; 
    	//case TOP_IR850_ON 	:Top_IR850_On(); break ;   
    	//case TOP_IR940_ON 	:Top_IR940_On(); break ;  
    	//case DB_UV_ON     	:Double_UV_On(); break ;  
    	//case LEFT_IR850_ON  :Left_IR850_On(); break ;  
    	//case BOT_W_ON       :Bot_W_On(); break ; 
    	//case BOT_IR_ON      :Bot_IR_On(); break ; 
    	//	 	  
    	//case RIGHT_W_ON 	:Right_W_On(); break ; 
    	//case RIGHT_IR850_ON	:Right_IR850_On(); break ; 
    	//case LEFT_UV_ON     :Left_UV_On(); break ; 
    	//case RIGHT_UV_ON    :Right_UV_On(); break ; 	 
    	//case DB_WT_UV_ON	:Double_WT_UV_On(); break ; 	 
    	//case DB_UV_EXPOSURE1_ON :if(System.Dsp.Sensor == SENSOR1){Top_W_On();OSTimeDly(100);}
		   //                      	Double_UV_Exposure1_On();  break ; 
    	//case DB_UV_EXPOSURE2_ON :if(System.Dsp.Sensor == SENSOR1){Top_W_On();OSTimeDly(100);}
					//				Double_UV_Exposure2_On(); break ; 
    	//case RIGHT_IR770_ON  :Right_IR770_On();break ; 
    	//case RIGHT_LASER_ON	 :Right_Laser_On();break ; 
    	////case C608_PWR_ON 	 :c608;break ; 
    	//case TOP_IR850_940_BLINK :Top_IR850_940_Blink();break ; 
		default :break ; 
	}
}

/*==================================================================
* Function	: Sensor1
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Sensor1()
{
	if(System.Dsp.Sensor != SENSOR1)
		{
		//	Select_Send(0x70);
			Dsp_Send_Data(0x70,0x00,10,0,0);
		//	Scen_Send(0x70,0x00);
			OSTimeDly(100); 
			Scen_Send(0xC1,0x60);
			OSTimeDly(5); 
			System.Dsp.Sensor = SENSOR1 ; 
			System.Dsp.CheckMode.Zoom = X0 ;
			System.Dsp.ViewMode.Zoom  = X0 ; 
			Sensor_refresh(); 
		 }
}


/*==================================================================
* Function	: Sensor2
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Sensor2()
{
	if(System.Dsp.Sensor != SENSOR2)
	{	
    //	Select_Send(0x71);
	//	Scen_Send(0x71,0x00);
		Dsp_Send_Data(0x71,0x00,0x22,20,150);

	//	Dsp_Send_Data(0x2C,0x20,0x20,120,D_NON);

    	OSTimeDly(100); 
    	Scen_Send(0xC1,0x60);

    	System.Dsp.Sensor = SENSOR2 ; 
    	OSTimeDly(10); 
		System.Dsp.CheckMode.Zoom = X0 ;
		System.Dsp.ViewMode.Zoom  = X0 ; 
		Sensor_refresh(); 
	}
}

/*==================================================================
* Function	: Sensor3
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void Sensor3()
{
	Select_Send(0x72);
	OSTimeDly(200); 
	Scen_Send(0xC1,0x60);
	OSTimeDly(5); 
	System.Dsp.Sensor = SENSOR3 ; 
	OSTimeDly(150); 
	Sensor_refresh(); 
}



/*==================================================================
* Function	: CheckMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void CheckMode()
{
	Key_Led_Init(); 
//	K2_LED = 0 ; 
	if((System.Dsp.Mode == PCCAM_MODE)||(System.Dsp.Mode == TF_MODE))
		{
			Select_Send(0xCE); 
			OSTimeDly(150);

		}
	else if(System.Dsp.Mode == VIEW_MODE)
		{
		 	Select_Send(0x26); 
			OSTimeDly(50);

		}  
	else if(System.Dsp.Mode == SLEEP_MODE )
		{
			Select_Send(0xE9);
			OSTimeDly(50);  
		}
	System.Dsp.Mode = CHECK_MODE ; 

	if(System.Dsp.Sensor != SENSOR1)
		{	
	 		Sensor1();
		} 
	Top_W_On(); 

	Check_View_Zoom(X0) ;
}


/*==================================================================
* Function	: ViewMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void ViewMode()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Light_Init(); 

		Select_Send(0x25);		
		OSTimeDly(50);	
		#ifdef AD_13				   
		System.Dsp.Sensor = NONSENSOR ;
		#elif defined AD_16

		#endif 

		MvtempDec1 = 0 ; 
		MvtempDec = 0 ;

		System.Dsp.Mode = VIEW_MODE ; 
		System.Dsp.ViewMode.Zoom = X0 ;
		System.Uart.PlayZom = 0x03 ; 
//		GR_DBG_PRINTF("IS In ViewMode\n\n");
	}
}

void ViewMode_F1()	//图像
{
	if(System.Dsp.Mode == VIEW_MODE)
	{

 		if(System.Dsp.ViewMode.Zoom != X0 )
		{
			Select_Send(0x3A);		
			OSTimeDly(50);	
			System.Dsp.Mode = VIEW_MODE ; 
			System.Dsp.ViewMode.Zoom = X0 ;

		}
		else
		{
			if(MvtempDec==1)
			{
				PhotoMvRight() ;
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 0 ;} 
				   
			//	  OSTimeDly(100);
			}
			else
			{
				PhotoMvLeft() ;	
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 1 ;} 
					
			//		OSTimeDly(100); 
			}		
		}
   }
}
void ViewMode_F2()	// 号码
{

	if(System.Dsp.Mode == VIEW_MODE)
	{
		if(System.Dsp.ViewMode.Zoom != X2 )
		{
			Dsp_Send_Data(0x33,0x60,0x01,0x42,0x43); 	//23 33 30 01 39 3D AA	//	Dsp_Send_Data(0x33,0x60,0x01,0x42,0x4B); 	//23 33 30 01 39 3D AA			
			OSTimeDly(50);
			System.Dsp.ViewMode.Zoom = X2 ;
		}
		else
		{
			if(MvtempDec==1)
			{
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 0 ;} 
			//	  PhotoMvRight() ; 
			Dsp_Send_Data(0x2B,0x60,0x01,0x42,0x43);//	Dsp_Send_Data(0x2B,0x60,0x01,0x42,0x4B);
		//	OSTimeDly(100);
			}
			else
			{
				if(++MvtempDec1>=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 1 ;} 
			//	PhotoMvLeft() ;	 	232A3001393DAA
				Dsp_Send_Data(0x2A,0x60,0x01,0x42,0x43);//   	Dsp_Send_Data(0x2A,0x60,0x01,0x42,0x4B);	   增大向左移下移
			//	OSTimeDly(100);
			}						
		}
	}

}
void ViewMode_F3()	// 大写金额
{ 
	if(System.Dsp.Mode == VIEW_MODE)
	{
		if(System.Dsp.ViewMode.Zoom != X3 )
		{
			Dsp_Send_Data(0x33,0x60,0x00,0x22,0x08); 		//23 33 30 01 39 3D AA			
			OSTimeDly(50);
			System.Dsp.ViewMode.Zoom = X3 ;

		}
		else
		{
			if(MvtempDec == 1)
			{
				if(++MvtempDec1 >= System.PhotoNum-1) 
				{
					MvtempDec1 = 0 ; MvtempDec = 0 ;
				} 
				Dsp_Send_Data(0x2B,0x60,0x00,0x22,0x08); 		//  Dsp_Send_Data(0x2B,0x40,0x00,0x1F,0x08); 
			//	OSTimeDly(100);
			}
			else
			{
				if(++MvtempDec1 >=System.PhotoNum-1) 
				{
					MvtempDec1 = 0 ; MvtempDec = 1 ;
				} 
			   	Dsp_Send_Data(0x2A,0x60,0x00,0x22,0x08); 
			//	OSTimeDly(100);
			}						
		}
	}
 	
}
void ViewMode_F4()	//数字 小写金额
{
	if(System.Dsp.Mode == VIEW_MODE)
	{
		if(System.Dsp.ViewMode.Zoom != X4 )
		{
			Dsp_Send_Data(0x33,0x60,0x01,0x30,0x8);
			OSTimeDly(50);
			System.Dsp.ViewMode.Zoom = X4 ;
		}
		else
		{
			if(MvtempDec ==1)
			{
				if(++MvtempDec1 >=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 0 ;} 
			//	  PhotoMvRight() ; 
				Dsp_Send_Data(0x2B,0x60,0x01,0x30,0x8);
			//	OSTimeDly(100);
			}
			else
			{
				if(++MvtempDec1 >=System.PhotoNum-1) {MvtempDec1 = 0 ; MvtempDec = 1 ;} 
			//	PhotoMvLeft() ;	 	232A3001393DAA
			   	Dsp_Send_Data(0x2A,0x60,0x01,0x30,0x08);
			//	OSTimeDly(100);
			}						
		}
	}

	
//	if(System.Dsp.Mode == CHECK_MODE)
//	{
//		Light_Init(); 
//
////		Select_Send(0x25);		
//		
//
//
//		MvtempDec1 = 0 ; 
//		MvtempDec = 0 ;
//
//		System.Dsp.Mode = VIEW_MODE ; 
//		System.Dsp.ViewMode.Zoom = X0 ;
//		System.Uart.PlayZom = 0x03 ; 
////		GR_DBG_PRINTF("IS In ViewMode\n\n");
//	}
}

/*==================================================================
* Function	: PccamMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PccamMode()
{
	if(USB_STATUS == USB_OUT)
	{
		  SHOW_SCREEN(0xE3,"USB NOT READY\n");
		  OSTimeDly(350) ; 
		  System.Usb.NewUsbStatu =	   System.Usb.OldUsbStatu  ;
		 // CheckMode(); 	
		  return ; 	
	}

	if (System.Dsp.Mode == TF_MODE)
	{
		CheckMode(); 
	}
	if(System.Dsp.Mode == CHECK_MODE)
	{
		OSTimeDly(100) ;
		Select_Send(0xCD); 
		OSTimeDly(200) ;
		System.Dsp.Mode = PCCAM_MODE ; 
	}
}

/*==================================================================
* Function	: TfMode
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void TfMode()
{

	if(USB_STATUS == USB_OUT)
	{
		  SHOW_SCREEN(0xE3,"USB NOT READY\n");
		  System.Usb.NewUsbStatu =	  System.Usb.OldUsbStatu  ;
		  OSTimeDly(350) ; 	
		  //CheckMode(); 	
		  return ; 	
	}
	if(System.Dsp.Mode == PCCAM_MODE)
	{
		CheckMode(); 
	}

	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == VIEW_MODE))
	{
		System.Dsp.Mode = TF_MODE ; 

		Select_Send(0xCC);				//U盘
		Light_Init() ; 
		OSTimeDly(10);	
	}
}


/*==================================================================
* Function	: PhotographOne
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
#ifdef AD_13
void PhotographOne()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		Select_Send(0x96); 				//单独拍照分组。和连拍区分开来！
		OSTimeDly(5);
		Select_Send(0x21); 					
		OSTimeDly(120);	
	}
}
#elif defined AD_16
void PhotographOne()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
		
		Select_Send(0x96); 				//单独拍照分组。和连拍区分开来！
		OSTimeDly(5);

		if(System.Led.Statu == RIGHT_ASK_BLINK)
		{
			System.Led.Statu = ALL_LED_OFF ; 
		    RIGHT_LASER = 0 ; 
			Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
			OSTimeDly(200);	
			System.Led.Statu = RIGHT_ASK_BLINK ; 
			pFuc(); 
			return ;
		}						
		Dsp_Send_Data(0x21,0x00,0x01,0x01,D_NON);
		OSTimeDly(200);	
		pFuc(); 
		//ShowZoom();
	}
}
#endif 





/*==================================================================
* Function	: PhotographEight
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotographEight()
{
	if(System.Dsp.Mode == CHECK_MODE)
	{
			SHOW_SCREEN(0xE8,"Wait..." );
			OSTimeDly(10);
			if(System.Dsp.Sensor != SENSOR2)
			{
				Sensor2(); 
			}	
	/*----------------------------------------------------*/  //侧白				
			Right_IR850_On();   							
			Select_Send(0x21);	
			OSTimeDly(200);

	/*----------------------------------------------------*///紫光				 
//			Double_UV_On();	 
//			Scen_Send(0xe5,PH_SENCE_TOP_UV_71);
//			OSTimeDly(100);	
//			Scen_Send(0xE7, PH_SENCE_TOP_UV_71); 	
//			OSTimeDly(300);
	/*----------------------------------------------------*///侧红外
			Right_IR850_On(); 
			OSTimeDly(100);
		    Select_Send(0x21); 
			OSTimeDly(200); 	

	/*----------------------------------------------------*///底红外															 
			Bot_IR_On();	
			OSTimeDly(160); 		
			Select_Send(0x21); 													
		 	OSTimeDly(200);			

	/*----------------------------------------------------*///sensor3		
//			Sensor3();						
//	/*----------------------------------------------------*///顶白光									
//			Top_W_On(); 
//			OSTimeDly(100);
//			Select_Send(0x21); 								//拍照
//			OSTimeDly(250);
//	/*----------------------------------------------------*///侧白光
//			Right_W_On(); 
//			OSTimeDly(200);
//		    Select_Send(0x21); 
//			OSTimeDly(200); 	
//	/*----------------------------------------------------*///紫光
//			Double_UV_On(); 
//			OSTimeDly(10);	
//			Scen_Send(0xe5,PH_SENCE_TOP_UV_72);
//			
//			OSTimeDly(100);	
//			Scen_Send(0xE7, PH_SENCE_TOP_UV_72); 	
//			OSTimeDly(300);
//	/*----------------------------------------------------*/ //IR					
//										 
//			Right_IR770_On(); 
//			OSTimeDly(200);
//			Select_Send(0x21); 													
//		 	OSTimeDly(200);			
//			
//	/*----------------------------------------------------*/
			CheckMode(); 
			
	 	//	Select_Send(0xE9); // 结束等待显示 
	}			
}

/*==================================================================
* Function	: PhotoDelOne
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoDelOne()
{
	if((System.Dsp.Mode == VIEW_MODE)
		&&(System.Dsp.ViewMode.Zoom == X0))
	{
		Select_Send(0x3C);
		OSTimeDly(200);	
	}
}
void PhotographFour_Sign()
{
	
}

void PhotographFour()
{
	
	if(System.Dsp.Mode == CHECK_MODE)
	{

	  //  Select_Send(0xE9); // 结束等待显示	
//		OSTimeDly(50) ; 
	}
}

/*==================================================================
* Function	: PhotoDelAll
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PhotoDelAll(void) //(uint8_t KeyValue) 
{
	if((System.Dsp.Mode == VIEW_MODE)
		&&(System.Dsp.ViewMode.Zoom == X0))
	{

		Select_Send_LONG(0x24);			
		OSTimeDly(300); 	   		
	}	
}



/*==================================================================
* Function	: PriorExposure
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void PriorExposure()
{



	if(System.Dsp.Mode == CHECK_MODE)
	{		
			CheckMode(); 

//			//重发 ，第一次可能曝光
//			DSP_SEND(4, &TW_Snr1EV_FB[0]);
//      		OSTimeDly(10); 
//			DSP_SEND(4, &TW_Snr1EV_FC[0]);
//			OSTimeDly(10); 
//			Scen_Send(0xD8,0x80) ;
//			OSTimeDly(10); 
//			Dsp_Send_Data(0xFF,G_SENCE_WT,0xAF,0x78,D_NON);
////			Scen_Send(0xD8,0x00) ;
////			Dsp_Send_Data(0xFF,G_SENCE_WT,0x00,0x00,D_NON);	
//				
//				
//			OSTimeDly(20); 

//			Scen_Send(G_SENCE_WT,0x01 ) ; 
//			OSTimeDly(300);	
//		//	OSTimeDly(300);
//			Scen_Send(0xE6, G_SENCE_WT); 
//			OSTimeDly(300);
//			Scen_Send(0xD8,0x00) ;
///////////////////////////////////////////////////////
////			Scen_Send(0xE6, PH_SENCE_R_IR850); 
////			OSTimeDly(300);
//			Left_IR850_On();
//			DSP_SEND(4, &L_IR_Snr1EV_FB[0]);
//      		OSTimeDly(10); 
//			DSP_SEND(4, &L_IR_Snr1EV_FC[0]);
//			OSTimeDly(10); 
//			Scen_Send(G_SENCE_L_IR,0x01 ) ; 
//			OSTimeDly(300);	
//		//	OSTimeDly(300);
//			Scen_Send(0xE6, G_SENCE_L_IR); 
//			OSTimeDly(300);
/////////////////////////////////////////////////////////////////
//			Top_IR940_On();
//			OSTimeDly(100); 
//
//			Dsp_Send_Data(0xFF,G_SENCE_T_IR940,0x50,0xD1,D_NON);
//
//////			DSP_SEND(4, &IR940_Snr1EV_FB[0]);
//////      		OSTimeDly(10); 
//////			DSP_SEND(4, &IR940_Snr1EV_FC[0]);
//////			OSTimeDly(100); 
//////			Scen_Send(G_SENCE_T_IR940,0x03 ) ; 
//			OSTimeDly(300);	
//		//	OSTimeDly(300);
//			Scen_Send(0xE6, G_SENCE_T_IR940); 
//			OSTimeDly(300);

/*----------------------------------------------------*/ //紫光
//		 	Double_UV_On();
//			OSTimeDly(300);		
//			Select_Send(0x96);			 
//			OSTimeDly(10);
//			Scen_Send(0xE6, G_SENCE_DB_UV); 														
//			OSTimeDly(600);		
//		 	Double_UV_On();
// 
//			Scen_Send(0x50,0x25 ) ; 
//			OSTimeDly(10); 
//			Scen_Send(0xD8,0xF1) ; 	
//		    Dsp_Send_Data(0xFF,G_SENCE_DB_UV,0xA0,0x70,D_NON);
//			//OSTimeDly(10); 
//
//			DSP_SEND(4, &UV_Snr1EV_FB[0]);
//      		OSTimeDly(10); 
//			DSP_SEND(4, &UV_Snr1EV_FC[0]);
//			OSTimeDly(10); 
//			Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
//			OSTimeDly(300);		
//			
//			Select_Send(0x96);			 
//			OSTimeDly(10);
//			Scen_Send(0xE6, G_SENCE_DB_UV); 														
//			OSTimeDly(600);	
//
//			Scen_Send(0x50,0x01) ;
//			Scen_Send(0xD8,0x80) ; 	 	
////			Dsp_Send_Data(0xFF,0x01,0x80,0x80,0x80);
//			OSTimeDly(10); 

			CheckMode(); 

	}

}



void Vir_Init()
{
//	System.Key.Value = 0 ; 
//	
//	System.Led.Statu = TOP_WHITE_ON ; 
//	
//	System.Dsp.Mode = CHECK_MODE; 
//
//	
//	System.Dsp.CheckMode.Zoom = X0 ; 
//	System.Dsp.ViewMode.Zoom  = X0 ; 
//	System.Dsp.TF_Mode.t = 0 ; 
//	System.Dsp.PccamMode.ConnectIn = 0 ; 
//	System.Dsp.Sensor =SENSOR1 ; 
//	System.Dsp.SD = OUT ; 
//	System.Usb.NewUsbStatu 	= USB_OUT; 
//	System.Usb.OldUsbStatu 	= USB_OUT;  
//	System.Usb.UsbStatuLabel= 0 ;
//	
//	System.Sys.PassWrd.Code[0] = 1 ; 
//	System.Sys.PassWrd.Code[1] = 2 ; 
//	System.Sys.PassWrd.Code[2] = 3 ;
//	System.Sys.PassWrd.Code[3] = 4 ; 
////
//	System.Sys.PassWrd.InputErrCount = 0 ; 
//	System.Sys.PassWrd.LockTime	= 0 ; 
//	System.Sys.SaveInfoFlag = 1 ; 
	System.Sys.NonFirstTimeUseFlag = 0x01 ; 
	System.Led.Pwm_IR940.Duty	=12	;
	System.Led.Pwm_IR850.Duty	=12 ;


//	System.Sys.Data.info.SoftwareVer[0]	 =SysVersion[0];	//V1.02.016
// 	System.Sys.Data.info.SoftwareVer[1]	 =SysVersion[1];
//	System.Sys.Data.info.SoftwareVer[2]	 =SysVersion[2];  
//
// 	System.Sys.Data.info.HardwareVer[0]	 =0x56312E31;	//V1.14.001
// 	System.Sys.Data.info.HardwareVer[1]	 =0x342E3030;
//	System.Sys.Data.info.HardwareVer[2]	 =0x31000000; 
//
// 	System.Sys.Data.info.MachineType[0]	 =0x41442D31; 
// 	System.Sys.Data.info.MachineType[1]	 =0x36000000;
//	System.Sys.Data.info.MachineType[2]	 =0x30000000;  
//
//  	System.Sys.Data.info.CdKey[0]	 =0x30313233; 	 //序列号 
// 	System.Sys.Data.info.CdKey[1]	 =0x34353637;
//	System.Sys.Data.info.CdKey[2]	 =0x38000000;  
//
//  	System.Sys.Data.info.MachineNum[0]	 =0x30313233; 	 //编号
// 	System.Sys.Data.info.MachineNum[1]	 =0x34353637;
//	System.Sys.Data.info.MachineNum[2]	 =0x38000000;  
//
//   	System.Sys.Data.info.ProductDate[0]	 =0x32303134; 	 //生产日期
// 	System.Sys.Data.info.ProductDate[1]	 =0x30343138;
//	System.Sys.Data.info.ProductDate[2]	 =0x33000000;  

	System.Error = NON ; 

//	ADJ_ExpSetFB[0]=0xFB ; 
//	ADJ_ExpSetFB[1]=0x01 ; 
//	ADJ_ExpSetFB[2]=0x20 ; 
//	ADJ_ExpSetFB[3]=0x20 ; 
//
//	ADJ_ExpSetFC[0]=0xFC ; 
//	ADJ_ExpSetFC[1]=0x01 ; 
//	ADJ_ExpSetFC[2]=0x18 ; 
//	ADJ_ExpSetFC[3]=0x18 ; 		

//	date[6] = 0x13;  
//	date[5] = 0x01; 
//	date[4] = 0x01;
//	date[3] = 0x01;
//	date[2] = 0x01; 
//	date[1] = 0x01;
//	date[0] = 0x01;
//    DS1307_WR(&date[0]); 
}

void Vir_Init_Update()
{
	System.Key.Value = 0 ; 
	
	System.Led.Statu = TOP_WHITE_ON ; 
	
	System.Dsp.Mode = CHECK_MODE; 

	
	System.Dsp.CheckMode.Zoom = X0 ; 
	System.Dsp.ViewMode.Zoom  = X0 ; 
	System.Dsp.TF_Mode.t = 0 ; 
	System.Dsp.PccamMode.ConnectIn = 0 ; 
	System.Dsp.Sensor =SENSOR1 ; 
	System.Dsp.SD = OUT ; 
	System.Usb.NewUsbStatu 	= USB_OUT; 
	System.Usb.OldUsbStatu 	= USB_OUT;  
	System.Usb.UsbStatuLabel= 0 ;
	 //升级固件不恢复密码
//	System.Sys.PassWrd.Code[0] = 1 ; 
//	System.Sys.PassWrd.Code[1] = 2 ; 
//	System.Sys.PassWrd.Code[2] = 3 ;
//	System.Sys.PassWrd.Code[3] = 4 ; 

	System.Sys.PassWrd.LockTime	= 0 ; 
	System.Sys.SaveInfoFlag = 0 ; 
	System.Sys.NonFirstTimeUseFlag = 0x01 ; 

	System.Sys.Data.info.SoftwareVer[0]	 =SysVersion[0];	 
 	System.Sys.Data.info.SoftwareVer[1]	 =SysVersion[1];
	System.Sys.Data.info.SoftwareVer[2]	 =SysVersion[2];  
	 //升级固件恢复存储信息
 	System.Sys.Data.info.HardwareVer[0]	 =0x56312E31;	//V1.14.001
 	System.Sys.Data.info.HardwareVer[1]	 =0x342E3030;
	System.Sys.Data.info.HardwareVer[2]	 =0x31000000; 

 	System.Sys.Data.info.MachineType[0]	 =0x41442D31; 
 	System.Sys.Data.info.MachineType[1]	 =0x36000000;
	System.Sys.Data.info.MachineType[2]	 =0x30000000;  

//  	System.Sys.Data.info.CdKey[0]	 =0x30313233; 	 //序列号 
// 	System.Sys.Data.info.CdKey[1]	 =0x34353637;
//	System.Sys.Data.info.CdKey[2]	 =0x38000000;  
//
//  	System.Sys.Data.info.MachineNum[0]	 =0x30313233; 	 //编号
// 	System.Sys.Data.info.MachineNum[1]	 =0x34353637;
//	System.Sys.Data.info.MachineNum[2]	 =0x38000000;  
//
//   	System.Sys.Data.info.ProductDate[0]	 =0x32303133; 	 //生产日期
// 	System.Sys.Data.info.ProductDate[1]	 =0x31323039;
//	System.Sys.Data.info.ProductDate[2]	 =0x33000000;  

	System.Error = NON ; 

//	ADJ_ExpSetFB[0]=0xFB ; 
//	ADJ_ExpSetFB[1]=0x01 ; 
//	ADJ_ExpSetFB[2]=0x20 ; 
//	ADJ_ExpSetFB[3]=0x20 ; 
//
//	ADJ_ExpSetFC[0]=0xFC ; 
//	ADJ_ExpSetFC[1]=0x01 ; 
//	ADJ_ExpSetFC[2]=0x18 ; 
//	ADJ_ExpSetFC[3]=0x18 ; 		

//	date[6] = 0x13;  
//	date[5] = 0x01; 
//	date[4] = 0x01;
//	date[3] = 0x01;
//	date[2] = 0x01; 
//	date[1] = 0x01;
//	date[0] = 0x01;
//  DS1307_WR(&date[0]); 
}
/*==================================================================
* Function	: PasswdFuc
* Description	: 按键输入密码操作
* Input Para	: 	keyReturnValue : 输入返回的按键键值 
					void (*Fuc)(void) 按键返回的场景  
					void (*PasswdFinish)() 密码输入成功后的场景
* Output Para	: 
* Return Value: 
==================================================================*/
void VerifyPassword(uint8_t keyReturnValue,void (*Fuc)(),void (*PasswdFinish)() )
{   
	uint16_t nonBtnDwnTime = 0 ; 
	uint8_t i = 0 ; 
	uint8_t InputPasswdLength=0 ; 
	uint32_t temp = 0 ;
	uint8_t PassWord[PASSWORD_LENGTH]; 

	
	//判别错误输入次数
	if(System.Sys.PassWrd.InputErrCount  >= INPUT_ERR_TIME_MAX)
	{
		SHOW_SCREEN(0xE3,"Password Locked");
		OSTimeDly(300) ;
		return ; 
	}
	//初始化

	Light_Init(); 

//	DS1307_RD(&date[0]); 
//	temp = sTime(NowTime) ;
// 	System.Sys.PassWrd.InputLength = 0 ; 
// 	System.Sys.PassWrd.InputErrCount = 0 ;  //连续输入几次密码退回后仍有效

	for(i=0;i<PASSWORD_LENGTH;i++)
	{
		PassWord[i] = 0 ;
	} //System.Sys.PassWrd.InputCode[i] = 0x00 ;
	
	SHOW_SCREENA(0xE8,(16),"Enter Password:\nXXXXXXXX");

	while(KeyScan()); 
	while(nonBtnDwnTime++ <= 65535)
	{	//按键扫描
		System.Key.Value = KeyScan();  
		System.Key.Keylong = &Keylong ;
		//键值处理
		if(System.Key.Value)
		{    
			
			nonBtnDwnTime = 0 ; 
 			if(System.Key.Value == keyReturnValue)
			{
				if(*System.Key.Keylong)
				{ 
				
				}
				else
				{
				  GR_DBG_PRINTF("exit the viewMode\n\n"); break ; 
				}
				
			} 
			else
			{
				PassWord[InputPasswdLength++] = System.Key.Value;
				SHOW_SCREENA(0xE8,(16+InputPasswdLength),"Enter Password:\nXXXXXXXX"); 
			}
		}	
		//键值判断
		if(InputPasswdLength == PASSWORD_LENGTH)
		{
			InputPasswdLength = 0 ;  //初始化长度，防止二次判断密码 。 
			for(i=0 ; i<PASSWORD_LENGTH;i++)
			{
				if(PassWord[i] == System.Sys.PassWrd.Code[i])
				{
					if(i == (PASSWORD_LENGTH - 1))
					{
						System.Sys.PassWrd.InputErrCount = 0 ; 
						Select_Send(0xE9);
						(*PasswdFinish)();
						//OSTimeDly(200); 
						GR_DBG_PRINTF("Machine is in viewMode\n\n") ; 
						return ; 
					}
				}
				else
				{
					SHOW_SCREEN(0xE8,  "Password Error"); 
					OSTimeDly(50);
					GR_DBG_PRINTF("AAASystem.Sys.PassWrd.InputErrCount is :%d",System.Sys.PassWrd.InputErrCount);	
					if(++System.Sys.PassWrd.InputErrCount >= INPUT_ERR_TIME_MAX)
					{
						
//						DS1307_RD(&date[0]); 
//					 	System.Sys.PassWrd.LockTime = sTime(NowTime) ;
						temp = System.Sys.PassWrd.LockTime - temp ; 

						if(temp <= 2 ) 	//防止在DS1307没电的时候不能读出信息
						{	
							System.Sys.PassWrd.InputErrCount = 0 ;  
						}
 						System.Sys.SaveInfoFlag = 1 ; 			//存储密码锁定信息 。 			
						Select_Send(0xE9);	
						(*Fuc)() ; 
						return ;   
					} 
					SHOW_SCREENA(0xE8,(16),"Enter Password:\nXXXXXXXX");
					break; 
			 	}
			}
		
		}
		OSTimeDly(5) ;
	}
	Select_Send(0xE9);	
	(*Fuc)() ; 
	return ;  
}
/*==================================================================
* Function	: ChangePassWord
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
void ChangePassWord()//(uint8_t keyReturnValue)
{
	uint16_t nonBtnDwnTime = 0 ; 
	uint8_t i = 0 ; 
	uint8_t PassWord1[PASSWORD_LENGTH], PassWord2[PASSWORD_LENGTH];
	uint8_t InputPasswdLength=0 ; 
	
//	System.Sys.PassWrd.InputLength = 0 ; 
//	System.Sys.PassWrd.InputErrCount = 0 ; 
	for(i=0;i<PASSWORD_LENGTH;i++)   
	{
		PassWord1[i]= 0 ; 
		PassWord2[i]= 0 ; 
	}
	SHOW_SCREENA(0xE8,20,"Enter New Password:\nXXXX"); 
	while(nonBtnDwnTime<62225)
	{
		System.Key.Value = KeyScan();
		System.Key.Keylong = &Keylong ; 
		if(System.Key.Value) 
		{	
			nonBtnDwnTime = 0 ; 
			
			if(System.Key.Value == 7)
			{
				continue ; 
			}	
			if(System.Key.Value== 9)//keyReturnValue )
			{
				if(System.Key.Keylong)
				{ 
					Select_Send(0xE9); return ; 		  
				}
			}
			else
			{
				PassWord1[InputPasswdLength++] = System.Key.Value;
				SHOW_SCREENA(0xE8,(20+InputPasswdLength),"Enter New Password:\nXXXXXXXX"); 
			}
			if(InputPasswdLength == PASSWORD_LENGTH)
			{
				break ; 
			}
		}
	}
	OSTimeDly(10); 
	if(InputPasswdLength == PASSWORD_LENGTH)
	{
		nonBtnDwnTime = 0 ; 
		InputPasswdLength = 0 ; 
		SHOW_SCREENA(0xE8,13,"Enter Again:\nXXXXXXXX");	
		while(nonBtnDwnTime<62225)	
		{
			System.Key.Value = KeyScan();
			System.Key.Keylong = &Keylong ; 
			if(System.Key.Value) 
			{	
				nonBtnDwnTime = 0 ; 
				
				if(System.Key.Value == 7)
				{
					continue ; 
				}	
				if(System.Key.Value== 9)//keyReturnValue )
				{
					if(System.Key.Keylong)
					{ 
						Select_Send(0xE9); return ; 		  
					}
				}
				else
				{
					PassWord2[InputPasswdLength++] = System.Key.Value;
					SHOW_SCREENA(0xE8,(13+InputPasswdLength),"Enter Again:\nXXXXXXXX");	
				}
				if(InputPasswdLength == PASSWORD_LENGTH)
				{
					InputPasswdLength  = 0 ; 
					for(i=0;i<PASSWORD_LENGTH;i++)
					{
						if(PassWord1[i] == PassWord2[i])
						{
							if(i == PASSWORD_LENGTH - 1)
							{
								for(i = 0 ;i< PASSWORD_LENGTH ;i++)     // 成功 ---保存密码
								{
									System.Sys.PassWrd.Code[i] = PassWord1[i];
								}
 								System.Sys.SaveInfoFlag = 1 ; 			//保存

								SHOW_SCREEN(0xE8,"Succeed"); 
								OSTimeDly(100); 
								Select_Send(0xE9); return ; 
							}
						}
						else
						{
							SHOW_SCREEN(0xE8,"Failed"); 
							OSTimeDly(100); 
							Select_Send(0xE9); return ; 
						}
					}
				}
			}
			OSTimeDly(10); 
		}
	}
	Select_Send(0xE9); return ;  
}

/*=================================================================================
* Function	: SystemReadBCKData
* Description	: 读取系统保存信息内容
* Input Para	: 
* Output Para	: 
* Return Value: 
=================================================================================*/
void SystemReadBCKData()
{
	
	uint32_t DataAddrPasswd,Temp;
	uint8_t  i= 0  ; 
	UNLOCKREG();
	DrvFMC_EnableISP();
 	DataAddrPasswd = DrvFMC_ReadDataFlashBaseAddr()+PAGE_SIZE*0;
	
	for(i=0;i<21;i++)
	{
 		DrvFMC_Read ((DataAddrPasswd+i*4),  &Temp)	; 
		System.Sys.Data.SysData[i] = Temp ; 
	}

	for(i=0;i<PASSWORD_LENGTH;i++) 
 	{
 		DrvFMC_Read ((DataAddrPasswd +21*4+i*4), &Temp);
		System.Sys.PassWrd.Code[i] = Temp ;
	}	
	
	{ DrvFMC_Read ((DataAddrPasswd+30*4), &Temp); System.Sys.PassWrd.InputErrCount=(uint8_t)Temp  ;}
	{ DrvFMC_Read ((DataAddrPasswd+31*4), &Temp); System.Sys.PassWrd.LockTime = Temp	;}
	{ DrvFMC_Read ((DataAddrPasswd+32*4), &Temp); System.Sys.NonFirstTimeUseFlag	=(uint8_t)Temp;}	

	for(i=0;i<30;i++) 
 	{
 		DrvFMC_Read ((DataAddrPasswd +33*4+i*4), &Temp);
		System.Dsp.photo.photo[i] = Temp ;
	}
	{ DrvFMC_Read ((DataAddrPasswd+63*4), &Temp); System.PhotoNum 	=(uint8_t)Temp;}	
	{ DrvFMC_Read ((DataAddrPasswd+64*4), &Temp); System.Led.Pwm_IR940.Duty =(uint8_t)Temp;}	
	{ DrvFMC_Read ((DataAddrPasswd+65*4), &Temp); System.Led.Pwm_IR850.Duty =(uint8_t)Temp;}	
	
	DrvFMC_DisableISP();
	LOCKREG();		
}


/*=================================================================================
* Function	: SysteWriteBCKData
* Description	: 
* Input Para	: 
* Output Para	: __________OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
* Return Value: 
=================================================================================*/
void SystemWriteBCKData() 
{
	uint32_t DataAddrPasswd,Temp;
	uint8_t  i= 0  ; 

	UNLOCKREG();
	DrvFMC_EnableISP();	
	DataAddrPasswd = DrvFMC_ReadDataFlashBaseAddr()+PAGE_SIZE*0;
	DrvFMC_Erase (DataAddrPasswd ); 
	
	 for(i=0;i<21;i++)
	 {
	 	Temp = System.Sys.Data.SysData[i]; 
		DrvFMC_Write ((DataAddrPasswd+i*4), Temp);
	 }




	for(i=0;i<PASSWORD_LENGTH;i++) 
		{
			Temp = System.Sys.PassWrd.Code[i] ;
			DrvFMC_Write ((DataAddrPasswd+21*4+i*4), Temp);
		}

 //	DataAddrPasswd = DrvFMC_ReadDataFlashBaseAddr()+PAGE_SIZE*1;
//	DrvFMC_Erase (DataAddrPasswd ); 
	{Temp = (uint32_t)System.Sys.PassWrd.InputErrCount  ;DrvFMC_Write ((DataAddrPasswd+30*4), Temp);}
	{Temp =  System.Sys.PassWrd.LockTime	    		;DrvFMC_Write ((DataAddrPasswd+31*4), Temp);}
	{Temp = (uint32_t)System.Sys.NonFirstTimeUseFlag    ;DrvFMC_Write ((DataAddrPasswd+32*4), Temp);}		

	 for(i=0;i<30;i++)
	 {
	 	Temp = System.Dsp.photo.photo[i] ; 
		DrvFMC_Write ((DataAddrPasswd+33*4+i*4), Temp);
	 }

	{Temp = (uint32_t)System.PhotoNum    ;DrvFMC_Write ((DataAddrPasswd+63*4), Temp);}	 

	{Temp = (uint32_t)System.Led.Pwm_IR940.Duty ; DrvFMC_Write ((DataAddrPasswd+64*4), Temp);}	
	{Temp = (uint32_t)System.Led.Pwm_IR850.Duty ; DrvFMC_Write ((DataAddrPasswd+65*4), Temp);}
	DrvFMC_DisableISP();
	LOCKREG();		
	

 	System.Sys.SaveInfoFlag = 0x00 ; 
}

void ConfigBCK() 
{	
	SystemReadBCKData(); 
 	if(  System.Sys.NonFirstTimeUseFlag != 0x01)   //第一次初始化
	//	||(System.Sys.Data.info.SoftwareVer[0]	!=SysVersion[0])
	//	||(System.Sys.Data.info.SoftwareVer[1]	!=SysVersion[1])
	//    ||(System.Sys.Data.info.SoftwareVer[2]	!=SysVersion[2]) )
	{
//		OSTimeDly(300); 
//		SHOW_SCREEN(0xe3,"Init Environment");

		//V1.02.016
 	
 


		Vir_Init() ;
		//初始化所有变量内容
 		System.Sys.SaveInfoFlag = 1 ; 
//		OSTimeDly(300); 
//		PriorExposure() ; 
	//	Select_Send(0xE9);
	}

// 	if(   (System.Sys.Data.info.SoftwareVer[0]	!=SysVersion[0])   //程序升级
//    	||(System.Sys.Data.info.SoftwareVer[1]	!=SysVersion[1])
//        ||(System.Sys.Data.info.SoftwareVer[2]	!=SysVersion[2]) )
//	{
//		OSTimeDly(300); 
//		SHOW_SCREEN(0xe3,"Update Firmware");
//	//	SHOW_SCREENW(0xE3, WcharToChar(L"固件升级") ); 
//		Vir_Init_Update();
//		//初始化所有变量内容
// 		System.Sys.SaveInfoFlag = 1 ; 
//		OSTimeDly(300); 
//	//	Select_Send(0xE9);
//	}


}
void CycleViewFuc()
{
//	K4_LED	= ~K4_LED ; 
		
	 if(System.Dsp.ViewMode.CycleView== 1)			 // In the CycleViewMode 
	 {
		if(System.Dsp.Mode != VIEW_MODE)
		{
			System.Dsp.ViewMode.CycleView = 0 ;	 return ; 
		}	
			 
	 	if(System.Dsp.ViewMode.CycleViewPause == 0)		 //Pause 
	 	{
	      	if((System.Dsp.Mode == VIEW_MODE)&&(System.Dsp.ViewMode.Zoom == X0))
			{
				Select_Send(0x2b);OSTimeDly(50);   
			}	
		}
	 }
 	 OSTimeDly(50); 
}
void AdcIntCallback(uint32_t u32UserData)
{
	gu8AdcIntFlag =1;		
}


/*==================================================================
* Function	: ADC_Dispose
* Description	: OneSingleMode
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
uint32_t  ADC_Dispose(uint8_t Channel)
{	
	uint32_t i32ConversionData  ;  
	UNLOCKREG(x);
 	 
	DrvADC_Open(ADC_SINGLE_END, ADC_SINGLE_OP, 0, EXTERNAL_12MHZ, 3);	
//	GR_DBG_PRINTF("\n\nConversion rate: %d samples/second\n", DrvADC_GetConversionRate());
	DrvADC_SetADCOperationMode(ADC_SINGLE_OP);		 			/* Set the ADC operation mode as single mode */

	DrvADC_SetADCInputMode(ADC_SINGLE_END);	 		     		/* Set the ADC input mode */
	
	DrvADC_SetADCChannel((1<<Channel), ADC_SINGLE_END);			/* Set the ADC channel */												 	 		
    gu8AdcIntFlag = 0;	   	
    DrvADC_EnableADCInt(AdcIntCallback, 0);						  
    DrvADC_StartConvert();									    /* Start A/D conversion */
 
		
    while(gu8AdcIntFlag==0)/* 应该设定操作步骤*/;     DrvADC_DisableADCInt(); 			/* Wait ADC interrupt */ 
	i32ConversionData = DrvADC_GetConversionData(Channel);
    OSTimeDly(1) ;														 

 	DrvADC_Close();
	LOCKREG(x);
	return 	 i32ConversionData ; 
}


/*==================================================================
* Function	: MedianFilter
* Description	: 
* Input Para	: 1参与运算的数组 
                  2数组长度
* Output Para	: 平均值
* Return Value: 
==================================================================*/
uint32_t MedianFilter(uint32_t *Array, uint8_t Num )
{
	uint8_t i = 0 ,j = 0 ;
	uint32_t Sum =0;
	
	for( i=0 ; i<Num;i++ )
	{
		for( j=i;j<Num;j++ )
		{
			 
			uint32_t  m = *(Array+i)<*(Array+j)? *(Array+i):*(Array+j) ; 
			*(Array+j)= *(Array+i)>*(Array+j)? *(Array+i):*(Array+j) ;
			*(Array+i)= m ; 
		}
		//GR_DBG_PRINTF("Array[%d] is : %d\n\n", i ,*(Array+i));
	}
  	for(i=1 ;i<Num-1;i++)
  	{
		Sum += *(Array+i); 
	}
	return Sum/(Num-2) ; 	
}
/*==================================================================
* Function	: ADC_Checking
* Description	: 设置第一第二通道
* Input Para	: 
* Output Para	: 
* Return Value: 
==================================================================*/
uint8_t ADC_Checking(uint32_t CHANNEL_VOLT ,uint32_t ERR_RANGE )
{
#ifdef ADC_CHECKING
#define ADC_VALUE_COUNT_MAX 10 //6  //must >=3 
	uint8_t count= 0,ValueCount = 0 ; 
	uint32_t ch1 = 0; 
	uint32_t ch2 = 0; 
  	uint32_t ADC_Value[ADC_VALUE_COUNT_MAX]; 	
//	GR_DBG_PRINTF("\nInput ADC......\n\n"); 
	for(;;)
	{		
		ch1 = ADC_Dispose(0x00) ; // GR_DBG_PRINTF("\nCH1 Is %X(%d)\n",ch1,ch1); 
		ch2 = ADC_Dispose(0x01) ; // GR_DBG_PRINTF("\nCH2 Is %X(%d)\n\n",ch2,ch2);

		if( ((ADC_STAND_VOLTAGE - ADC_RSD) <ch1) && (ch1<(ADC_STAND_VOLTAGE+ADC_RSD)))
		{ 
			OSTimeDly(1); 

			ADC_Value[ValueCount++] = ch2 ; //+= ch2 ; 
		 	//	GR_DBG_PRINTF("ADC_Value[%d] is: %d \n\n ",ValueCount-1, ADC_Value[ValueCount-1]);	
			if(ValueCount >=ADC_VALUE_COUNT_MAX)
			{
				ch2 = MedianFilter(ADC_Value, ADC_VALUE_COUNT_MAX );
			 	GR_DBG_PRINTF("ADC_ch2 is: %d \n\n\n ",ch2);	
				//ch2 =	ADC_Value /6  ;  GR_DBG_PRINTF("\nCH2 average Is %X(%d)\n\n",ch2,ch2);
				
				if(((CHANNEL_VOLT - ERR_RANGE) < ch2) && (ch2 < (CHANNEL_VOLT + ERR_RANGE)))
				{
			//		GR_DBG_PRINTF("\n LED Is OK!!!\n\n");
					return TRUE ;  
				}
				else						   // 读取数值不匹配
				{
					System.Error = LED_HRD_ERR; 
			//		GR_DBG_PRINTF("\n LED have some error!!!\n\n\n");
					return FALSE ;	
				}
			}
			else
			{
				continue ; 
			}
		}
		else
		{
			System.Error = SYS_HRD_ERR; 
		//	GR_DBG_PRINTF("\n stdand voltage is Err,Discard the Value!!!\n\n\n");
		}
		if(count++ >= 100) 						// 因为电压不稳读取错误数大于30次
		{
			System.Error = ADC_COUNT_OUT; 
		//	GR_DBG_PRINTF("\nADC Perform  Failed!!\n\n");
			return FALSE ;
		}  
	}
#endif
	return TRUE ;
}


 void SYS_Error()
 {
 	if(System.Error != NON)
 	{
		switch(System.Error)
		{
			case LED_HRD_ERR : SHOW_SCREEN(0xE8, "ERR H13105"); break ; 
		 	case SYS_HRD_ERR : SHOW_SCREEN(0xE8, "ERR H13106"); break ;  
			case ADC_COUNT_OUT :SHOW_SCREEN(0xE8,"ERR H13107"); break ;  
//	 		case SYS_CON_TIME_OUT :SHOW_SCREEN(0xE8,"ERR H13108"); break ; 
			default	:break ; 
		}
		
		System.Error  = NON ; 
	 // 	Light_Init();
	//	while(1);
	}	
 }

void DspRst()
{
	OSTimeDly(10);
	DSP_INIT_PIN = 0 ; 
	OSTimeDly(50);
	DSP_INIT_PIN = 1 ; 
	OSTimeDly(50);

	DSP_INIT_PIN = 0 ; 
	OSTimeDly(10);
	DSP_INIT_PIN = 1 ; 
	OSTimeDly(10);

	DSP_INIT_PIN = 0 ; 
	OSTimeDly(10);
	DSP_INIT_PIN = 1 ; 
 	OSTimeDly(200);
}
/////////////////////////////////////////////

//void ApCombine(const uint8_t* DataA,const uint8_t* DataB, uint8_t* DataC)
//{
//	uint8_t  i=0, j=0; 
//	for(i=0;(*(DataA + i)!= NULL)&&(i<255) ;i++)
//	{
//	   *(DataC+i) = DataA[i]; 
//	}
//	for(j=0;(*(DataA + j)!= NULL)&&(i<255) ;i++,j++)
//	{
//	   *(DataC+i) = DataB[j];
//	}	
//}



