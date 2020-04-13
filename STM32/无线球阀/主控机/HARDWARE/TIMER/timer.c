#include "timer.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
//////////////////////////////////////////////////////////////////////////////////	 
#define Open 			0x01			//开启球阀
#define Shutdown 	0x00			//关闭球阀
//////////////////////////////////////////////////////////////////////////////////   	 
extern u16 time;
extern void uart1_send_cmd(u8 action);
extern u8 Send_cmd,Get_cmd,Success;


//arr：自动重装值
//psc：时钟预分频数
void TIM4_Cap_Init(u16 arr,u16 psc)
{		 
	
	RCC->APB1ENR|=1<<2;   			//TIM4 时钟使能 
	RCC->APB2ENR|=1<<3;    			//使能PORTB时钟 

	GPIOB->CRH&=0XFFFFFF00;			//PB8,9 输入  
	GPIOB->CRH|=0X00000088;			//输入模式    
	GPIOB->ODR&=~(1<<9);				//PB8,9 下拉
	GPIOB->ODR&=~(1<<8);				//PB8,9下拉
	  

	
	TIM4->ARR=arr;  			//设定计数器自动重装值 最大10ms溢出  
	TIM4->PSC=psc;  			//预分频器,1M的计数频率,1us加1.

	TIM4->CCMR2|=1<<8  | 1;				//CC4S=01 	选择输入端 IC4映射到TI4上
 	TIM4->CCMR2|=3<<12 | 3<<4;  	//IC4F=0011 配置输入滤波器 8个定时器时钟周期滤波
 	TIM4->CCMR2|=0<<10 | 0<<2;  	//IC4PS=00 	配置输入分频,不分频 

	TIM4->CCER|=0<<13; 						//CC4P=0	上升沿捕获
	TIM4->CCER|=1<<12 | 1<<8; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
	TIM4->DIER|=1<<4  | 1<<3;   	//允许CC4IE捕获中断				
	TIM4->DIER|=1<<0;   					//允许更新中断				
	TIM4->CR1|=0x01;    					//使能定时器4
  MY_NVIC_Init(3,3,TIM4_IRQn,2);//抢占1，子优先级3，组2	
}


//定时器5中断服务程序	 
void TIM4_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM4->SR;
	if(tsr&0X01)//溢出
	{
			time++;
		if(Send_cmd)															//刚发送命令
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
				if(!Success)													//接收端成功执行任务
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
	
	if(tsr&0X10)//上升沿捕获
	{
		uart1_send_cmd(Shutdown);
		OLED_Clear();
		OLED_ShowString(0,2,"Start Connect...",16);
		OLED_ShowString(0,0,"Task: Shutdown",16);
		Send_cmd = 1;						//标记命令已发出
		Success = 0;						//清零上次执行失败的标志位
		time = 0;								//定时器开始累加计时
	}		
	if(tsr&0X8)//上升沿捕获
	{
		uart1_send_cmd(Open);
		OLED_Clear();
		OLED_ShowString(0,2,"Start Connect...",16);
		OLED_ShowString(0,0,"Task: Open",16);
		Send_cmd = 1;						//标记命令已发出
		Success = 0;						//清零上次执行失败的标志位
		time = 0;								//定时器开始累加计时
	}		
	TIM4->SR=0;//清除中断标志位 
}














