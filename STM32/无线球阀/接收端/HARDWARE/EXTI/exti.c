#include "exti.h"
#include "delay.h" 
#include "24l01.h"



//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32F103������V1
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/10
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
u8 tx_buf[1]={0};
u8 e_flag[12]={0};
u16 flag[10]={0};
void EXTI0_IRQHandler(void)
{
	NRF24L01_TX_Mode();
	if(!e_flag[0])
	{tx_buf[0]= 10;
	 e_flag[0]++;}
	else 
	{
		tx_buf[0]= 11;
		e_flag[0]=0;
	}
	while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
	
	EXTI->RTSR|=1<<0;						//��������Ϊ�����ش���
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}
void EXTI1_IRQHandler(void)
{
	NRF24L01_TX_Mode();
	if(!e_flag[1])
	{tx_buf[0]= 20;
	e_flag[1]++;}
	else 
	{
		tx_buf[0]= 21;
		e_flag[1]=0;
	}
	while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
	
	EXTI->RTSR|=1<<1;						//��������Ϊ�����ش���
	EXTI->PR=1<<1;  //���LINE1�ϵ��жϱ�־λ  
}
void EXTI2_IRQHandler(void)
{
	NRF24L01_TX_Mode();
	if(!e_flag[2])
	{tx_buf[0]= 30;
	 e_flag[2]++;
	}
	else 
	{
		tx_buf[0]= 31;
		e_flag[2]=0;
	}
	while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
	
	EXTI->RTSR|=1<<2;						//��������Ϊ�����ش��� 
	EXTI->PR=1<<2;  //���LINE2�ϵ��жϱ�־λ  
}
void EXTI3_IRQHandler(void)
{
	NRF24L01_TX_Mode();
	if(!e_flag[3])
	{tx_buf[0]= 40;
	 e_flag[3]++;
	}
	else 
	{
		tx_buf[0]= 41;
		e_flag[3]=0;
	}
	while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
	
	EXTI->RTSR|=1<<3;						//��������Ϊ�����ش���  
	EXTI->PR=1<<3;  //���LINE3�ϵ��жϱ�־λ  
}
void EXTI4_IRQHandler(void)
{
	NRF24L01_TX_Mode();
	if(!e_flag[4])
	{tx_buf[0]= 50;
	 e_flag[4]++;
	}
	else 
	{
		tx_buf[0]= 51;
		e_flag[4]=0;
	}
	while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
	
	EXTI->RTSR|=1<<4;						//��������Ϊ�����ش���  	 
	EXTI->PR=1<<4;  //���LINE4�ϵ��жϱ�־λ  
}
//�ⲿ�ж�9-5�������
void EXTI9_5_IRQHandler(void)
{

	flag[0] = (EXTI->PR) & 0x20;
	flag[1] = (EXTI->PR) & 0x40;
	flag[2] = (EXTI->PR) & 0x80;
	flag[3] = (EXTI->PR) & 0x100;
	flag[4] = (EXTI->PR) & 0x200;
	
		if(flag[0])
		{
			if(!e_flag[5])
			{
				tx_buf[0]=60;
				e_flag[5]++;
				
			}
			else
			{
				tx_buf[0]=61;
				e_flag[5]=0;
			}
			flag[0]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<5;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<5;						//��������Ϊ�����ش���
		}
		
		else	if(flag[1])
		{
			if(!e_flag[6])
			{
				tx_buf[0]=70;
				e_flag[6]++;
				
			}
			else
			{
				tx_buf[0]=71;
				e_flag[6]=0;
			}
			flag[1]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<6;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<6;						//��������Ϊ�����ش���
		}
		else	if(flag[2])
		{
			if(!e_flag[7])
			{
				tx_buf[0]=80;
				e_flag[7]++;
				
			}
			else
			{
				tx_buf[0]=81;
				e_flag[7]=0;
			}
			flag[2]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<7;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<7;						//��������Ϊ�����ش���
		}
		
	
} 



void EXTI15_10_IRQHandler(void)
{
	flag[5] = (EXTI->PR) & 0x400;
	flag[6] = (EXTI->PR) & 0x800;
	flag[7] = (EXTI->PR) & 0x1000;
	flag[8] = (EXTI->PR) & 0x2000;
	flag[9] = (EXTI->PR) & 0x4000;
	
	if(flag[5])
		{
			if(!e_flag[8])
			{
				tx_buf[0]=90;
				e_flag[8]++;
				
			}
			else
			{
				tx_buf[0]=91;
				e_flag[8]=0;
			}
			flag[5]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<10;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<10;						//��������Ϊ�����ش���
		}
		
		else	if(flag[6])
		{
			if(!e_flag[9])
			{
				tx_buf[0]=100;
				e_flag[9]++;
				
			}
			else
			{
				tx_buf[0]=101;
				e_flag[9]=0;
			}
			flag[6]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<11;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<11;						//��������Ϊ�����ش���
		}
		else	if(flag[7])
		{
			if(!e_flag[10])
			{
				tx_buf[0]=110;
				e_flag[10]++;
				
			}
			else
			{
				tx_buf[0]=111;
				e_flag[10]=0;
			}
			flag[7]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<12;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<12;						//��������Ϊ�����ش���
		}
		else	if(flag[9])
		{
			if(!e_flag[11])
			{
				tx_buf[0]=120;
				e_flag[11]++;
				
			}
			else
			{
				tx_buf[0]=121;
				e_flag[11]=0;
			}
			flag[9]=0;
			while(NRF24L01_TxPacket(tx_buf) != 0){delay_ms(10);}
			EXTI->PR=1<<14;  							//���LINE9�ϵ��жϱ�־λ
			EXTI->RTSR|=1<<14;						//��������Ϊ�����ش���
		}
		
	
} 

   
//�ⲿ�жϳ�ʼ������
//��ʼ��PA0/PE3/PE4Ϊ�ж�����.
void EXTIX_Init(void)
{
	
	Ex_NVIC_Config(GPIO_A,0,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,1,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,2,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,3,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,4,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,5,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,6,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,7,FTIR); 	//�½��ش��� 
	Ex_NVIC_Config(GPIO_A,12,FTIR); //�½��ش��� 
  Ex_NVIC_Config(GPIO_B,10,FTIR); //�½��ش��� 
	Ex_NVIC_Config(GPIO_B,11,FTIR); //�½��ش���
  Ex_NVIC_Config(GPIO_C,14,FTIR); //�½��ش���	


 	
 
	MY_NVIC_Init(2,1,EXTI0_IRQn,2);	//��ռ2�������ȼ�1����2
	MY_NVIC_Init(2,1,EXTI1_IRQn,2);	//��ռ2�������ȼ�1����2
	MY_NVIC_Init(2,1,EXTI2_IRQn,2);	//��ռ2�������ȼ�1����2
	MY_NVIC_Init(2,1,EXTI3_IRQn,2);	//��ռ2�������ȼ�1����2
	MY_NVIC_Init(2,1,EXTI4_IRQn,2);	//��ռ2�������ȼ�1����2
	MY_NVIC_Init(2,1,EXTI9_5_IRQn,2);	//��ռ2�������ȼ�1����2
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);	//��ռ2�������ȼ�1����2

  
}












