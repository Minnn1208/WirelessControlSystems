#include<reg52.h>
#include<stdio.h>
void UartInit(void)		//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

void UART1_SendData(char dat)
{
	ES=0;			//关串口中断
	SBUF=dat;			
	while(TI!=1);	//等待发送成功
	TI=0;			//清除发送中断标志
	ES=1;			//开串口中断
}

char putchar(char c)
{
	UART1_SendData(c);
	return c;
}



