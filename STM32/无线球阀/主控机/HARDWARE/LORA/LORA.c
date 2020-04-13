#include "sys.h"		
#include "delay.h"	
#include "led.h" 
#include "oled.h"
#include "LORA.h"

char check[3] = {0xc4,0xc4,0xc4};
extern u8 LORA_Check_Flag;
u8 p;
void LORA_Check(void)
{
	LORA_Check_Flag = 0;
	for(p=0;p<3;p++)
			{
				USART1->DR=(check[p] & (uint16_t)0x01FF);
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			

	while(LORA_Check_Flag==0)
	{
		PBout(5)=1;		//进入命令模式
			for(p=0;p<3;p++)
			{
				USART1->DR=(check[p] & (uint16_t)0x01FF);
				while((USART1->SR&0X40)==0);//等待发送结束
			}
		delay_ms(800);
		if(LORA_Check_Flag==0)
		{
			OLED_Clear();
			OLED_ShowString(0,0," LORA_Check_Fail",16);
		}
		PBout(5)=0;
	}
	PBout(5)=0;
}

void LORA_Init(void)
{
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟	   	 
 	 
	GPIOB->CRL&=0XFF0FFFFF; 
	GPIOB->CRL|=0X00300000;//PB5推挽输出 
	GPIOB->ODR|=1<<5;      //Pb5输出高	
}
