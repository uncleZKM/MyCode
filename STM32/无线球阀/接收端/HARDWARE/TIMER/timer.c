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
//定时器5通道1输入捕获配置
//arr：自动重装值
//psc：时钟预分频数
void TIM4_Cap_Init(u16 arr,u16 psc)
{		 
	
	RCC->APB1ENR|=1<<2;   	//TIM4 时钟使能 
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟 

	GPIOB->CRH&=0XFFFFFF0F;	//PB9 输入  
	GPIOB->CRH|=0X00000080;	//输入模式    
	GPIOB->ODR&=~(1<<9);		//PB9 下拉
	  
// 	TIM4->ARR=10000;  		//设定计数器自动重装值 最大10ms溢出  
//	TIM4->PSC=71;  			//预分频器,1M的计数频率,1us加1.	 
	
	TIM4->ARR=arr;  		//设定计数器自动重装值 最大10ms溢出  
	TIM4->PSC=psc;  			//预分频器,1M的计数频率,1us加1.

	TIM4->CCMR2|=1<<8;		//CC4S=01 	选择输入端 IC4映射到TI4上
 	TIM4->CCMR2|=3<<12;  	//IC4F=0011 配置输入滤波器 8个定时器时钟周期滤波
 	TIM4->CCMR2|=0<<10;  	//IC4PS=00 	配置输入分频,不分频 

	TIM4->CCER|=0<<13; 		//CC4P=0	上升沿捕获
	TIM4->CCER|=1<<12; 		//CC4E=1 	允许捕获计数器的值到捕获寄存器中
	TIM4->DIER|=1<<4;   	//允许CC4IE捕获中断				
	TIM4->DIER|=1<<0;   	//允许更新中断				
	TIM4->CR1|=0x01;    	//使能定时器4
  MY_NVIC_Init(3,3,TIM4_IRQn,2);//抢占1，子优先级3，组2	
}

//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到高电平;1,已经捕获到高电平了.
//[5:0]:捕获高电平后溢出的次数
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
//定时器5中断服务程序	 
void TIM4_IRQHandler(void)
{ 		    
	u16 tsr;
	tsr=TIM4->SR;
	if(tsr&0X01)//溢出
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
	if(tsr&0X10)//上升沿捕获
	{
		if(start)
			getNum++;
	}		
	TIM4->SR=0;//清除中断标志位 
}















