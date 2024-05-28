/*******************************************************************************
* 实验名			   :温度显示实验
* 使用的IO	     : 
* 实验效果       :1602显示温度
*	注意					 ：
*******************************************************************************/

#include<reg51.h>
#include"lcd.h"
#include"temp.h"

uchar CNCHAR[6] = "摄氏度";
void LcdDisplay(float);
void UsartConfiguration();

/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void main()
{
	UsartConfiguration();
	LcdInit();			 //初始化LCD1602
	LcdWriteCom(0x88);	//写地址 80表示初始地址
	LcdWriteData('C'); 
	while(1)
	{
		LcdDisplay(Ds18b20ReadTemp());
//		Delay1ms(1000);//1s钟刷一次
	}
}

/*******************************************************************************
* 函数名         : LcdDisplay()
* 函数功能		   : LCD显示读取到的温度
* 输入           : v
* 输出         	 : 无
*******************************************************************************/

/*******************************************************************************
* 函数名称    : LcdDisplay
* 函数功能    : 显示摄氏度温度
* 输入参数    : temp_celsius - 摄氏度温度值
* 输出参数    : 无
*******************************************************************************/
void LcdDisplay(float temp_celsius) {
    unsigned char datas[] = {0, 0, 0, 0, 0, 0, 0}; // 存储温度数据
    unsigned int temp_int;
    unsigned int temp_decimal;
    unsigned char i;

    // 分离整数部分和小数部分
    temp_int = (unsigned int)temp_celsius;
    temp_decimal = (unsigned int)((temp_celsius - temp_int) * 10000);

    // 提取温度整数部分的每一位
    datas[0] = temp_int / 10 % 10; // 十位
    datas[1] = temp_int % 10;      // 个位

    // 提取温度小数部分的每一位
    datas[2] = temp_decimal / 1000; // 千位
    datas[3] = temp_decimal / 100 % 10; // 百位
    datas[4] = temp_decimal / 10 % 10;  // 十位
    datas[5] = temp_decimal % 10;       // 个位

    // 温度整数部分的第一行显示
    LcdWriteCom(0x80); // 设置显示位置为第一行第一个位置
    LcdWriteData('T'); // 温度标题
    LcdWriteData('e');
    LcdWriteData('m');
    LcdWriteData('p');
    LcdWriteData('e');
    LcdWriteData('r');
    LcdWriteData('a');
    LcdWriteData('t');
    LcdWriteData('u');
    LcdWriteData('r');
    LcdWriteData('e');
    LcdWriteData(':');

    // 温度数值的第二行显示
    LcdWriteCom(0xC0); // 设置显示位置为第二行第一个位置
    LcdWriteData(' '); // 温度整数部分的第一个空格
    LcdWriteData(' '); // 温度整数部分的第二个空格
    LcdWriteData('0' + datas[0]); // 温度整数部分
    LcdWriteData('0' + datas[1]);
    LcdWriteData('.');

    LcdWriteData('0' + datas[2]); // 温度小数部分
    LcdWriteData('0' + datas[3]);
    LcdWriteData('0' + datas[4]);
    LcdWriteData('0' + datas[5]);
    LcdWriteData('C'); // 摄氏度符号
}




/*******************************************************************************
* 函 数 名         :UsartConfiguration()
* 函数功能		   :设置串口
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void UsartConfiguration()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
//	ES=1;						//打开接收中断
//	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}
