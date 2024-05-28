#include <REGX52.H>
#include "Timer0.h"
#include "Int0.h"

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Data[4];
unsigned char IR_pData;

unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;

/**
  * @brief  红外遥控初始化
  * @param  无
  * @retval 无
  */
void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();
}

/**
  * @brief  红外遥控获取接收到数据帧标志位
  * @param  无
  * @retval 是否接收到数据帧，1为接收到，0为未接收到
  */
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief  红外遥控获取接收到连发帧标志位
  * @param  无
  * @retval 是否接收到连发帧，1为接收到，0为未接收到
  */
unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief  红外遥控获取接收到的地址数据
  * @param  无
  * @retval 接收到的地址数据
  */
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

/**
  * @brief  红外遥控获取接收到的指令数据
  * @param  无
  * @retval 接收到的指令数据
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

//外部中断0中断函数，下降沿触发执行
void Int0_Routine(void) interrupt 0
{
	if(IR_State==0)				//状态，空闲状态
	{
		Timer0_SetCounter(0);	//定时器计数器清0
		Timer0_Run(1);			//定时器开始计时
		IR_State=1;				//状态变为1
	}
	else if(IR_State==1)		//状态，等待start帧或Repeat帧
	{
		IR_Time=Timer0_GetCounter();	//获取上一次中断到此次中断的时间
		Timer0_SetCounter(0);	//定时器计数器清0
		//如果计时为3.5ms，则接收到了Start帧，（判断值在12MHz晶振下为13500，在11.0592MHz晶振下为12442）
		if(IR_Time>13500-500 && IR_Time<13500+500)
		{
			IR_State=2;			//状态变为2
		}
		//如果计时为1.25ms，则接收到了Repeat帧，（判断值在12MHz晶振下为11250，在11.0592MHz晶振下为10368）
		else if(IR_Time>11250-500 && IR_Time<11250+500)
		{
			IR_RepeatFlag=1;	//接收到连发帧标志位为1
			Timer0_Run(0);		//定时器停止
			IR_State=0;			//状态变为0
		}
		else					//接收错误
		{
			IR_State=1;			//状态变为1
		}
	}
	else if(IR_State==2)		//状态，接收数据
	{
		IR_Time=Timer0_GetCounter();	//获取上一次中断到此次中断的时间
		Timer0_SetCounter(0);	//定时器计数器清0
		//如果计时为120us，则接收到了数据0，（判断值在12MHz晶振下为1120，在11.0592MHz晶振下为1032）
		if(IR_Time>1120-500 && IR_Time<1120+500)
		{
			IR_Data[IR_pData/8]&=~(0x01<<(IR_pData%8));	//数据对应位清0
			IR_pData++;			//数据位指针自增
		}
		//如果计时为250us，则接收到了数据1，（判断值在12MHz晶振下为2250，在11.0592MHz晶振下为2074）
		else if(IR_Time>2250-500 && IR_Time<2250+500)
		{
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//数据对应位置1
			IR_pData++;			//数据位指针自增
		}
		else					//接收错误
		{
			IR_pData=0;			//数据位指针清0
			IR_State=1;			//状态变为1
		}
		if(IR_pData>=32)		//如果接收到了32位数据
		{
			IR_pData=0;			//数据位指针清0
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))	//数据校验
			{
				IR_Address=IR_Data[0];	//存储数据
				IR_Command=IR_Data[2];
				IR_DataFlag=1;	//接收到连发帧标志位为1
			}
			Timer0_Run(0);		//定时器停止
			IR_State=0;			//状态变为0
		}
	}
}