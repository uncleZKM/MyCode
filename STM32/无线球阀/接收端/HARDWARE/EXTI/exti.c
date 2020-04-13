#include "exti.h"
#include "delay.h" 
#include "24l01.h"



//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32F103开发板V1
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/10
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
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
	
	EXTI->RTSR|=1<<0;						//立即设置为上升沿触发
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
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
	
	EXTI->RTSR|=1<<1;						//立即设置为上升沿触发
	EXTI->PR=1<<1;  //清除LINE1上的中断标志位  
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
	
	EXTI->RTSR|=1<<2;						//立即设置为上升沿触发 
	EXTI->PR=1<<2;  //清除LINE2上的中断标志位  
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
	
	EXTI->RTSR|=1<<3;						//立即设置为上升沿触发  
	EXTI->PR=1<<3;  //清除LINE3上的中断标志位  
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
	
	EXTI->RTSR|=1<<4;						//立即设置为上升沿触发  	 
	EXTI->PR=1<<4;  //清除LINE4上的中断标志位  
}
//外部中断9-5服务程序
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
			EXTI->PR=1<<5;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<5;						//立即设置为上升沿触发
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
			EXTI->PR=1<<6;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<6;						//立即设置为上升沿触发
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
			EXTI->PR=1<<7;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<7;						//立即设置为上升沿触发
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
			EXTI->PR=1<<10;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<10;						//立即设置为上升沿触发
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
			EXTI->PR=1<<11;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<11;						//立即设置为上升沿触发
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
			EXTI->PR=1<<12;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<12;						//立即设置为上升沿触发
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
			EXTI->PR=1<<14;  							//清除LINE9上的中断标志位
			EXTI->RTSR|=1<<14;						//立即设置为上升沿触发
		}
		
	
} 

   
//外部中断初始化程序
//初始化PA0/PE3/PE4为中断输入.
void EXTIX_Init(void)
{
	
	Ex_NVIC_Config(GPIO_A,0,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,1,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,2,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,3,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,4,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,5,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,6,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,7,FTIR); 	//下降沿触发 
	Ex_NVIC_Config(GPIO_A,12,FTIR); //下降沿触发 
  Ex_NVIC_Config(GPIO_B,10,FTIR); //下降沿触发 
	Ex_NVIC_Config(GPIO_B,11,FTIR); //下降沿触发
  Ex_NVIC_Config(GPIO_C,14,FTIR); //下降沿触发	


 	
 
	MY_NVIC_Init(2,1,EXTI0_IRQn,2);	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,1,EXTI1_IRQn,2);	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,1,EXTI2_IRQn,2);	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,1,EXTI3_IRQn,2);	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,1,EXTI4_IRQn,2);	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,1,EXTI9_5_IRQn,2);	//抢占2，子优先级1，组2
	MY_NVIC_Init(2,1,EXTI15_10_IRQn,2);	//抢占2，子优先级1，组2

  
}












