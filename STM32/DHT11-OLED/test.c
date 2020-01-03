#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "oled.h"
#include "myiic.h"
#include "dht11.h"
int main(void)
{
	
	u8 temperature;  	    
	u8 humidity; 
	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72); //��ʱ��ʼ��
	uart_init(72,115200); //���ڳ�ʼ��Ϊ 115200
	LED_Init();
	IIC_Init();
	OLED_Init();
	OLED_Clear();
	while(DHT11_Init())	//DHT11��ʼ��	
	{
		OLED_ShowString(0,0,"DHT11-ERROR",16);//0��,0��
		delay_ms(200);
		OLED_Clear();
 		delay_ms(200);
	}		
	OLED_ShowString(0,0,"STM32-DHT11-Test",16);//0��,0��
	OLED_ShowString(0,2,"     Auther     ",16);//0��,0��
	OLED_ShowString(0,4,"  Wang Xiuting  ",16);//0��,0��
	OLED_ShowString(0,6,"    16114208    ",16);//0��,0��
	DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
 	delay_ms(800);
	delay_ms(800);
	delay_ms(800);
	OLED_Clear();
	OLED_ShowString(0,0,"Temp:    ~C",16);//0��,0��
	OLED_ShowString(0,2,"Humi:    %",16);//0��,2��

	
	while(1)
{
	DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
	OLED_ShowNum(44,2,humidity,2,16);
	OLED_ShowNum(44,0,temperature,2,16);
	LED0=0;
	delay_ms(500);
	LED0=1;
	delay_ms(500);

}
}

