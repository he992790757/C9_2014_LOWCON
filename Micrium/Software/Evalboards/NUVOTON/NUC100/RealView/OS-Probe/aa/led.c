#define   __LED
#include "Led.h"
#include "config.h"

#include "communication.h"
#include <ucos_ii.h>
#include <stdio.h>
#include "performance.h"


const uint8_t UV_Snr1_ExposureEV_FB[] ={0xFB,G_SENCE_TL_UV,0x12,0x12}	;	//365
const uint8_t UV_Snr1_ExposureEV_FC[] ={0xFC,G_SENCE_TL_UV,0x10,0x10}	; // 0x45,0x45}	;
const uint8_t UV_Snr1_ExposureEV_WB[] ={0xFF,G_SENCE_TL_UV,0x00,0x00}	;

const uint8_t UV_Snr2_ExposureEV_FB[] ={0xFB,G_SENCE_DB_UV2,0xF5,0xF5}	;   //254  35
const uint8_t UV_Snr2_ExposureEV_FC[] ={0xFC,G_SENCE_DB_UV2,0x80,0x90}	;	 //95	45  50 
const uint8_t UV_Snr2_ExposureEV_WB[] ={0xFF,G_SENCE_DB_UV2,0x00,0x00}	;

const uint8_t UV_Snr3_ExposureEV_FB[] ={0xFB,G_SENCE_B_UV,0x12,0x12}	;	//365
const uint8_t UV_Snr3_ExposureEV_FC[] ={0xFC,G_SENCE_B_UV,0x20,0x20}	; // 0x45,0x45}	;
const uint8_t UV_Snr3_ExposureEV_WB[] ={0xFF,G_SENCE_B_UV,0x00,0x00}	;


const uint8_t W_Snr1_ExposureEV_FB[] ={0xFB,G_SENCE_R_ASK,0x10,0x10}	;		// 底部白光
const uint8_t W_Snr1_ExposureEV_FC[] ={0xFC,G_SENCE_R_ASK,0x1B,0x1F}	;
const uint8_t W_Snr1_ExposureEV_WB[] ={0xFF,G_SENCE_R_ASK,0x00,0x00}	;

const uint8_t test[] = {0x7e,0xa2} ; 


void Key_Led_Init()
{
// 	K1_LED = 1 ; 
//	K2_LED = 1 ; 
//	K3_LED = 1 ; 
//	K4_LED = 1 ; 
//	K5_LED = 1 ; 
//	K6_LED = 1 ; 
//	K7_LED = 1 ; 
//	K8_LED = 1 ;     
}



void FilterSwitcher(FILTER FT )
{
	if(System.Dsp.Sensor == SENSOR2)
		{
		 	if(FT == FILTER_IR)
			 	{
					if(	System.FilterSw != FILTER_IR)
					{
						CUT_A1=0;
						CUT_A2=1;	
						OSTimeDly(5);
						CUT_A1=1;
						CUT_A2=1;	
						System.FilterSw =FILTER_IR;
						GR_DBG_PRINTF("FT IN SENSOR1 FILTER_IR \n\n"); 
					}
				}
		 	else if(FT == FILTER_W)
			 	{
					if(	System.FilterSw != FILTER_W)
					{
						CUT_A1=1;
						CUT_A2=0;	
						OSTimeDly(5);
						CUT_A1=1;
						CUT_A2=1;	
						System.FilterSw =FILTER_W	;
						GR_DBG_PRINTF("FT IN SENSOR1 FILTER_W \n\n"); 
					}
				}
		}

	if(System.Dsp.Sensor == SENSOR1)
		{
		 	if(FT == FILTER_IR)
			 	{
					if(	System.FilterSw_Sensor2 != FILTER_IR)
					{
						CUT_B1=0;
						CUT_B2=1;	
						OSTimeDly(5);
						CUT_B1=1;
						CUT_B2=1;	
						System.FilterSw_Sensor2 =FILTER_IR;
						GR_DBG_PRINTF("FT IN SENSOR2 FILTER_IR \n\n"); 
					}
				}
		 	else if(FT == FILTER_W)
			 	{
					if(	System.FilterSw_Sensor2 != FILTER_W)
					{
						CUT_B1=1;
						CUT_B2=0;	
						OSTimeDly(5);
						CUT_B1=1;
						CUT_B2=1;	
						System.FilterSw_Sensor2 =FILTER_W	;
						GR_DBG_PRINTF("FT IN SENSOR2 FILTER_W \n\n"); 
					}
				}
			
		}


}

void  Light_Init()
{
	TOP_W       	= 	1 ; 
	TOP_IR850   	= 	1 ; 
	TOP_IR940   	= 	1 ; 
	LEFT_W       	= 	1 ; 
	RIGHT_W  	= 	1 ; 
	LEFT_IR850   	=	1 ; 
	RIGHT_IR850	= 	1 ;                        
	BOT_W       	= 	1 ;                      
	BOT_IR     	= 	1 ;                            
	RIGHT_UV    	= 	1 ;                       
	LEFT_UV        	= 	1 ;                         
	RIGHT_IR770  = 	1 ;                          
	RIGHT_LASER	 = 	1 ;                        
	C3_PWR 		= 	0 ;                            

    LEFT_OnAxis        =1;  //同轴光

    TOP_LEFT_UV   =1;	//激光加补光

	RTD2662_AV =   1 ; 
    LEFT_BLUE       =1; //左侧蓝光
    LEFT_W_SMAL     =1;  //侧白光小视窗


	BOT_UV         =1;     	// 
   	TOP_IR940_SMAL =1;       //侧白光
    TOP_W_SMAL     =1;       //侧白光
	RIGHT_LASER_WHITE = 1; 
	System.Led.Pwm_IR940.flag = FALSE; 
	System.Led.Pwm_IR850.flag = FALSE; 
	
	System.Led.Statu = ALL_LED_OFF ; 
	pFuc   =Light_Init  ;
}

void Top_W_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
		{
			if(System.Dsp.Sensor == C608) Sensor1(); 	
			DSP_SENDB(0x16,TOP_LABEL, "W"); 	
			Light_Init();
		   	TOP_W = 0;
			FilterSwitcher(FILTER_W ) ;
//			Scen_Send(G_SENCE_WT,0x00);
	        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON);  
//			Scen_Send(0xD7,127) ; 		     
//            Scen_Send(0xDA,127) ; 		     
//            Scen_Send(0xD9,127) ; 			 
//			Scen_Send(0xD8,127) ;			 
//  	        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON);  
// 	        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON);  
//			Scen_Send(G_SENCE_WT,0x01);
//			
		 	Scen_Send(G_SENCE_WT,0x00);
			OSTimeDly(10); 
			System.Led.Statu = TOP_WHITE_ON ; 	
			pFuc   = Top_W_On ;
			ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W );
		}
}

void Left_OnAXis_On(void)
{

	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
		{
			if(System.Dsp.Sensor == C608) Sensor1(); 	
			DSP_SENDB(0x16,LB_NON, "COAX"); 	
			Light_Init();
		   	LEFT_OnAxis = 0;
			FilterSwitcher(FILTER_W ) ;
		 	Scen_Send(G_SENCE_L_Axis ,0x00);
			System.Led.Statu = LEFT_ONAXIS_ON; 	
			pFuc   = Left_OnAXis_On ;
		//	ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W );
		}
}




void Top_IR850_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||System.Dsp.Mode == PCCAM_MODE)
		{
			if(System.Dsp.Sensor == C608) Sensor1(); 
			DSP_SENDB(0x16,TOP_LABEL, "IR2 " ); 			//	200ms
			Light_Init();
			TOP_IR850=0;
			FilterSwitcher(FILTER_IR ) ;
	    
        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
//		Scen_Send(0xD7,0) ; 		    //锐度
//        Scen_Send(0xDA,0) ; 		    //对比度
//        Scen_Send(0xD9,0) ; 			//亮度
//		Scen_Send(0xD8,0) ;				//饱和度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x02);


		Scen_Send(G_SENCE_WT,0x02);
//		Scen_Send(G_SENCE_T_IR850,0x02);					    //	200ms
		OSTimeDly(10); 
		System.Led.Statu = TOP_IR850_ON ; 
		ADC_Checking(ADC_CK_VLT_T_IR850,ADC_RSD_T_IR850);
		pFuc   =  Top_IR850_On;
		}
}
void Top_IR940_On_test(void)
{


	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode ==  PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,TOP_LABEL,"IR3 " ); //	"940" 		

		Light_Init();
		TOP_IR940=0;
		FilterSwitcher(FILTER_IR ) ;
		Scen_Send(G_SENCE_T_IR940,0x02);	
		System.Led.Statu= TOP_IR940_ON ; 
		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);
		OSTimeDly(50);
		Dsp_Send_Data(0xFF,G_SENCE_T_IR940,0x50,0xD1,D_NON);
		pFuc   = Top_IR940_On_test ;
	}
}


void Top_IR940_On(void)
{


	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode ==  PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,TOP_LABEL,"IR3 " ); //	"940" 		

		Light_Init();
		TOP_IR940=0;
		FilterSwitcher(FILTER_IR ) ;

		
        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
		Scen_Send(G_SENCE_WT,0x02);
//		Scen_Send(0xD7,0) ; 		    //锐度
//        Scen_Send(0xDA,0) ; 		    //对比度
//        Scen_Send(0xD9,0) ; 			//亮度
//		Scen_Send(0xD8,0) ;				//饱和度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x02);

//		Scen_Send(G_SENCE_T_IR940,0x02);	
		OSTimeDly(10); 
		System.Led.Statu= TOP_IR940_ON ; 
		pFuc   = Top_IR940_On ;
		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);

	}
}

void Left_W_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode == PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,LEFT_LABEL, "W" ); 

		Light_Init();
		LEFT_W=0;
		FilterSwitcher(FILTER_W ) ;
		Scen_Send(G_SENCE_L_W,0x00);
		OSTimeDly(10); 
		System.Led.Statu = LEFT_W_ON ; 
		pFuc   = Left_W_On ;
	//	ADC_Checking(ADC_CK_VLT_L_W,ADC_RSD_L_W);
	}
}

void Right_W_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,LEFT_LABEL, "W" );
		Light_Init();
		RIGHT_W=0;
		FilterSwitcher(FILTER_W ) ;
		Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON);
     	Scen_Send(G_SENCE_WT,0x00);
//		if(System.Dsp.Sensor == SENSOR1)
//		{	Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON);  
//			Scen_Send(0xD7,0) ; 		     
//	        Scen_Send(0xDA,0) ; 		    
//	        Scen_Send(0xD9,0) ; 			 
//			Scen_Send(0xD8,0) ;			 
//	        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON);  
//	        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON);  
//			Scen_Send(G_SENCE_WT,0x00);
//		}
//		else  if(System.Dsp.Sensor == SENSOR2)
//		{	Dsp_Send_Data(0xFF,G_SENCE_WT,120,127,D_NON);  
//			Scen_Send(0xD7,127) ; 		     
//	        Scen_Send(0xDA,127) ; 		    
//	        Scen_Send(0xD9,127) ; 			 
//			Scen_Send(0xD8,127) ;			 
//	        Dsp_Send_Data(0xFB,G_SENCE_WT,8,8,D_NON);  
//	        Dsp_Send_Data(0xFC,G_SENCE_WT,26,26,D_NON);  
//			Scen_Send(G_SENCE_WT,0x01);		
//		}
	//	Scen_Send(G_SENCE_L_W,0x00);
		System.Led.Statu = RIGHT_W_ON ; 
		pFuc   = Right_W_On ;
	//	ADC_Checking(ADC_CK_VLT_R_W,ADC_RSD_R_W);
	}
}
void Double_Side_W_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		//if(System.Dsp.Sensor == C608) Sensor1(); 
		//DSP_SENDB(0x16,LB_NON, "W" );
		//Light_Init();
		LEFT_W =0;
		RIGHT_W=0;
		FilterSwitcher(FILTER_W ) ;
		Scen_Send(G_SENCE_DB_W,0x00);
		pFuc   = Double_Side_W_On ;
		//System.Led.Statu = DB_W_ON ; 

	//	ADC_Checking(ADC_CK_VLT_R_W,ADC_RSD_R_W);
	}
}
void Left_W1_On(void)
{
	if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode == PCCAM_MODE)
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,TOP_R_LABEL, "W" ); 

		Light_Init();
		LEFT_W_SMAL =0;
		FilterSwitcher(FILTER_W ) ;

      Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
//		Scen_Send(0xD7,0) ; 		    //锐度
//        Scen_Send(0xDA,0) ; 		    //对比度
//        Scen_Send(0xD9,0) ; 			//亮度
//		Scen_Send(0xD8,0) ;				//饱和度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x01);

		Scen_Send(G_SENCE_L_W,0x00);
		OSTimeDly(10); 
		System.Led.Statu = LEFT_W1_ON ; 
		pFuc   = Left_W1_On ;
	//	ADC_Checking(ADC_CK_VLT_L_W,ADC_RSD_L_W);
	}
}


void RIGHT_OnAxis_On(void)
{
	//if((System.Dsp.Mode == CHECK_MODE)||System.Dsp.Mode == PCCAM_MODE)
	//{
	//	if(System.Dsp.Sensor == C608) Sensor1(); 
	//	DSP_SENDB(0x16,LEFT_LABEL, "W" ); 

	//	Light_Init();
	//	LEFT_OnAxis =0;
	//	FilterSwitcher(FILTER_W ) ;
	//	Scen_Send(G_SENCE_L_W,0x00);
	//	System.Led.Statu = LEFT_W1_ON ; 
	////	ADC_Checking(ADC_CK_VLT_L_W,ADC_RSD_L_W);
	//}
}

void Left_IR850_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,LEFT_LABEL, "IR2 " );
		Light_Init();
		LEFT_IR850 = 0;
	//	FilterSwitcher(FILTER_IR ) ;
		FilterSwitcher(FILTER_W ) ;
		Scen_Send(G_SENCE_L_IR,0x02);
		OSTimeDly(10); 
		System.Led.Statu = LEFT_IR850_ON ;  
		pFuc   =Left_IR850_On  ;
	//	ADC_Checking(ADC_CK_VLT_L_IR,ADC_RSD_L_IR);
	}
}

void Right_IR850_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,LEFT_LABEL, "IR2" ); 

		Light_Init();
		RIGHT_IR850 = 0;
		FilterSwitcher(FILTER_W ) ;

//		Scen_Send(G_SENCE_WT,0x02);								
//		if(System.Dsp.Sensor == SENSOR1)
//		{
//	        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
//			Scen_Send(0xD7,0) ; 		    //锐度
//	        Scen_Send(0xDA,0) ; 		    //对比度
//	        Scen_Send(0xD9,0) ; 			//亮度
//			Scen_Send(0xD8,0) ;				//饱和度
//	        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
//	        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
//			Scen_Send(G_SENCE_WT,0x02);		
//		}
//		else if(System.Dsp.Sensor == SENSOR2)
//		{
//	        Dsp_Send_Data(0xFF,G_SENCE_WT,218,127,D_NON); //白平衡
//			Scen_Send(0xD7,127) ; 		    //锐度
//	        Scen_Send(0xDA,127) ; 		    //对比度
//	        Scen_Send(0xD9,127) ; 			//亮度
//			Scen_Send(0xD8,127) ;				//饱和度
//	        Dsp_Send_Data(0xFB,G_SENCE_WT,42,42,D_NON); //曝光度
//	        Dsp_Send_Data(0xFC,G_SENCE_WT,42,42,D_NON); //曝光时间
//			Scen_Send(G_SENCE_WT,0x03);	
//		}
		Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
		Scen_Send(G_SENCE_WT,0x02);
		OSTimeDly(100); 
		System.Led.Statu = RIGHT_IR850_ON ;  
		pFuc   = Right_IR850_On ;
	//	ADC_Checking(ADC_CK_VLT_R_IR,ADC_RSD_R_IR);
	}
}

void Double_Side_IR_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		//if(System.Dsp.Sensor == C608) Sensor1(); 

		//DSP_SENDB(0x16,LB_NON, "IR" ); 

		//Light_Init();
		LEFT_IR850  = 0 ;
		RIGHT_IR850 = 0 ;
		
		FilterSwitcher(FILTER_IR ) ;
		Scen_Send(G_SENCE_DB_IR,0x02);
		pFuc   =  Double_Side_IR_On;
		//System.Led.Statu = DB_IR850_ON ;  
	//	ADC_Checking(ADC_CK_VLT_R_IR,ADC_RSD_R_IR);
	}    
}

void Bot_W_On(void)													   //3
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,BTM_LABEL, "W" ); 

		Light_Init();
		BOT_W=0;	
		FilterSwitcher(FILTER_W ) ;

		Scen_Send(G_SENCE_WT,0x00);
        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
		Scen_Send(0xD7,0) ; 		    //锐度
        Scen_Send(0xDA,0) ; 		    //对比度
        Scen_Send(0xD9,0) ; 			//亮度
		Scen_Send(0xD8,0) ;				//饱和度
        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
		Scen_Send(G_SENCE_WT,0x00);
		OSTimeDly(10); 
		System.Led.Statu = BOT_W_ON ;
		pFuc   = Bot_W_On; 
		ADC_Checking(ADC_CK_VLT_B_W,ADC_RSD_B_W);
	}
}

void Bot_IR_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,BTM_LABEL, "IR2 " ); 
		Light_Init();
		BOT_IR=0;	
		FilterSwitcher(FILTER_W ) ;

		Scen_Send(G_SENCE_WT,0x02)  ; 
        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
		Scen_Send(0xD7,0) ; 		    //锐度
        Scen_Send(0xDA,0) ; 		    //对比度
        Scen_Send(0xD9,0) ; 			//亮度
		Scen_Send(0xD8,0) ;				//饱和度
        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
		Scen_Send(G_SENCE_WT,0x02)  ; 
		OSTimeDly(10); 
		System.Led.Statu = BOT_IR_ON ; 
		ADC_Checking(ADC_CK_VLT_B_IR,ADC_RSD_B_IR);
		pFuc   =  Bot_IR_On ; 
	}
}
void Left_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,LB_NON, "UV365" ); 

		Light_Init();
		LEFT_UV=0;
		FilterSwitcher(FILTER_W ) ;
		Scen_Send(G_SENCE_DB_UV,0x00);
		System.Led.Statu = LEFT_UV_ON ; 
		pFuc   = Left_UV_On ;
	// 	ADC_Checking(ADC_CK_VLT_R_UV,ADC_RSD_R_UV);
	}	
}

void Right_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,LB_NON, "UV365" ); 

		Light_Init();
		RIGHT_UV=0;
		FilterSwitcher(FILTER_W ) ;
		Scen_Send(G_SENCE_DB_UV,0x00);
		System.Led.Statu = RIGHT_UV_ON ; 
		pFuc   =Right_UV_On  ;
	// 	ADC_Checking(ADC_CK_VLT_R_UV,ADC_RSD_R_UV);
	}
}

void Double_WT_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,LB_NON, "UV365" ); 
		Scen_Send(G_SENCE_DB_UV,0x00);	

		Light_Init();
	   	TOP_W = 0;
		OSTimeDly(100);

		Light_Init();
		LEFT_UV=0;
	//	OSTimeDly(100);
		RIGHT_UV=0;
		FilterSwitcher(FILTER_W ) ;	
		System.Led.Statu = DB_WT_UV_ON ; 
		pFuc   = Double_WT_UV_On ;
		ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
	}
}

void Double_UV_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		if(System.Led.Statu != DB_UV_ON  )
		{
			DSP_SENDB(0x16,LB_NON, "UV365" ); 
			pFuc   = Double_UV_On ;
			Light_Init();
			LEFT_UV=0;		
			RIGHT_UV=0;
 	   	    FilterSwitcher(FILTER_W ) ;

			Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
			Scen_Send(G_SENCE_WT,0x00);

		        
//	//			Scen_Send(0xD7,218) ; 		    //锐度
//	//	        Scen_Send(0xDA,127) ; 		    //对比度
//	//	        Scen_Send(0xD9,207) ; 			//亮度
//	//			Scen_Send(0xD8,127) ;				//饱和度
//		        Dsp_Send_Data(0xFB,G_SENCE_DB_UV,90,90,D_NON); //曝光度
//		        Dsp_Send_Data(0xFC,G_SENCE_DB_UV,15,15,D_NON); //曝光时间
//				Scen_Send(G_SENCE_DB_UV,0x01);
		//	Scen_Send(G_SENCE_DB_UV,0x00);	
				
			System.Led.Statu = DB_UV_ON ; 
			pFuc   =Double_UV_On  ;
			ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);  
		}
	}
}

void TopLeft_Uv_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,TOP_LABEL, "UV" ); 
		
		Light_Init();
		TOP_LEFT_UV = 0;	

		if(System.Dsp.Sensor != SENSOR2)
		{	
	    	Dsp_Send_Data(0x71,0x00,0x22,20,150);
			FilterSwitcher(FILTER_W ) ;
	    	OSTimeDly(10); 
	    	System.Dsp.Sensor = SENSOR2 ; 
			System.Dsp.CheckMode.Zoom = X0 ;
			System.Dsp.ViewMode.Zoom  = X0 ; 
		}

		FilterSwitcher(FILTER_W ) ;	
//		if(System.Key.OldValue != 7)
//		{
//			Check_View_Zoom(X0);
//			OSTimeDly(20);
//		}
		OSTimeDly(10);

//	    Scen_Send(G_SENCE_WT,0x00);
        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
//		Scen_Send(0xD7,127) ; 		    //锐度
//        Scen_Send(0xDA,127) ; 		    //对比度
//        Scen_Send(0xD9,239) ; 		 	 //亮度
//		Scen_Send(0xD8,97) ;		     //饱和度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,16,28,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,16,28,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x01);

	 	Scen_Send(G_SENCE_WT,0x00);	
		System.Led.Statu = TOP_LEFT_UV_ON; 
		pFuc   = TopLeft_Uv_On ;
	//	ADC_Checking(ADC_CK_VLT_R_LA,ADC_RSD_R_LA);
	}
}
void Left_Blue_On(void)
{

	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
		{
			if(System.Dsp.Sensor == C608) Sensor1(); 	
			DSP_SENDB(0x16,LB_NON, "BLU "); 	
			Light_Init();
			LEFT_BLUE = 0;	 
		//	Sensor2();
			if(System.Dsp.Sensor != SENSOR2)
			{
				System.Dsp.CheckMode.Zoom = X0 ;
				System.Dsp.ViewMode.Zoom  = X0 ; 
		    	System.Dsp.Sensor = SENSOR2 ; 								
		    	Dsp_Send_Data(0x71,0x00,0x22,20,150);
				FilterSwitcher(FILTER_IR) ;		//滤片切换器要到sensor后面切 
		    	OSTimeDly(10); 
			}																																				
//			Check_View_Zoom(X0)	;   
			FilterSwitcher(FILTER_IR) ;		//滤片切换器要到sensor后面切 
//		    OSTimeDly(30); 

			Dsp_Send_Data(0xFF,G_SENCE_L_BLUE,0,0,D_NON); //白平衡
			Scen_Send(0xD7,127) ; 		    //锐度
			Scen_Send(0xDA,127) ; 		    //对比度
			Scen_Send(0xD9,127) ; 			//亮度
			Scen_Send(0xD8,127) ;				//饱和度
			Dsp_Send_Data(0xFB,G_SENCE_L_BLUE,25,25,D_NON); //曝光度
			Dsp_Send_Data(0xFC,G_SENCE_L_BLUE,70,70,D_NON); //曝光时间
			Scen_Send(G_SENCE_L_BLUE,0x00);
							 
		 //	Scen_Send(G_SENCE_L_BLUE,0x02);
			System.Led.Statu = LEFT_BLUE_ON; 	
			pFuc   = Left_Blue_On ;
			//ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W );
		}
}

void Bot_Uv_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,BTM_LABEL, "UV" ); 
		
		Light_Init();
		BOT_UV = 0;	
//		RIGHT_LASER_WHITE = 0 ; 					//----------2
		FilterSwitcher(FILTER_W ) ;

       Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
//		Scen_Send(0xD7,0) ; 		    //锐度
//        Scen_Send(0xDA,0) ; 		    //对比度
//        Scen_Send(0xD9,0) ; 			//亮度
//		Scen_Send(0xD8,0) ;				//饱和度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,0,0,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,0,0,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x01);

		Scen_Send(G_SENCE_WT,0x00);	
		System.Led.Statu = BOT_UV_ON; 
		pFuc   = Bot_Uv_On ; 
	//	ADC_Checking(ADC_CK_VLT_R_LA,ADC_RSD_R_LA);
	}
}

void Top_Ir940_Small_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,TOP_LABEL, "IR3 " ); 
		
		Light_Init();
		TOP_IR940_SMAL = 0;	
		FilterSwitcher(FILTER_W ) ;

		
       Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
	   Scen_Send(G_SENCE_WT,0x02);
//		Scen_Send(0xD7,127) ; 		    //锐度
//        Scen_Send(0xDA,127) ; 		    //对比度
//        Scen_Send(0xD9,127) ; 			//亮度
//		Scen_Send(0xD8,127) ;				//饱和度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,18,30,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,18,30,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x03);


//		Scen_Send(G_SENCE_T_IR940_SMAL,0x02);	
		OSTimeDly(10); 
		System.Led.Statu = T_IR940_SMAL_ON; 
	//	ADC_Checking(ADC_CK_VLT_R_LA,ADC_RSD_R_LA);
	pFuc   =Top_Ir940_Small_On  ;
	}
}

void Top_W_Small_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,TOP_LABEL, "W" ); 
		Light_Init();
		TOP_W_SMAL = 0;	
		TOP_W  = 0 ;
//		RIGHT_LASER_WHITE = 0 ; 
		FilterSwitcher(FILTER_W) ;

		
       Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡
	   Scen_Send(G_SENCE_WT,0x00);
//		Scen_Send(0xD7,244) ; 		    //锐度
//        Scen_Send(0xDA,127) ; 		    //对比度
//		Scen_Send(0xD8,128) ;				//饱和度
//		Scen_Send(0xD9,128) ; 			//亮度
//        Dsp_Send_Data(0xFB,G_SENCE_WT,3,3,D_NON); //曝光度
//        Dsp_Send_Data(0xFC,G_SENCE_WT,3,3,D_NON); //曝光时间
//		Scen_Send(G_SENCE_WT,0x01);


		

	//	Scen_Send(G_SENCE_T_W_SMAL,0x00);	
		OSTimeDly(10); 
		System.Led.Statu = T_W_SMAL_ON; 
		pFuc   =Top_W_Small_On  ;
	//	ADC_Checking(ADC_CK_VLT_R_LA,ADC_RSD_R_LA);
	}
}



void SetAGC()
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{

	}	
}


void ExProsure()
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

	   	Sensor2(); 

		OSTimeDly(300) ;
		Top_W_On() ; 
		OSTimeDly(300) ; 

  ////////////////////////////////////////////////////////////////////////// 111111111111111
		DSP_SENDB(0x16,TOP_LABEL, "UV" ); 
		
		Light_Init();
		TOP_LEFT_UV = 0;	
		FilterSwitcher(FILTER_W ) ;
		OSTimeDly(100);
  //////////////////////////////////////////////////////////////////////////
 		DSP_SEND(4, &UV_Snr1_ExposureEV_FB[0]);
		OSTimeDly(50); 
		DSP_SEND(4, &UV_Snr1_ExposureEV_FC[0]);
		OSTimeDly(50); 
		DSP_SEND(4, &UV_Snr1_ExposureEV_WB[0]);
		OSTimeDly(50);
		Scen_Send(G_SENCE_TL_UV,0x01 ) ; 	   

		OSTimeDly(300);
	//	RIGHT_UV=0;
		Scen_Send(0xE6, G_SENCE_TL_UV); 
		OSTimeDly(500);

//		System.Led.Statu = DB_UV_EXPOSURE1_ON; 
//		ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
//////////////////////////////////////////////////////////////////////////////// 22222222222
		Top_W_On() ; 
		OSTimeDly(300) ; 

		DSP_SENDB(0x16,LB_NON, "IRF"); 	
		Light_Init();
	   	LEFT_BLUE = 0;
		FilterSwitcher(FILTER_IR) ;
  //////////////////////////////////////////////////////////////////////////
		OSTimeDly(200) ; 
		DSP_SEND(4, &UV_Snr2_ExposureEV_FB[0]);
		OSTimeDly(50); 
		DSP_SEND(4, &UV_Snr2_ExposureEV_FC[0]);
		OSTimeDly(50); 
		DSP_SEND(4, &UV_Snr2_ExposureEV_WB[0]);
		OSTimeDly(50);
		Scen_Send(G_SENCE_DB_UV2,0x03 ) ; 
		OSTimeDly(300);			
		Scen_Send(0xE6, G_SENCE_DB_UV2); 
		OSTimeDly(300);

////////////////////////////////////////////////////////////////////////////////33333333333333333333
		Top_W_On() ; 
		OSTimeDly(300) ; 
																				// AAAAAAAAAAAAAAAAAAAAAAAAAAAAA2
		DSP_SENDB(0x16,BTM_LABEL, "W" ); 
		FilterSwitcher(FILTER_W ) ;


		Light_Init();
		RIGHT_LASER_WHITE = 0 ; 
	    OSTimeDly(200);
  //////////////////////////////////////////////////////////////////////////
		DSP_SEND(4, &W_Snr1_ExposureEV_FB[0]);
		OSTimeDly(50); 
		DSP_SEND(4, &W_Snr1_ExposureEV_FC[0]);
		OSTimeDly(50); 
		DSP_SEND(4, &W_Snr1_ExposureEV_WB[0]);
		OSTimeDly(50);
 		Scen_Send(G_SENCE_R_ASK,0x01 ) ; 
		OSTimeDly(300);
			
		Scen_Send(0xE6, G_SENCE_R_ASK); 
		OSTimeDly(300);

	}	
}


void Double_UV_Exposure1_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
		{
			if(System.Dsp.Sensor == C608) Sensor1(); 

			DSP_SENDB(0x16,LB_NON, "UV365" ); 
			FilterSwitcher(FILTER_W ) ;

			OSTimeDly(10);
	 
			Light_Init();
			LEFT_UV=0;		
		//	RIGHT_UV=0;
			if(System.Dsp.Sensor == SENSOR1)	
				{
			    		Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
			    		OSTimeDly(50); 
			    		Scen_Send(0xE5, G_SENCE_DB_UV); 
			    		OSTimeDly(50);
				}
			else
				{
			    		//Scen_Send(0x01,0x00 ) ; 
			    		//OSTimeDly(50);	

					Scen_Send(G_SENCE_DB_UV,0x01 ) ; 
			    		OSTimeDly(50); 
			    		Scen_Send(0xE5, G_SENCE_DB_UV); 
			    		OSTimeDly(50);
				}
			pFuc   = Double_UV_Exposure1_On ;
			System.Led.Statu = DB_UV_EXPOSURE1_ON; 
			ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);

		}
}

void Double_UV_Exposure2_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
		{
			if(System.Dsp.Sensor == C608) Sensor1(); 

			DSP_SENDB(0x16,LB_NON, "UV254" ); 
			FilterSwitcher(FILTER_W ) ;
			
				
			Light_Init();
		//	LEFT_UV=0;
			RIGHT_UV=0;		

			if(System.Dsp.Sensor == SENSOR1)	
				{
					Scen_Send(G_SENCE_DB_UV2,0x01 ) ; 
					OSTimeDly(50); 
					Scen_Send(0xE5, G_SENCE_DB_UV2); 	
					OSTimeDly(50);
				}
			else
				{
			    		Scen_Send(0x01,0x00 ) ; 
			    		OSTimeDly(50);			
				}
			System.Led.Statu = DB_UV_EXPOSURE2_ON ; 
			ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
			pFuc   = Double_UV_Exposure2_On ;
		}
}



void Right_IR770_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 

		DSP_SENDB(0x16,TOP_LABEL, "IR1 " ); 
		Light_Init();
		RIGHT_IR770 = 0;
		FilterSwitcher(FILTER_W) ;

		Scen_Send(G_SENCE_T_IR770,0x02);
        Dsp_Send_Data(0xFF,G_SENCE_T_IR770,52,89,D_NON); //白平衡
		Scen_Send(0xD7,127) ; 		    //锐度
        Scen_Send(0xDA,127) ; 		    //对比度
        Scen_Send(0xD9,127) ; 			//亮度
		Scen_Send(0xD8,127) ;				//饱和度
        Dsp_Send_Data(0xFB,G_SENCE_T_IR770,2,5,D_NON); //曝光度
        Dsp_Send_Data(0xFC,G_SENCE_T_IR770,2,3,D_NON); //曝光时间
		Scen_Send(G_SENCE_T_IR770,0x03);


//		Scen_Send(G_SENCE_T_IR770,0x02);	
		OSTimeDly(10); 
		System.Led.Statu = RIGHT_IR770_ON; 
		pFuc   = Right_IR770_On ;
	//	ADC_Checking(ADC_CK_VLT_R_770,ADC_RSD_R_770);
	}
}

void Right_Laser_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Dsp.Sensor == C608) Sensor1(); 
		DSP_SENDB(0x16,LB_NON, "ASK" ); 

		Light_Init();
		RIGHT_LASER = 0;	
 		RIGHT_LASER_WHITE = 0 ; 
		FilterSwitcher(FILTER_W ) ;
		Scen_Send(G_SENCE_B_IR,0x00);	
		System.Led.Statu = RIGHT_LASER_ON; 
		pFuc   = Right_Laser_On ;
	//	ADC_Checking(ADC_CK_VLT_R_LA,ADC_RSD_R_LA);
	}
}


void C608_On(void)
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
		{
			Light_Init();
			A1=0;  
			A0=1; 
			EN=1;
		  	C3_PWR = 1;	
			RTD2662_AV = 0 ; 											                                                                                    
			OSTimeDly(10);
			
			DSP_SENDB(0x16,0x08, " C608");	 			
			OSTimeDly(10);	
			
			Select_Send(0x39);			      
			OSTimeDly(200);
			  
			Scen_Send(0xC1,0xC8);
			pFuc   = C608_On ;
			System.Led.Statu = C608_PWR_ON; 
			System.Dsp.Sensor = C608 ;
		}
//	System.Dsp.Scale_Status = X0;    //存储方式
}

void Right_ASK_Blink()
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
		{
		    		// 创建闪烁进程	
			if(System.Dsp.Sensor == C608) Sensor1(); 
			DSP_SENDB(0x16,LB_NON, "ASK" );	
					
			Light_Init();	
			FilterSwitcher(FILTER_W ) ;				
			RIGHT_LASER_WHITE = 0 ; 	

	        Dsp_Send_Data(0xFF,G_SENCE_WT,0,0,D_NON); //白平衡									
			Scen_Send(G_SENCE_WT,0x00);

//			Scen_Send(0xD7,127) ; 		    //锐度
//	        Scen_Send(0xDA,127) ; 		    //对比度
//	        Scen_Send(0xD9,127) ; 			//亮度
//			Scen_Send(0xD8,127) ;			//饱和度
//	        Dsp_Send_Data(0xFB,G_SENCE_WT,20,20,D_NON); //曝光度
//	        Dsp_Send_Data(0xFC,G_SENCE_WT,24,24,D_NON); //曝光时间
//			Scen_Send(G_SENCE_WT,0x01);	
			OSTimeDly(5);	
			Check_View_Zoom(X1)	;
			OSTimeDly(20);	
		 //	Scen_Send(G_SENCE_R_ASK,0x00);

			System.Led.Statu = RIGHT_ASK_BLINK; 
			pFuc   = Right_ASK_Blink ;
		}
}

void Right_ASK_PlatForm(uint8_t NUM)
{	
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Led.Statu == RIGHT_ASK_BLINK)
		{	 
		    //Light_Init();	
			System.Led.Statu= RIGHT_ASK_BLINK ;
    		if(NUM)
    		{		
                    RIGHT_LASER = 0 ; 
    		}
    		else
    		{
                    RIGHT_LASER = 1 ;	                  
    		}
    		
    //		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);   
		}
	}
}



void Top_IR850_940_Blink()
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
		{
		    		// 创建闪烁进程	
			if(System.Dsp.Sensor == C608) Sensor1(); 
			DSP_SENDB(0x16,LB_NON,"BLINK" ); //	"940" 		
			FilterSwitcher(FILTER_IR ) ;
			Scen_Send(G_SENCE_T_IR940,0x02);
			pFuc   = Top_IR850_940_Blink ;
			System.Led.Statu= TOP_IR850_940_BLINK ;
		}
}

void Top_IR850_940_Blink_PlatForm(uint8_t NUM)
{	
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Led.Statu == TOP_IR850_940_BLINK)
		{	 
		    Light_Init();	
			System.Led.Statu= TOP_IR850_940_BLINK ;
    		if(NUM)
    		{
        		
				if(System.Dsp.Sensor == SENSOR2)
				{
					TOP_IR940 = 0 ; 
        		    System.Led.Pwm_IR940.flag  = TRUE ; 
				}
				else
				{
                    TOP_IR940 = 0 ; 
				}
    		}
    		else
    		{
                if(System.Dsp.Sensor == SENSOR2)
				{
					TOP_IR850 = 0 ; 
				    System.Led.Pwm_IR850.flag  = TRUE ;
                }
				else
				{
                    TOP_IR850 = 0 ; 
				}
        		                  
    		}
    		
    //		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);   
		}
	}
}



void Side_W_IR_Blink()
{
	if(System.Dsp.Mode == CHECK_MODE||(System.Dsp.Mode == PCCAM_MODE))
		{
		    		// 创建闪烁进程	
			if(System.Dsp.Sensor == C608) Sensor1(); 
			DSP_SENDB(0x16,LB_NON,"BK1 " ); //	"940" 		
			//FilterSwitcher(FILTER_IR ) ;
			//Scen_Send(G_SENCE_T_IR940,0x02);

			System.Led.Statu= SIDE_W_IR_BLINK ;
			pFuc   = Side_W_IR_Blink ;
		}
}

void Side_W_IR_Blink_PlatForm(uint8_t NUM)
{	
	if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == PCCAM_MODE))
	{
		if(System.Led.Statu == SIDE_W_IR_BLINK)
		{	 
		    Light_Init();	
			System.Led.Statu= SIDE_W_IR_BLINK ;
    		if(NUM)
    		{
        		
//				if(System.Dsp.Sensor == SENSOR2)
//				{
//					//TOP_IR940 = 0 ; 
//        		    //System.Led.Pwm_IR940.flag  = TRUE ; 
//
//					
//				}
//				else
//				{
//                    //TOP_IR940 = 0 ; 
//				}

				Double_Side_W_On(); 
    		}
    		else
    		{
    //            if(System.Dsp.Sensor == SENSOR2)
				//{
				//	TOP_IR850 = 0 ; 
				//    System.Led.Pwm_IR850.flag  = TRUE ;
    //            }
				//else
				//{
    //                TOP_IR850 = 0 ; 
				//}
				Double_Side_IR_On(); 
        		                  
    		}
    		
    //		ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);   
		}
	}
}


void CheckLight()
{
	
	Light_Init();TOP_IR940=0;ADC_Checking(ADC_CK_VLT_T_IR940,ADC_RSD_T_IR940);	 
	Light_Init();BOT_IR=0;	 ADC_Checking(ADC_CK_VLT_B_IR,ADC_RSD_B_IR);
	Light_Init();LEFT_UV=0;	 RIGHT_UV=0;	 ADC_Checking(ADC_CK_VLT_DB_UV,ADC_RSD_DB_UV);
	Light_Init();TOP_W = 0;	 ADC_Checking(ADC_CK_VLT_T_W,ADC_RSD_T_W );
//	Light_Init();
}


