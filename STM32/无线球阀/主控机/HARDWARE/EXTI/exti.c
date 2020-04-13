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
			EXTI->IMR&=~(1<<15);			//�Լ���ɺ���ʹ���ⲿ�ж�15�������ⲿ�ж���15������¼�

	}
	EXTI->PR=1<<15;  							//���LINE15�ϵ��жϱ�־λ
} 

//
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
  Ex_NVIC_Config(GPIO_B,15,FTIR); //�½��ش���	
	MY_NVIC_Init(0,3,EXTI15_10_IRQn,2);	//��ռ2�������ȼ�1����2

}












