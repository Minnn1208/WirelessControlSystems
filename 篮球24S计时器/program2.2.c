#include <reg52.H>

sbit C=P2^4;
sbit B1=P2^3;
sbit A=P2^2;
sbit key=P3^2;
sbit key2=P3^1;

unsigned char code table[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};  //数码管显示的数字
//0x3f = 0011 1111  1100  0000  0000 0110

void main()
{

	
	int time=24;
	TMOD|=0X01;

	TH0=(65536-12100)/256;
	TL0=(65536-12100)%256;		
	ET0=1;		
	EA=1;
	while(1)
	{
		if(key==0){
			while(1){
			time=24;
			C=1;
			B1=1;
			A=1;
			P0=table[time/10];
			P0=0;
			
			//001数码管第二位
			C=1;
			B1=1;
			A=0;
			P0=table[time%10];
			P0=0;
		}
			
	}
		
		while(1)
		{
			

			//000数码管第一位
			C=1;              
			B1=1;
			A=1;
			P0=table[time/10];
			P0=0;
			
			//001数码管第二位
			C=1;
			B1=1;
			A=0;
			P0=table[time%10];
			P0=0;
			
			if(key3 == 0){
				while(1){
					C=1;              
					B1=1;
					A=1;
					P0=table[time/10];
					P0=0;
			
					//001数码管第二位
					C=1;
					B1=1;
					A=0;
					P0=table[time%10];
					P0=0;
					if(key2 == 0){
						break;
					}
				}
			}


			count++;

			if(count==25000)
			{
				count=0;
				time--;
				break;
			}
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
			
					//000数码管第二位
					C=1;
					B1=1;
					A=0;
					P0=table[time%10];
					P0=0;
			
					count++;
					if(count==25000)
					{	

						break;
					}
			
				}
				break;
			}
		 
	}
}