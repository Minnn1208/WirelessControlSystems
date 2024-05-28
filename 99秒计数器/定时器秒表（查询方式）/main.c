/**************************************************************************************
*		              定时器秒表(查询方式)实验												  *
实现现象：下载程序后数码管最后两位实现秒表功能。
注意事项：如果不想让点阵模块显示，可以将74HC595模块上的JP595短接片拔掉。																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
u16 s;
u8 sec,mb[2];

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
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
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


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	
	Timer0Init();
	while(1)
	{
		if(TF0==1)
		{
			TF0=0;
			TH0=0XFC;	//给定时器赋初值，定时1ms
			TL0=0X18;
			s++;
		}
		if(s==1000)		 //到达1s时间
		{	
			s=0;
			sec++;
			if(sec==100)sec=0;	 //计时到100秒后重新开始
		}
		mb[0]=sec%10;	   //秒表个位
	    mb[1]=sec/10;	   //秒表十位
		DigDisplay();	   //消隐
	}
}
