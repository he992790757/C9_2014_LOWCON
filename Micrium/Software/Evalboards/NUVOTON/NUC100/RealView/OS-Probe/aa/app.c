
/***************************************************************************************
****************************************************************************************
* FILE		: app.c
* Description	: 1 USB  
				  2 时钟 
				  3 定时 //休眠/ 节电/ 等等
				  4 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1		XXX	2013/08/23	Initial Version
   
****************************************************************************************
****************************************************************************************/

#define  __APP
#include <ucos_ii.h>
#include "app_cfg.h" 
#include "cpu.h"
#include "global.h"
#include "performance.h"
#include <stdio.h>
#include "Driver\DrvUART.h"
#include "Driver\DrvGPIO.h"
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "Driver\DrvTIMER.h"
//#include <stdlib.h>

#include "Driver\DrvUSB.h"
#include "HID_API.h"
#include "communication.h" 

#include "config.h"
#include "KeyScan.h"
#include "keydispose.h"
#include "HIDSysIO.h"
#include "V6MDebug.h"
#include "led.h"
#include "DrvUSB.h"
//#include "machineconfig.h"; 

#include"DS1307.h"
#include "time.h"
#include "adjustIR.h"

// uint32_t volatile 	SysData[18];					   //系统信息存储

#define DATA_FLASH_BASE          ((     uint32_t)0x0001F000)
#define GR_ID          			 0x12345678UL

OS_STK_DATA stk_data;
INT32U stk_size;
uint8_t err ;
uint8_t tmps ;
void Delay(uint32_t delayCnt)
{
    while (delayCnt--)
    {
        __NOP();
        __NOP();
    }
}				
//uint32_t ssss[92];

void InitIO()
{
	DrvGPIO_SetPortBits (E_GPA, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPB, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPC, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPD, 0xFFFF);
	DrvGPIO_SetPortBits (E_GPE, 0xFFFF);
}

void InitValue()
{
		
}

void init_sensor(void)
{

}
void InitStart()
{
//	uint8_t i =0 ;
///////////// 数据初始化/////////////////////////
	SignOutCount = 0 ; 
 	System.Key.Value = 0 ; 
	System.Led.Statu = TOP_WHITE_ON ; 	
	System.Dsp.Mode = CHECK_MODE; 

	
	System.Dsp.CheckMode.Zoom = X0 ; 
	System.Dsp.ViewMode.Zoom  = X0 ; 
	System.Dsp.TF_Mode.t = 0 ; 
	System.Dsp.PccamMode.ConnectIn = 0 ; 
	System.Dsp.Sensor =SENSOR1 ; 
//	System.Dsp.SD = OUT ; 
	System.Usb.NewUsbStatu 	= USB_OUT; 
	System.Usb.OldUsbStatu 	= USB_OUT;  
	System.Usb.UsbStatuLabel= 0 ;
	System.Dsp.Sensor = C608;
	System.SleepEnable = 1 ; 
	System.Process_TakePht  = 1 ; 

	//if(	System.FilterSw != FILTER_W)
	{
		CUT_A1=1;
		CUT_A2=0;	
		OSTimeDly(10);
		CUT_A1=1;
		CUT_A2=1;	
		System.FilterSw =FILTER_W	;
	}
//	if(	System.FilterSw_Sensor2 != FILTER_W)
	{
		CUT_B1=1;
		CUT_B2=0;	
		OSTimeDly(10);
		CUT_B1=1;
		CUT_B2=1;	
		System.FilterSw_Sensor2 =FILTER_W	;
	}
							
//	for(i=0;i<46;i++)
//	{	OSTimeDly(20);
//	}
//	for(i=0;i<20;i++)

	{	OSTimeDly(350);
	}
//	K2_LED=0;

	 Scen_Send(0x60,0x00);				   //拍照水印
	 OSTimeDly(20);
	 Scen_Send(0xC1,0x60);				   //duibidu
	 OSTimeDly(50);
	 Select_Send(0x27);		
	
//	 Scen_Send(0x99,0x04);					//像素降低至03等级，共 有4等级
     SetAGC() ;
	 CheckMode(); 
}


/* ----------------- APPLICATION GLOBALS ------------------ */
//static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
//static OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
//static OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];

#define STACK1SIZE   128// 128
#define STACK2SIZE   120 // 最小
#define STACK3SIZE   64  // 最小

#ifdef THREAD_TEST

//OS_STK SYS_Task_Stack[STACKSIZE]; 
//#define SYS_Task_Prio				19

OS_STK Task1_Stack[STACK1SIZE]; 
#define Task1_Prio     18

OS_STK Task2_Stack[STACK2SIZE];
#define  Task2_Prio       20

OS_STK Task3_Stack[STACK3SIZE];
#define  Task3_Prio       19

#endif



/*
*********************************************************************************************************
*                                            LOCAL FUCTION
*********************************************************************************************************
*/
int32_t BSP_INIT_UART0(void)
{
	STR_UART_T param;

	/* SYSCLK =>12Mhz*/
	DrvGPIO_InitFunction(E_FUNC_UART0_RX_TX);

	/* Select UART Clock Source From 12MHz */
	DrvSYS_SelectIPClockSource(E_SYS_UART_CLKSRC,0); 
	
    param.u32BaudRate        = 115200;
    param.u8cDataBits        = DRVUART_DATABITS_8;
    param.u8cStopBits        = DRVUART_STOPBITS_1;
    param.u8cParity          = DRVUART_PARITY_NONE;
    param.u8cRxTriggerLevel  = DRVUART_FIFO_62BYTES;
    param.u8TimeOut        	 = 250;
    if(DrvUART_Open(UART_PORT0,&param) == 0)
		return TRUE;
	else
		return FALSE;
}

#ifdef UART_OS_TEST
OS_STK UART_Stack[STACKSIZE]; 
#define UARTTask_Prio     50

void UARTTask(void *Id)
{	
#if OS_CRITICAL_METHOD == 3                         /* Allocate storage for CPU status register           */
	OS_CPU_SR  cpu_sr;
#endif
	(void)Id;//remove warning

	OS_UART_HANDLE();
	
	while(1) OSTimeDly(3000);
}	// main
#endif

void SysTick_Handler(void)			// 非常重要   系统滴答
{
	OSIntEnter();
	OSTimeTick();
	OSIntExit();
}

void Timer0_Callback (void)//200ms
{
	if(System.Time.Click ++ >= 5) // 1s
	{	
		System.Time.Click = 0 ; 
//		if(System.SleepEnable)
	    {
			if((System.Dsp.Mode == CHECK_MODE)||(System.Dsp.Mode == SLEEP_MODE))
			{
				if((System.Dsp.Sensor != C608)&&(System.Key.NoKeyTime <= 3000))
				{
						System.Key.NoKeyTime ++  ;
				} 	
			}
		}
	}	
}


void WDT_Init()
{
	UNLOCKREG(); 
	DrvWDT_Open(E_WDT_LEVEL6);	

	 //看门狗定时器复位使能
	 DrvWDT_Ioctl(E_WDT_IOC_ENABLE_RESET_FUNC, 0); 

	//使能看门狗定时器 WTE
	 DrvWDT_Ioctl(E_WDT_IOC_START_TIMER, 0); 

	 LOCKREG(); 
	//	
}
void WDT_Feed()
{
	UNLOCKREG();
	DrvWDT_Ioctl(E_WDT_IOC_RESET_TIMER, 0);  
	LOCKREG(); 	
}

void TIMER_Configuration()				   
{

    DrvTIMER_Init();														

	DrvSYS_SelectIPClockSource(E_SYS_TMR0_CLKSRC,0);					

	DrvTIMER_Open(E_TMR0,5,E_PERIODIC_MODE);								
	
 	DrvTIMER_SetTimerEvent(E_TMR0,1,(TIMER_CALLBACK) Timer0_Callback,0);

	DrvTIMER_EnableInt(E_TMR0);											

	DrvTIMER_Start(E_TMR0);												
}
//void TIMER1_Configuration()				   
//{	
//    DrvTIMER_Init();
//															
//	DrvSYS_SelectIPClockSource(E_SYS_TMR1_CLKSRC,0);					
//
//	DrvTIMER_Open(E_TMR1,50000,E_PERIODIC_MODE);								
//	
// 	DrvTIMER_SetTimerEvent(E_TMR1,1,(TIMER_CALLBACK) Timer1_Callback,0);
//
//	DrvTIMER_EnableInt(E_TMR1);											
//
//	DrvTIMER_Start(E_TMR1);												
//}


#ifdef THREAD_TEST


void Task1(void *Id)
{
	uint8_t  n = 0 ; 
	(void) Id;		
	SysTick_Config(120000);	 
//	CPU_IntEn();  
	n = KeyScan();			 	
 	DspRst(); 
				

//	CheckLight();	
//	OSTimeDly(250);
															    
	ConfigBCK(); 

 	InitStart();

	GR_DBG_PRINTF("Variable System length %d ",sizeof(System) ); 
	
	TIMER_Configuration(); 
	TIMER1_Configuration();
   	System.Usb.OldUsbStatu = USB_STATUS ;	   
	switch(n)
	{
		case 1 :  TESTA(); 	  break ; 
	//	case 2 :  TESTB(); 	  break ;
	//	case 3 :  TESTC(); 	  break ;
	//	case 4 :  TESTD(); 	  break ;
		case 3 :  TESTE(); 	  break ;
		default :break ; 
	}
		
	for(;;)   
	{	
		KeyDispose();	
		OSTimeDly(5); 			
	}
}
void Task3(void *Id)
{
	(void) Id;	
	while(1)
	{
       if(System.Led.Statu == TOP_IR850_940_BLINK)
	   {  
	         if(tmps<1) tmps++ ; else tmps = 0 ; 
	   	      Top_IR850_940_Blink_PlatForm(tmps) ; 		
			  OSTimeDly(100);	
	   }	
	   else if(System.Led.Statu == SIDE_W_IR_BLINK)
	   {  
	         if(tmps<1) tmps++ ; else tmps = 0 ; 
	   	      Side_W_IR_Blink_PlatForm(tmps) ; 	
			  OSTimeDly(100);		
	   }
	   else if(System.Led.Statu == RIGHT_ASK_BLINK)
	   {
	         if(tmps<1) tmps++ ; else tmps = 0 ; 
	   	      Right_ASK_PlatForm(tmps) ; 	
			  OSTimeDly(20);	   		
	   }
	   OSTimeDly(10);	
	}
}
void Task2(void *Id)  
{
	int32_t i32Ret = E_SUCCESS;
	E_DRVUSB_STATE eUsbState;

	(void) Id;

 	i32Ret = DrvUSB_Open((void *)DrvUSB_DispatchEvent);
//	i32Ret = DrvUSB_Open(0);			  //随便。。
    if (i32Ret != E_SUCCESS)
		return ;
    while (1)
    {
        /* Disable USB-related interrupts. */
        _DRVUSB_ENABLE_MISC_INT(0);

        /* Enable float-detection interrupt. */
        _DRVUSB_ENABLE_FLDET_INT();

        // Wait for USB connected.
        while (1)
        {
            // Order here is significant.
            // Give a chance to handle remaining events before exiting this loop.
            eUsbState = DrvUSB_GetUsbState();

            //DrvUSB_DispatchEvent();

            if (eUsbState >= eDRVUSB_ATTACHED &&
                    eUsbState != eDRVUSB_SUSPENDED)
            {
                break;
            } 


        }

        /* Start HID and install the callback functions to handle in/out report */
        HID_Init((void *)HID_GetInReport, (void *)HID_SetOutReport);

        // Enable USB-related interrupts.
        _DRVUSB_ENABLE_MISC_INT(INTEN_WAKEUP | INTEN_WAKEUPEN | INTEN_FLDET | INTEN_USB | INTEN_BUS);

        // Poll and handle USB events.
        while (1)
         {
             eUsbState = DrvUSB_GetUsbState();
 //            DrvUSB_DispatchEvent();
             if (eUsbState == eDRVUSB_DETACHED)
             {
                 break;
            }
// 
//			err = OSTaskStkChk(OS_PRIO_SELF, &stk_data);
//			if (err == OS_NO_ERR) {
//			stk_size = stk_data.OSFree + stk_data.OSUsed;
//				printf(" task 2 stk_size is %d,stk_data.OSFree is %d ,stk_data.OSUsed is %d  \n\n",stk_size,stk_data.OSFree,stk_data.OSUsed );
//			}		 
	     }
        // Disable USB-related interrupts.
        _DRVUSB_ENABLE_MISC_INT(0);	
	//	OSTimeDly(100);
    }		      
}

//void Task3(void *Id)   
//{   
////	uint8_t i=0 ; 
//   (void) Id;
//	for (;;)
//	{
//		OSTimeDly(100); 
//
//	}
//}
#endif

/*=================================================================================
* Function	: main
* Description	: 
* Input Para	: 
* Output Para	: 
* Return Value: 
=================================================================================*/

int  main (void)
{
//	uint32_t Temp=0;
//================================配置系统时钟==============//
	UNLOCKREG();  
	SYSCLK->PWRCON.OSC22M_EN = 1;//default is enabled 
	SYSCLK->PWRCON.XTL12M_EN = 1;
	SYSCLK->CLKSEL0.HCLK_S = 0;//using 12M as HCLK src

  //  DrvSYS_Delay(5000);    	
    Delay(5000)	 ;
    DrvSYS_Open(48000000);   
//	DSP_INIT_PIN = 0 ; 	
//  LCD_POWER = 1 ;  

//	
   
//===================================================================================//	
	BSP_INIT_UART0();                												 //init the uart0
	GR_DBG_PRINTF("System Is run\n\n"); 
	DrvUART_EnableInt(UART_PORT0,DRVUART_RDAINT | DRVUART_TOUTINT,UART_INT_HANDLE);	 //
//===================================================================================//
 //	Vir_Init() ; //初始化环境变量	
	
////===============================读取dataflash存储的系统信息=========================//	
  //读取flash中数据	  第一次运行读写写入默认值
////======================================开始任务=====================================//


	OSInit();
	CPU_IntDis() ;

 //	SysTick_Config(120000);	 
 //	InitValue();
                                     
#ifdef THREAD_TEST
    OSTaskCreateExt(Task2,  (void *)0,  (OS_STK *)&Task2_Stack[STACK2SIZE-1],  Task2_Prio,Task2_Prio,Task2_Stack,STACK2SIZE ,NULL,OS_TASK_OPT_STK_CHK);
	OSTaskCreateExt(Task1,  (void *)0,  (OS_STK *)&Task1_Stack[STACK1SIZE-1],   Task1_Prio,Task1_Prio,Task1_Stack,STACK1SIZE,NULL,OS_TASK_OPT_STK_CHK);
	OSTaskCreateExt(Task3,  (void *)0,  (OS_STK *)&Task3_Stack[STACK3SIZE-1],   Task3_Prio,Task3_Prio,Task3_Stack,STACK3SIZE,NULL,OS_TASK_OPT_STK_CHK);
//	OSTaskCreate(SYS_Task,  (void *)0,  (OS_STK *)&SYS_Task_Stack[STACKSIZE-1],SYS_Task_Prio); 
#endif
	OSStart();   
//===================================================================================//
}

void OSTaskReturnHook(OS_TCB *ptcb)
{
	
}

#if OS_APP_HOOKS_EN > 0

#endif
#if OS_APP_HOOKS_EN > 0 && OS_VERSION >= 251
void  App_TaskIdleHook (void)
{
}
#endif



#if OS_APP_HOOKS_EN > 0 && OS_VERSION >= 204

void  App_TCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif




#if OS_APP_HOOKS_EN > 0
void  App_TaskCreateHook (OS_TCB *ptcb)
{
	(void)ptcb;
}
#endif

void  App_TaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
}

#if OS_APP_HOOKS_EN > 0 && OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{
}
#endif
#if OS_APP_HOOKS_EN > 0
void  App_TaskStatHook (void)
{
}
#endif
#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{
}
#endif



