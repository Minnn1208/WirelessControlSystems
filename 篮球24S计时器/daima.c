#include <REGX52.H>

sbit C=P2^4;
sbit B1=P2^3;
sbit A=P2^2;

unsigned char code table[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  //数码管显示的数字



//延迟函数
void Delay10000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	i = 1000;
	j = 59;
	k = 28;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
	int time=24;
	int count=0;
	while(1)
	{
		while(time>0)
		{
			//000数码管第一位
			C=1;
			B1=1;
			A=1;
			P0=table[time/10];
			P0=0;
			Delay10000ms();
			//001数码管第二位
			C=1;
			B1=1;
			A=0;
			P0=table[time%10];
			P0=0;
			
			Delay10000ms();

			time--;
		}
	
		
		if(time==0)
			{	
				while(1)
				{
				//000数码管第一位
				C=1;
				B1=1;
				A=1;
				P0=table[time/10];
				P0=0;
				Delay10000ms();
				//000数码管第二位
				C=1;
				B1=1;
				A=0;
				P0=table[time%10];
				P0=0;
			
				Delay10000ms();
				}
			}
		   
	}
}



