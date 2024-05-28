#include <reg51.h>
#include <intrins.h>
 
typedef unsigned char u8;
typedef unsigned int u16;
 
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
 
u8 code ledduan[][8]={{0x00,0x00,0x32,0x49,0x49,0x49,0x3e,0x00},     //9
                      {0x00,0x00,0x36,0x49,0x49,0x49,0x36,0x00},     //8
                      {0x00,0x00,0x40,0x40,0x4f,0x50,0x60,0x00},     //7
                      {0x00,0x00,0x3e,0x49,0x49,0x49,0x26,0x00},     //6
                      {0x00,0x00,0x72,0x51,0x51,0x51,0x4e,0x00},     //5
                      {0x00,0x00,0x0c,0x14,0x24,0x7f,0x04,0x00},     //4
                      {0x00,0x00,0x2a,0x49,0x49,0x49,0x36,0x00},     //3
                      {0x00,0x00,0x27,0x45,0x45,0x45,0x39,0x00},     //2
                      {0x00,0x00,0x00,0x21,0x7f,0x01,0x00,0x00},     //1
                      {0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00}};    //0


//u8 code ledduan[3][8]={{0x00,0x00,0x81,0xFF,0xFF,0x81,0x00,0x00},     //I
//                      {0x38,0x7C,0x7E,0x3F,0x3F,0x7E,0x7C,0x38},     //ai 
//                      {0x00,0xFE,0x01,0x01,0x01,0x01,0xFE,0x00},};   //U
 
u8 ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe}; 
 
 
void delay(u16 i)
{
	while(i--);
}
 
void Hc595SendByte(u8 dat)
{
   u8 i;
   SRCLK=0;
	 RCLK=0;
   for(i=0;i<8;i++)
   {
		SER=dat>>7;
		dat<<=1;
		 
		SRCLK=1;
    _nop_();
		_nop_();
		SRCLK=0;
   }
	 RCLK=1;
	 _nop_();
	 _nop_();
	 RCLK=0; 
}
 
int main()
{
	u16 i,j,k;
	while(1)
	{                                                
		for(j=0;j<80;j++)                           //控制数字到下一个数字的速度
		{
			for(i=0;i<8;i++)
			{
				P0=ledwei[i];
//				delay(5000);	
				Hc595SendByte(ledduan[k][i]);
				delay(150);				
				Hc595SendByte(0x00);
			}
		}
		k++;                                       //ldeduan的数组++
	  if(k>=10)                                    //当k>=10,
		{
			k=0;                                   //k=0
		}
	}
}