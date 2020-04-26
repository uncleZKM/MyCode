#include <wiringPi.h>  
#include <stdio.h>

//IO方向设置
#define DS18B20_IO_IN()  	pinMode (7, INPUT)
#define DS18B20_IO_OUT() 	pinMode (7, OUTPUT)

////IO操作函数											   
#define	DS18B20_DQ_OUT1 digitalWrite(7, HIGH) 		//数据端口 
#define	DS18B20_DQ_OUT0 digitalWrite(7, LOW) 		//数据端口 
#define	DS18B20_DQ_IN  	digitalRead(7)  		   //数据端口	
#define   u8	unsigned char 
#define   u16  	unsigned int

u8 DS18B20_Init(void);			//初始化DS18B20
short DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20   

//复位DS18B20
void DS18B20_Rst(void)	   
{                 
	DS18B20_IO_OUT(); 	//SET GPIO7 OUTPUT
    DS18B20_DQ_OUT0; 	//拉低DQ
    delayMicroseconds(750);    	//拉低750us
    DS18B20_DQ_OUT1; 	//DQ1 
	delayMicroseconds(15);     	//15US
}

//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 DS18B20_Check(void) 	   
{   
	u8 retry=0;
	DS18B20_IO_IN();	//SET GPIO7 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delayMicroseconds(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delayMicroseconds(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
u8 DS18B20_Init(void)
{
	wiringPiSetup() ;
	DS18B20_Rst();
	return DS18B20_Check();
}  

//从DS18B20读取一个位
//返回值：1/0
u8 DS18B20_Read_Bit(void) 	 
{
    u8 data;
	DS18B20_IO_OUT();	//SET PG11 OUTPUT
    DS18B20_DQ_OUT0; 
	delayMicroseconds(2);
    DS18B20_DQ_OUT1; 
	DS18B20_IO_IN();	//SET PG11 INPUT
	delayMicroseconds(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    delayMicroseconds(50);           
    return data;
}

//从DS18B20读取一个字节
//返回值：读到的数据
u8 DS18B20_Read_Byte(void)     
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}

//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(u8 dat)     
 {             
    u8 j;
    u8 testb;
	DS18B20_IO_OUT();	//SET PG11 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT0;	// Write 1
            delayMicroseconds(2);                            
            DS18B20_DQ_OUT1;
            delayMicroseconds(60);             
        }
        else 
        {
            DS18B20_DQ_OUT0;	// Write 0
            delayMicroseconds(60);             
            DS18B20_DQ_OUT1;
            delayMicroseconds(2);                          
        }
    }
}


//开始温度转换
void DS18B20_Start(void) 
{   						               
    DS18B20_Rst();	   
	DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
} 

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
short DS18B20_Get_Temp(void)
{
    u8 temp;
    u8 TL,TH;
	short tem;
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// convert	    
    TL=DS18B20_Read_Byte(); 	// LSB   
    TH=DS18B20_Read_Byte(); 	// MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;					//温度为负  
    }else temp=1;				//温度为正	  	  
    tem=TH; 					//获得高八位
    tem<<=8;    
    tem+=TL;					//获得底八位
    tem=(float)tem*0.625;		//转换     
	if(temp)return tem; 		//返回温度值
	else return -tem;    
}

/*
int main()
{
	short temp;
	DS18B20_Init();
	while(1)
	{
		temp = DS18B20_Get_Temp();
		printf("temp->%d\n",temp);
		delay(800);
	}
	
	
	return 0;
}
*/