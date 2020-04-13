#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"  	
#include "oled.h"
#include "myiic.h"
#include "LORA.h"
#include "exti.h"
#include "timer.h"
//ALIENTEK��ӢSTM32F103������ ʵ��4
//���� ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
void uart1_handle(void);
void uart1_send_cmd(u8 action);
u8 LORA_Check_Flag;
u16 time;
u8 Get_cmd,Success,Errors,Send_cmd;
u8 date[6]={0xaa,0xcc,0x17,0x0A,0x0d,0x0a};
int main(void)
{								   
	Stm32_Clock_Init(9);	//ϵͳʱ������
	uart_init(72,9600); 	//���ڳ�ʼ��Ϊ9600
	delay_init(72);	   	 	//��ʱ��ʼ�� 
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	IIC_Init();                //��ʼ��IIC��IO��
	OLED_Init();
	OLED_Clear();
	EXTIX_Init();
	LORA_Init();
//	TIM3_Int_Init(100,719);
	TIM4_Cap_Init(100,719);  //1ms���һ��
	LORA_Check();

 	while(1)
	{
	}		 
}

void uart1_handle(void)
{
	if(USART_RX_STA&0x8000)
		{	
			OLED_ShowNum(0,4,USART_RX_BUF[0],4,16);
				if((USART_RX_BUF[0]==0x0C) | (USART_RX_BUF[0]==0x0E))
				{
					Success = 1;					//�����ɹ�
					
				}
			
			else
			{
				if(USART_RX_BUF[0]==0x0A)
				{
					LED0 = 0;
					delay_ms(400);
					LED0 = 1;
					delay_ms(400);
					LED0 = 0;
					delay_ms(400);
					LED0 = 1;
					Get_cmd = 1;
				}
			}
			USART_RX_STA=0;
		}
}
void uart1_send_cmd(u8 action)
{
	u8 t=0;
	if(action)
	{
		date[3] = 0x0A;
	}
	else
	{
		date[3] = 0x0B;
	}
	for(t=0;t<6;t++)
			{
				USART1->DR=(date[t] & (uint16_t)0x01FF);
				while((USART1->SR&0X40)==0);						//�ȴ��������
			}
}
