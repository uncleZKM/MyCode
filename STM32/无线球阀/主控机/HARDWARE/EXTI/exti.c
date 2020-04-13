#include "exti.h"
#include "delay.h"
#include "led.h" 
#include "oled.h"
extern u8 LORA_Check_Flag,send_flag;
extern void uart1_send_cmd(void);
void EXTI15_10_IRQHandler(void)
{
	u16 flag;
	flag = (EXTI->PR) & 0x8000;
	
	if(flag)
	{
			
			if(LORA_Check_Flag==0)
			{
				OLED_Clear();
				OLED_ShowString(0,0,"    LORA--OK    ",16);
				delay_ms(2500);
				LORA_Check_Flag++;
			}
			EXTI->IMR&=~(1<<15);			//自检完成后不再使用外部中断15，屏蔽外部中断线15上面的事件

	}
	EXTI->PR=1<<15;  							//清除LINE15上的中断标志位
} 

//
//外部中断初始化程序
void EXTIX_Init(void)
{
  Ex_NVIC_Config(GPIO_B,15,FTIR); //下降沿触发	
	MY_NVIC_Init(0,3,EXTI15_10_IRQn,2);	//抢占2，子优先级1，组2

}












