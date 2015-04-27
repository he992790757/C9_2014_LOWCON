
#ifndef CONFIG_H
#define CONFIG_H

#include "DrvGPIO.h"	 
 

#define    	L1	GPC_15//矩阵键盘
#define		L2	GPC_14//矩阵键盘
#define    	L3	GPB_8//矩阵键盘
#define		H1	GPB_14//矩阵键盘
#define    	H2	GPB_13//矩阵键盘
#define    	H3	GPA_11//矩阵键盘


#define		K7	GPA_10//用于独立按键第三个
#define		K6	GPA_9//用于独立按键第四个 
#define		K5	GPB_7// 用于独立按键第二个
#define		K4	GPB_6// 用于独立按键第一个 
#define		K3	GPB_5//用于独立按键第七个
#define		K2	GPB_4//用于独立按键第六个
#define		K1	GPA_8//用于独立按键第五个






///**************键盘定义*************/ 

//#define		K5	GPA_10
//#define		K6	GPC_1	//	GPA_9
//#define		K2	GPC_0	//GPA_8
//#define		K7	GPB_4//用于独立按键第六个
//#define		K3	GPB_5//用于独立按键第七个
//#define		K8	GPB_6// 用于独立按键第一个 
//#define		K4	GPB_7// 用于独立按键第二个
//#define		K9  GPB_12//
//#define		K1  GPA_11//
 


#define    	TOP_W       	GPA_0   //顶850红外
#define    	TOP_IR850      	GPA_2   //顶940红外
#define    	TOP_IR940      	GPA_1   //顶白光
#define    	LEFT_W      	GPA_13    //侧白光
#define 	RIGHT_UV    	GPA_4  	// GPB_2
#define    	LEFT_UV         GPA_3   //底白光  
#define     BOT_W       	GPA_5   //前紫灯	
#define    	BOT_IR     		GPA_6   //底红外
#define    	LEFT_IR850     	GPA_14   //侧红外

#define 	C3_PWR 			GPA_15  //C608

#define 	RIGHT_W 		GPC_7 // 
#define     RIGHT_IR850	    GPA_7 //              //   
 

#define    	TOP_IR940_SMAL     	GPB_4    //侧白光
#define    	   TOP_W_SMAL      	GPA_9    //侧白光
#define    	RIGHT_IR770     	GPB_5    //侧白光

#define    	  LEFT_W_SMAL   		GPB_6  //左侧蓝光
#define    	 LEFT_BLUE    	GPA_8  //侧白光小视窗

#define 	RIGHT_LASER		    GPB_7	//激光
#define     RIGHT_LASER_WHITE	GPA_10

#define 	BOT_UV         GPC_2	// 
#define 	TOP_LEFT_UV          GPA_14	// 


#define 	LEFT_BOT_W_A		GPC_11	//激光
#define     LEFT_BOT_W_B		GPB_9
#define    	LEFT_BOT_W_C     	GPB_10 //侧白光小视窗



//未用上

#define    	LEFT_OnAxis        GPB_10  //同轴光






//#define 	JG 			GPA_15
//#define    	TEST_LED    GPB_9  
/***************4639*****************/
#define    	A1      	GPC_8 
#define    	A0      	GPC_9  
#define    	EN       	GPC_10 
/***************IRCUT*****************/
#define 	CUT_A1 		GPC_1
#define 	CUT_A2 		 GPC_0

#define 	CUT_B1 		 GPE_15 //GPC_3//GPE_5 
#define 	CUT_B2 		 GPE_15//GPC_2//GPB_11

#define		RTD2662_AV 	GPC_3

//#define		CUT_C1 		GPB_3
//#define 	CUT_C2 		GPB_2


#define		DSP_INIT_PIN  GPB_3	  ///////-----------------/////////////////////




//#define    	L1	GPC_15//矩阵键盘
//#define		L2	GPC_14//矩阵键盘
//#define    	L3	GPB_8//矩阵键盘
//#define		H1	GPB_14//矩阵键盘
//#define    	H2	GPB_13//矩阵键盘
//#define    	H3	GPA_11//矩阵键盘
//
// 
//// 
//// 
////#define		K1_LED  GPC_15//按键指示灯1
////#define		K2_LED  GPC_14//按键指示灯2
////#define		K3_LED  GPB_8 //按键指示灯3
////#define		K4_LED  GPB_14//按键指示灯4
////#define		K5_LED  GPB_13//按键指示灯5
////#define		K6_LED  GPB_12//按键指示灯6
////#define		K7_LED  GPA_11//按键指示灯7
////#define		K8_LED  GPA_10//按键指示灯8 	
//
//#define		K7	GPA_10//用于独立按键第三个
//#define		K6	GPA_9//用于独立按键第四个 
//#define		K5	GPB_7// 用于独立按键第二个
//#define		K4	GPB_6// 用于独立按键第一个 
//#define		K3	GPB_5//用于独立按键第七个
//#define		K2	GPB_4//用于独立按键第六个
//#define		K1	GPA_8//用于独立按键第五个
//
//
//
//
//
//
/////**************键盘定义*************/ 
//
////#define		K5	GPA_10
////#define		K6	GPC_1	//	GPA_9
////#define		K2	GPC_0	//GPA_8
////#define		K7	GPB_4//用于独立按键第六个
////#define		K3	GPB_5//用于独立按键第七个
////#define		K8	GPB_6// 用于独立按键第一个 
////#define		K4	GPB_7// 用于独立按键第二个
////#define		K9  GPB_12//
////#define		K1  GPA_11//
// 
//
///************各种LED控制IO**********/
//#define    	TOP_W       	GPA_0   //顶850红外
//#define    	TOP_IR850      	GPA_2   //顶940红外
//#define    	TOP_IR940      	GPA_1   //顶白光
//#define    	LEFT_W      	GPC_7   //侧白光
//#define 	RIGHT_UV    	GPA_4  	// GPB_2
//#define    	LEFT_UV         GPA_3   //底白光  
//#define     BOT_W       	GPA_5   //前紫灯	
//#define    	BOT_IR     		GPA_6   //底红外
//#define    	LEFT_IR850     	GPA_7   //侧红外
//
//#define 	C3_PWR 			GPA_15  //C608
//
//#define 	RIGHT_LASER		    GPB_9	//激光
//#define    	LEFT_BLUE       	GPE_5 //左侧蓝光
//#define    	LEFT_W_SMAL     	GPB_11  //侧白光小视窗
//#define 	TOP_LEFT_UV         GPC_11	// 
//
//#define 	RIGHT_W 		GPA_13 //
//#define     RIGHT_IR850	    GPA_14             //   
//#define    	RIGHT_IR770     GPA_10  //侧白光
//
//#define 	BOT_UV             GPB_10	// 
//#define    	TOP_IR940_SMAL     GPA_9    //侧白光
//#define    	TOP_W_SMAL         GPC_2  //侧白光
//#define     RIGHT_LASER_WHITE	GPB_12
//
////未用上
//
//#define    	LEFT_OnAxis        GPC_11  //同轴光
//
//
//
//
//
//
////#define 	JG 			GPA_15
////#define    	TEST_LED    GPB_9  
///***************4639*****************/
//#define    	A1      	GPC_8 
//#define    	A0      	GPC_9  
//#define    	EN       	GPC_10 
///***************IRCUT*****************/
//#define 	CUT_A1 		GPC_0
//#define 	CUT_A2 		 GPC_1
//
//#define 	CUT_B1 		GPE_11//GPE_5 
//#define 	CUT_B2 		GPE_11//GPB_11
////#define		CUT_C1 		GPB_3
////#define 	CUT_C2 		GPB_2
//
//
//#define		DSP_INIT_PIN  GPB_3	  ///////-----------------/////////////////////
//

#endif





