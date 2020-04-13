#include "timer.h"
#include "led.h"
#include "delay.h"

#define OpenSuccess 0x0c
#define CloseSuccess 0x0e
#define ErrOpen 0x0d
#define ErrClose 0x0f
extern u8  getNum,start,cmdOpen,cmdClose;
extern u16 time;

void usart1_send(u8 action);
//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_Cap_Init(u16 arr,u16 psc)
{		 
	
	RCC->APB1ENR|=1<<2;   	//TIM4 ʱ��ʹ�� 
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ�� 

	GPIOB->CRH&=0XFFFFFF0F;	//PB9 ����  
	GPIOB->CRH|=0X00000080;	//����ģʽ    
	GPIOB->ODR&=~(1<<9);		//PB9 ����
	  
// 	TIM4->ARR=10000;  		//�趨�������Զ���װֵ ���10ms���  
//	TIM4->PSC=71;  			//Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	 
	
	TIM4->ARR=arr;  		//�趨�������Զ���װֵ ���10ms���  
	TIM4->PSC=psc;  			//Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.

	TIM4->CCMR2|=1<<8;		//CC4S=01 	ѡ������� IC4ӳ�䵽TI4��
 	TIM4->CCMR2|=3<<12;  	//IC4F=0011 ���������˲��� 8����ʱ��ʱ�������˲�
 	TIM4->CCMR2|=0<<10;  	//IC4PS=00 	���������Ƶ,����Ƶ 

	TIM4->CCER|=0<<13; 		//CC4P=0	�����ز���
	TIM4->CCER|=1<<12; 		//CC4E=1 	�������������ֵ������Ĵ�����
	TIM4->DIER|=1<<4;   	//����CC4IE�����ж�				
	TIM4->DIER|=1<<0;   	//��������ж�				
	TIM4->CR1|=0x01;    	//ʹ�ܶ�ʱ��4
  MY_NVIC_Init(3,3,TIM4_IRQn,2);//��ռ1�������ȼ�3����2	
}

//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽸ߵ�ƽ;1,�Ѿ����񵽸ߵ�ƽ��.
//[5:0]:����ߵ�ƽ������Ĵ���
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
//��ʱ��5�жϷ������	 
void TIM4_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM4->SR;
	if(tsr&0X01)//���
	{
		time++;
		if(time == 3000)
		{
			if(cmdOpen)
			{
				if(getNum > 2)
				{
					usart1_send(0x0c);
				}
				else
				{
					usart1_send(0x00);
				}
				cmdOpen = 0;
				start =0;
				getNum = 0;
			}
			if(cmdClose)
			{
				if(getNum < 2)
				{
					usart1_send(CloseSuccess);
				}
				else
				{
					usart1_send(0);
				}
				cmdClose = 0;
				start = 0;
				getNum = 0;
			}
			time = 0;
		}
	}		
	if(tsr&0X10)//�����ز���
	{
		if(start)
			getNum++;
	}		
	TIM4->SR=0;//����жϱ�־λ 
}















