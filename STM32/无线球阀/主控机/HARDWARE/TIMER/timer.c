#include "timer.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
//////////////////////////////////////////////////////////////////////////////////	 
#define Open 			0x01			//������
#define Shutdown 	0x00			//�ر���
//////////////////////////////////////////////////////////////////////////////////   	 
extern u16 time;
extern void uart1_send_cmd(u8 action);
extern u8 Send_cmd,Get_cmd,Success;


//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_Cap_Init(u16 arr,u16 psc)
{		 
	
	RCC->APB1ENR|=1<<2;   			//TIM4 ʱ��ʹ�� 
	RCC->APB2ENR|=1<<3;    			//ʹ��PORTBʱ�� 

	GPIOB->CRH&=0XFFFFFF00;			//PB8,9 ����  
	GPIOB->CRH|=0X00000088;			//����ģʽ    
	GPIOB->ODR&=~(1<<9);				//PB8,9 ����
	GPIOB->ODR&=~(1<<8);				//PB8,9����
	  

	
	TIM4->ARR=arr;  			//�趨�������Զ���װֵ ���10ms���  
	TIM4->PSC=psc;  			//Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.

	TIM4->CCMR2|=1<<8  | 1;				//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
 	TIM4->CCMR2|=3<<12 | 3<<4;  	//IC4F=0011 ���������˲��� 8����ʱ��ʱ�������˲�
 	TIM4->CCMR2|=0<<10 | 0<<2;  	//IC4PS=00 	���������Ƶ,����Ƶ 

	TIM4->CCER|=0<<13; 						//CC4P=0	�����ز���
	TIM4->CCER|=1<<12 | 1<<8; 		//CC4E=1 	�������������ֵ������Ĵ�����
	TIM4->DIER|=1<<4  | 1<<3;   	//����CC4IE�����ж�				
	TIM4->DIER|=1<<0;   					//��������ж�				
	TIM4->CR1|=0x01;    					//ʹ�ܶ�ʱ��4
  MY_NVIC_Init(3,3,TIM4_IRQn,2);//��ռ1�������ȼ�3����2	
}


//��ʱ��5�жϷ������	 
void TIM4_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM4->SR;
	if(tsr&0X01)//���
	{
			time++;
		if(Send_cmd)															//�շ�������
		{
			if(time >= 2000)
			{
				if(Send_cmd)
				{
					if(Get_cmd)
					{
						OLED_ShowString(0,2,"                ",16);
						OLED_ShowString(0,2,"SEND--OK    ",16);
						Send_cmd = 0;
					}
					else
					{
						OLED_ShowString(0,2," Connect--Error ",16);
						OLED_ShowString(0,4,"Please try again",16);
						delay_ms(1000);
					}
				}
			
				time = 0;
			}
		}
		if(Get_cmd)
		{
			if(time >= 4000)
			{
				if(!Success)													//���ն˳ɹ�ִ������
				{
					OLED_ShowString(0,4,"Task--Fail",16);
					OLED_ShowString(0,6,"Please try again",16);
				}
				else
				{
					OLED_ShowString(0,4,"Task--OK",16);
				}
				time = 0;
			}
		}
	}	
	
	if(tsr&0X10)//�����ز���
	{
		uart1_send_cmd(Shutdown);
		OLED_Clear();
		OLED_ShowString(0,2,"Start Connect...",16);
		OLED_ShowString(0,0,"Task: Shutdown",16);
		Send_cmd = 1;						//��������ѷ���
		Success = 0;						//�����ϴ�ִ��ʧ�ܵı�־λ
		time = 0;								//��ʱ����ʼ�ۼӼ�ʱ
	}		
	if(tsr&0X8)//�����ز���
	{
		uart1_send_cmd(Open);
		OLED_Clear();
		OLED_ShowString(0,2,"Start Connect...",16);
		OLED_ShowString(0,0,"Task: Open",16);
		Send_cmd = 1;						//��������ѷ���
		Success = 0;						//�����ϴ�ִ��ʧ�ܵı�־λ
		time = 0;								//��ʱ����ʼ�ۼӼ�ʱ
	}		
	TIM4->SR=0;//����жϱ�־λ 
}














