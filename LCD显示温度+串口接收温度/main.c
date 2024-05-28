/*******************************************************************************
* ʵ����			   :�¶���ʾʵ��
* ʹ�õ�IO	     : 
* ʵ��Ч��       :1602��ʾ�¶�
*	ע��					 ��
*******************************************************************************/

#include<reg51.h>
#include"lcd.h"
#include"temp.h"

uchar CNCHAR[6] = "���϶�";
void LcdDisplay(float);
void UsartConfiguration();

/*******************************************************************************
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
	UsartConfiguration();
	LcdInit();			 //��ʼ��LCD1602
	LcdWriteCom(0x88);	//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('C'); 
	while(1)
	{
		LcdDisplay(Ds18b20ReadTemp());
//		Delay1ms(1000);//1s��ˢһ��
	}
}

/*******************************************************************************
* ������         : LcdDisplay()
* ��������		   : LCD��ʾ��ȡ�����¶�
* ����           : v
* ���         	 : ��
*******************************************************************************/

/*******************************************************************************
* ��������    : LcdDisplay
* ��������    : ��ʾ���϶��¶�
* �������    : temp_celsius - ���϶��¶�ֵ
* �������    : ��
*******************************************************************************/
void LcdDisplay(float temp_celsius) {
    unsigned char datas[] = {0, 0, 0, 0, 0, 0, 0}; // �洢�¶�����
    unsigned int temp_int;
    unsigned int temp_decimal;
    unsigned char i;

    // �����������ֺ�С������
    temp_int = (unsigned int)temp_celsius;
    temp_decimal = (unsigned int)((temp_celsius - temp_int) * 10000);

    // ��ȡ�¶��������ֵ�ÿһλ
    datas[0] = temp_int / 10 % 10; // ʮλ
    datas[1] = temp_int % 10;      // ��λ

    // ��ȡ�¶�С�����ֵ�ÿһλ
    datas[2] = temp_decimal / 1000; // ǧλ
    datas[3] = temp_decimal / 100 % 10; // ��λ
    datas[4] = temp_decimal / 10 % 10;  // ʮλ
    datas[5] = temp_decimal % 10;       // ��λ

    // �¶��������ֵĵ�һ����ʾ
    LcdWriteCom(0x80); // ������ʾλ��Ϊ��һ�е�һ��λ��
    LcdWriteData('T'); // �¶ȱ���
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

    // �¶���ֵ�ĵڶ�����ʾ
    LcdWriteCom(0xC0); // ������ʾλ��Ϊ�ڶ��е�һ��λ��
    LcdWriteData(' '); // �¶��������ֵĵ�һ���ո�
    LcdWriteData(' '); // �¶��������ֵĵڶ����ո�
    LcdWriteData('0' + datas[0]); // �¶���������
    LcdWriteData('0' + datas[1]);
    LcdWriteData('.');

    LcdWriteData('0' + datas[2]); // �¶�С������
    LcdWriteData('0' + datas[3]);
    LcdWriteData('0' + datas[4]);
    LcdWriteData('0' + datas[5]);
    LcdWriteData('C'); // ���϶ȷ���
}




/*******************************************************************************
* �� �� ��         :UsartConfiguration()
* ��������		   :���ô���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void UsartConfiguration()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF3;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF3;
//	ES=1;						//�򿪽����ж�
//	EA=1;						//�����ж�
	TR1=1;					//�򿪼�����
}
