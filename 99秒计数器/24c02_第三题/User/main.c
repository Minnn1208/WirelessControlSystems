#include<reg52.h>
#include<24c02.h>
//#include<serial_debug.h>

#define EEPROM_ADDRESS	0	//定义数据存入EEPROM的起始地址

//定义数码管引脚
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//定义数码管显示
u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

u16 s = 0;
u8 mb[2];
u8 sec = 0;


void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	TR0=1;//打开定时器			
}


void DigDisplay()
{
	u8 i;
	for(i=0;i<2;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位	
		}
		P0=smgduan[mb[i]];//发送段码
		delay(1); //间隔一段时间扫描	
		P0=0x00;//消隐
	}
}


void main()
{	
	Timer0Init();
	while(1)
	{
		sec = at24c02_read_one_byte(EEPROM_ADDRESS);

	  	if(TF0==1)
		{
			TF0=0;
			TH0=0XFC;	//给定时器赋初值，定时1ms
			TL0=0X18;
			s++;
		}
		if(s==220)		 //到达1s时间，调整
		{	
			s = 0;
			sec++;
			if(sec==100) sec=0;	 //计时到99秒后重新开始
			at24c02_write_one_byte(EEPROM_ADDRESS,sec);
		}
		mb[0]=sec%10;	   //秒表个位
	    mb[1]=sec/10;	   //秒表十位
		DigDisplay();
	}
}