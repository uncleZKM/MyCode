#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 	 
#include "timer.h"

//****************************自定义变量******************************************
u8  cmdOpen  = 0;								//开启球阀标志位
u8  cmdClose = 0;								//关闭球阀标志位
u8  openErr  = 0;								//开启球阀异常标志位
u8  closeErr = 0;								//关闭球阀异常标志位
u16 getNum   = 0;								//读取的流量计脉冲次数
u8 start;
u16 time;
#define Open  0x0A
#define Close 0x0B
//****************************自定义变量******************************************//

void usart1_send(u8 action);
u16 t; 
char date[6]={0xaA,0xBB,0x17,0x0A,0x0d,0x0a}; 

int main(void)
{								  	  
	Stm32_Clock_Init(9);	//系统时钟设置
	uart_init(72,9600); 	//串口初始化为9600
	delay_init(72);	   	 	//延时初始化 
	LED_Init();		  		//初始化与LED连接的硬件接口 
	TIM4_Cap_Init(100,719);  //1ms溢出一次
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
				while((USART1->SR&0X40)==0);						//等待发送完成
				
			}
			time = 0;

}
