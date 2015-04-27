
#define __KEYDISPOSE1

#include "Keydispose1.h"
#include "Keydispose.h"
#include "ucos_ii.h"
#include "stdint.h"
#include "global.h"
#include "KeyScan.h"
#include "performance.h"
#include "Led.h"
#include "config.h"
#include "communication.h" 
#include "V6MDebug.h"
#include "Adjustir.h"


#ifdef C9_2011C_SAM

void  SensorChange()
{
	//sensor1�л���sensor2
	
	//1��¼֮ǰ�İ���ֵ
	if(System.Dsp.Sensor == SENSOR1)
	{  System.Dsp.Sensor = SENSOR2 ;
       switch(System.Key.OldValue)
       {
            case 2: Top_W_Small_On(); System.Dsp.Sensor = SENSOR1	;break ; 
				   		
			case 3: Right_IR770_On();System.Dsp.Sensor = SENSOR1	; break ;
			case 4: TopLeft_Uv_On() ;System.Dsp.Sensor = SENSOR1	; break ;
			case 5: System.Dsp.Sensor = SENSOR1	; break; 
			case 6: System.Dsp.Sensor = SENSOR1	; break; 
		//	case 7: Top_W_On();System.Key.OldValue = 2 ;System.Dsp.Sensor = SENSOR1	;break ;
		//    case 8: Top_W_On();System.Key.OldValue = 2 ;System.Dsp.Sensor = SENSOR1	;break ;
	//		case 9: System.Dsp.Sensor = SENSOR1	;return ; 
			default:System.Dsp.Sensor = SENSOR1	;break ; 	
	   }
	}
	else if(System.Dsp.Sensor == SENSOR2)
	{  System.Dsp.Sensor = SENSOR1 ;
       switch(System.Key.OldValue)
       {    
            case 2: Top_W_On();   System.Dsp.Sensor = SENSOR2 ;break ; 	   		
			case 3: Top_IR850_On() ; System.Dsp.Sensor = SENSOR2 ; break ;
			case 4: Double_UV_On();System.Dsp.Sensor = SENSOR2 ;   break ;
			case 5: System.Dsp.Sensor = SENSOR2 ; break; 
			case 6: System.Dsp.Sensor = SENSOR2 ;break; 
			case 7: if(System.Dsp.CheckMode.Zoom != X1 )Check_View_Zoom(X1);else if(System.Dsp.CheckMode.Zoom != X0)Check_View_Zoom(X0);
					System.Dsp.Sensor = SENSOR2 ;break ;
		    case 8: Top_W_On();System.Key.OldValue = 2 ;System.Dsp.Sensor = SENSOR2 ;break ;
	//		case 9: System.Dsp.Sensor = SENSOR2 ;return ; 
			default:System.Dsp.Sensor = SENSOR2	;break ; 		
	   }  
	}
}


void KeyInfoDispose()
{
	
	
		//������⴦��
	System.Key.Value = KeyScan() ;
	System.Key.Keylong = &Keylong ; 
	if(!System.Key.Value)
		{
			// �������߲��� 
			if(System.Key.NoKeyTime == 120)
			{
				if(System.Dsp.Mode == CHECK_MODE)
				{
					if(System.Led.Statu == RIGHT_ASK_BLINK )
					{
						CheckMode(); 
					}	
				}		
			}
 			else if(System.Key.NoKeyTime == 180)
			{
				if(System.Dsp.Mode == CHECK_MODE)
				{
					if(System.Led.Statu == DB_UV_ON )
					{
						CheckMode(); 
					}	
				}	
			}
			else if(System.Key.NoKeyTime == 300)
			{
				if(System.Dsp.Mode == CHECK_MODE)
					{		
						System.Dsp.Mode = SLEEP_MODE ; 
					//	SHOW_SCREEN(0xE8,  "Power Saving Mode");   
						Light_Init() ; 
						SHOW_SCREEN(0xE8,  "Sleep"); 
						OSTimeDly(200);						  		
					}
			}
//			else if ((System.Key.NoKeyTime == 300)&&(System.Dsp.Mode == SLEEP_MODE))
//				{
//				 	System.Dsp.Mode = SLEEP_MODE ;
//				  	SHOW_SCREEN(0xE8,  "Power Saving Mode"); 
//					//	SHOW_SCREENW(0xE8, WcharToChar(L"�ڵ�ģʽ") );
//					OSTimeDly(200);			   //������
//				}
		}
	else
		{
		//	GR_DBG_PRINTF("keylong is  %d OK it is  %d\n\n",*System.Key.Keylong,Keylong);
			// �����Ѳ���
			System.Key.NoKeyTime = 0 ;
			if(System.Dsp.Mode == SLEEP_MODE)
				{	
					CheckMode(); 
					OSTimeDly(200) ; 
				}
//			//����������
			switch(System.Key.Value)
				{

				case 1 ://ȫ��--�ֲ� �����������608
					{
						if(*System.Key.Keylong)
						{
							if((System.Dsp.Mode ==CHECK_MODE)
								||(System.Dsp.Mode ==PCCAM_MODE))
							{						
								if(System.Led.Statu == C608_PWR_ON)
								{
									CheckMode(); 
								}
								else
								{
									C608_On() ;
								}
	
							}
						}												  
						else
						{
							if(System.Led.Statu == C608_PWR_ON)
							{
								CheckMode(); 
							} else
						    {
								if((System.Dsp.Mode ==CHECK_MODE)
								   ||(System.Dsp.Mode ==PCCAM_MODE))
								{
									if(System.Dsp.Sensor == SENSOR1)
									{
									   if((System.Led.Statu == TOP_WHITE_ON )&&(System.Key.OldValue !=2))
									   {
									   	 Top_W_Small_On(); 	
									   }
										Sensor2(); 		   
										switch(System.Key.OldValue)
								       {
								            case 2: Top_W_Small_On(); ;break ; 		// ��sensor2�ĵط��Ѿ�����														   		
											case 3: Right_IR770_On();; break ;
											case 4: TopLeft_Uv_On() ;; break ;
											case 5: break; 
											case 6: break; 
									// 	 	case 7: Top_W_Small_On(); System.Key.OldValue = 2 ;System.Dsp.Sensor = SENSOR1	;break ;
									//	    case 8: Top_W_Small_On(); System.Key.OldValue = 2 ;System.Dsp.Sensor = SENSOR1	;break ;
									//		case 9: System.Dsp.Sensor = SENSOR1	;return ; 
									 		default:break ; 	
									   }							
									}
									else  if(System.Dsp.Sensor == SENSOR2)
									{
										//if((System.Key.OldValue == 7)&&((System.Led.Statu == TOP_LEFT_UV_ON)||(System.Led.Statu == BOT_UV_ON )))
										if(System.Dsp.CheckMode.Zoom == X0)
										{
											Check_View_Zoom(X2);
//											return ; 
										}
										else
										{
											if((System.Led.Statu == T_W_SMAL_ON )&&(System.Key.OldValue !=2))
											{
												Top_W_On();
											} 
											FilterSwitcher(FILTER_W ) ;	   // ֮ǰ����л�����Ƭ�л���
											Sensor1() ;
											
											switch(System.Key.OldValue)
									       {    
									            case 2: Top_W_On();System.Key.OldValue = 2 ;return ; 	   		
												case 3: Top_IR850_On() ;  break ;
												case 4: Double_UV_On(); break ;
												case 5: break; 
												case 6: break; 
												case 7: Top_W_On();System.Key.OldValue = 2 ;break ;
											    case 8: Top_W_On();System.Key.OldValue = 2 ;break ;
										//		case 9: System.Dsp.Sensor = SENSOR2 ;return ; 
												default:break ; 		
										   }   
										}
										
									}

								}
							}
						}
					}break ; 
					case 2 ://ȫ��������׹⣬����׹⡢
					        //�ֲ���ͬ��⣬��׹⣬����⣨�෽��
						{
							if(System.Dsp.Sensor == SENSOR1 )
							{
								if((System.Dsp.Mode ==CHECK_MODE)
    								||(System.Dsp.Mode ==PCCAM_MODE))
    								{	
                                       if(System.Led.Statu == TOP_WHITE_ON) 
                                       {
                                          Right_W_On() ;
									   }else
									   {
                                          Top_W_On(); 
									   }
    								}								
							}
							else if(System.Dsp.Sensor == SENSOR2)
							{
								if((System.Dsp.Mode ==CHECK_MODE)
    								||(System.Dsp.Mode ==PCCAM_MODE))
    								{
									  // Check_View_Zoom(X0);	
									 if((System.Dsp.CheckMode.Zoom == X1 )
										|| (System.Dsp.CheckMode.Zoom == X3 ))
									  {
									  	 Check_View_Zoom(X0)	;
									  }		
                                       if(System.Led.Statu == T_W_SMAL_ON) 
                                       {
									   	 // Right_W_On();
                                          Left_W1_On() ;
									   }
									   else
									   {
                                          Top_W_Small_On();
									   }
    								}								
							}
							else
							{
                                 CheckMode(); 
							}							
						}break ; 
//
					case 3 ://����850������940�����ڶ��Σ�������850��940����ѭ��
			
						{										
							if(*System.Key.Keylong)// ����У������
								{
									if(System.Dsp.Mode == CHECK_MODE)
										{
											ExProsure() ;
										}
								}
							else
								{
            						if(System.Dsp.Sensor == SENSOR1 )
            						{
    									if((System.Dsp.Mode ==CHECK_MODE)
    										||(System.Dsp.Mode ==PCCAM_MODE))
    										{
    											if(System.Led.Statu == TOP_IR850_ON)
    												{
    													Top_IR940_On() ; 
    												}
    											else
    												{
    													Top_IR850_On() ; 
    												}
    										}
            						}
									else if(System.Dsp.Sensor == SENSOR2 )
									{
     									if((System.Dsp.Mode ==CHECK_MODE)
    										||(System.Dsp.Mode ==PCCAM_MODE))
    										{
											//	Check_View_Zoom(X0);
												if((System.Dsp.CheckMode.Zoom == X1 )
												|| (System.Dsp.CheckMode.Zoom == X3 ))
												  {
												  	 Check_View_Zoom(X0)	;
												  }	
												  	
    											if(System.Led.Statu == RIGHT_IR770_ON)
    												{
    													Top_Ir940_Small_On();
    												}
												else
    												{
    													Right_IR770_On(); 
    												}
    										}                                       
									}
								}
						}break ; 

					case 4 ://ȫ�������Ϲ�365�������Ϲ�254
					        //�ֲ���UV-LED�����⣨�Ŵ�3X)
						{  						
							if(*System.Key.Keylong)// ����У������
								{
									
								}
							else
								{
    								if(System.Dsp.Sensor == SENSOR1 )
    							    {
    									if((System.Dsp.Mode ==CHECK_MODE)
    										||(System.Dsp.Mode ==PCCAM_MODE))
    										{
												
                                                Double_UV_On(); 
    										}
    								}
        							if(System.Dsp.Sensor == SENSOR2 )
        							{
    									if((System.Dsp.Mode ==CHECK_MODE)
    										||(System.Dsp.Mode ==PCCAM_MODE))
    										{
											if((System.Dsp.CheckMode.Zoom == X1 )
												|| (System.Dsp.CheckMode.Zoom == X3 ))
											  {
											  	 Check_View_Zoom(X0)	;
											  }		
                                                TopLeft_Uv_On();
    									    }
        							}
								}					
						}break ; 
 
					
					case 5 ://͸��׹⡢͸���⣬ѭ��
						{
								if((System.Dsp.Mode ==CHECK_MODE)
									||(System.Dsp.Mode ==PCCAM_MODE))
								{
								//	Check_View_Zoom(X0);
									if((System.Dsp.CheckMode.Zoom == X1 )
										|| (System.Dsp.CheckMode.Zoom == X3 ))
									  {
									  	 Check_View_Zoom(X0)	;
									  }		
									if(System.Led.Statu == RIGHT_W_ON)
									{
									   Right_IR850_On();
									}
									else
									{
										Right_W_On();
									}
								}	
								else if(System.Dsp.Mode ==VIEW_MODE)
								{
                                    PhotoPrevious(); 
								}
										
						}break ; 

					case 6 ://����⡢�����ѭ��	
						{	
							if(*System.Key.Keylong)// ����У������
							{
								if(System.Dsp.Mode ==TF_MODE)
								{
								   CheckMode();
								}
								else
								{
									TfMode();
								} 
							}
							else								
							{
								//	Check_View_Zoom(X0);	
						        if((System.Dsp.Mode ==CHECK_MODE)
									||(System.Dsp.Mode ==PCCAM_MODE))
								{
									if((System.Dsp.CheckMode.Zoom == X1 )
										|| (System.Dsp.CheckMode.Zoom == X3 ))
									  {
									  	 Check_View_Zoom(X0);
									  }	
									if(System.Led.Statu == BOT_W_ON)
									{
										Bot_IR_On(); 
									}
									else
									{
										Bot_W_On() ; 
									}
								}
								else if(System.Dsp.Mode ==VIEW_MODE)
								{
                                    PhotoNext() ;  
								}	
						   }
						}break ;
					case 7 :    //�ֲ��ӳ����׹⡢���⣨����Ƭ�л���
						{
							if(*System.Key.Keylong)// ����У������
							{
							}
							else								
							{
								if((System.Dsp.Mode ==CHECK_MODE)
									||(System.Dsp.Mode ==PCCAM_MODE))
								{									  									  								 
                                      if(System.Led.Statu == TOP_LEFT_UV_ON)
									  {
                                         Bot_Uv_On( );
										 Check_View_Zoom(X3)	;
									  }								  
									  else
									  {
	
                                         TopLeft_Uv_On(); 
										 //if(System.Dsp.CheckMode.Zoom == X1 )
										  {
										  	 Check_View_Zoom(X3)	;
										  }	
									  }		  	
								}
							}					
												
						}break ; 
					
					case 8 ://a)	M��Ԥ�����ط�ģʽ�л�
						{
							if(*System.Key.Keylong)// ����У������
							{
								if(System.Dsp.Mode ==VIEW_MODE)
								{
									 CheckMode();
								}
								else  if(System.Dsp.Mode ==CHECK_MODE)
								{
									 ViewMode(); 
									 
								} 	
							}
							else								
							{
						        if((System.Dsp.Mode ==CHECK_MODE)
									||(System.Dsp.Mode ==PCCAM_MODE))
						        {									
    									  if(System.Led.Statu == LEFT_BLUE_ON)
    									  {
											 Right_ASK_Blink();	 	
    									  }										  
    									  else
    									  {  										  	  									  
											  Left_Blue_On();    
											  Check_View_Zoom(X0)	;                                          
    									  }     
								}	
							}
						}break ; 
					case 9 :/*Ԥ��ģʽ�£��޲�����
                            �ط�ģʽ�£�ǰ��ҳ
                            ��Ƭ�Ŵ�ģʽ�£���΢��
                            */
                            {	
								if(*System.Key.Keylong) 
								{
									 if(System.Dsp.Mode ==CHECK_MODE)
									 {
										PccamMode(); 
									 }
									 else   if(System.Dsp.Mode ==PCCAM_MODE)
									 {
									 	CheckMode(); 
									 }
									 else   if(System.Dsp.Mode ==VIEW_MODE)
									 {
                                        PhotoDelAll() ;
									 }
								}
								else
								{
    						        if((System.Dsp.Mode ==CHECK_MODE)
    									||(System.Dsp.Mode ==PCCAM_MODE))
    								{
										PhotographOne() ; 
    								} 
									else if(System.Dsp.Mode ==VIEW_MODE)
									{
                                        PhotoDelOne() ; 
									}
								}
						    }break ; 							
					default : break ; 
				}
				if(!(*System.Key.Keylong))
				{
				    if((System.Key.Value !=1 )&&(System.Key.Value !=9 ))
						if((System.Dsp.Mode ==CHECK_MODE)||(System.Dsp.Mode ==PCCAM_MODE))System.Key.OldValue = System.Key.Value ; 
				}
		}
}



#endif 
