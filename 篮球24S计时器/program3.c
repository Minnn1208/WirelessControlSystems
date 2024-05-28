#include <REGX52.H>

sbit C=P2^4;
sbit B1=P2^3;
sbit A=P2^2;

unsigned char code table[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  //数码管显示的数字



//延迟函数
void delay1s(void)
{
  unsigned char h,i,j,k;
  for(h=50;h>0;h--)
  for(i=400;i>0;i--)
  for(j=116;j>0;j--)
  for(k=214;k>0;k--);
}



void main()
{
	int time=24;
	int count=0;
	while(1)
	{
		while(time=1)
		{
			//000数码管第一位
			C=1;
			B1=1;
			A=1;
			P0=table[time/10];
			P0=0;
			delay1s();
			//001数码管第二位

			
		}


		   
	}
}

