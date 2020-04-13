#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 	 
#include "timer.h"

//****************************�Զ������******************************************
u8  cmdOpen  = 0;								//�����򷧱�־λ
u8  cmdClose = 0;								//�ر��򷧱�־λ
u8  openErr  = 0;								//�������쳣��־λ
u8  closeErr = 0;								//�ر����쳣��־λ
u16 getNum   = 0;								//��ȡ���������������
u8 start;
u16 time;
#define Open  0x0A
#define Close 0x0B
//****************************�Զ������******************************************//

void usart1_send(u8 action);
u16 t; 
char date[6]={0xaA,0xBB,0x17,0x0A,0x0d,0x0a}; 

int main(void)
{								  	  
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	TIM4_Cap_Init(100,719);  //1ms���һ��
 	while(1)
	{

	}		 
}
void handle_USART_1(void)
{
	if(USART_RX_STA&0x8000)
		{		
//			if(USART_RX_BUF[0]==0x0A)
//			{
//				LED0=~LED0;
//				usart1_send();
//			}
//			USART_RX_STA=0;
			switch(USART_RX_BUF[0])
			{
				case 0x0A:	cmdOpen =1;	start=1;	usart1_send(Open);break;
				case 0x0B:	cmdClose=1;	start=1;	usart1_send(Close);break;
			}
			USART_RX_STA=0;
		}
		
}

void usart1_send(u8 action)
{
			date[3] = action;
			for(t=0;t<6;t++)
			{
				USART1->DR=(date[t] & (uint16_t)0x01FF);
				while((USART1->SR&0X40)==0);						//�ȴ��������
				
			}
			time = 0;

}
