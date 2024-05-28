#include "reg52.h"
#include "public.h"
#include "display.h"

u8 mb[2];

//定义数码管显示
u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

/*******************************************************************************
* 函 数 名         : Timer0Init
* 函数功能		   : 定时器0初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X18;	
	TR0=1;//打开定时器			
}

/*******************************************************************************
* 函 数 名         : DigDisplay
* 函数功能		   : 数码管动态扫描函数，循环扫描2个数码管显示
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0;i<2;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;	
		}
		P0=smgduan[mb[i]];//发送段码
		delay(1); //间隔一段时间扫描	
		P0=0x00;//消隐
	}
}