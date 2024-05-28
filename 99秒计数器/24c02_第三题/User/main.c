#include<reg52.h>
#include<24c02.h>
//#include<serial_debug.h>

#define EEPROM_ADDRESS	0	//�������ݴ���EEPROM����ʼ��ַ

//�������������
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//�����������ʾ
u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ

u16 s = 0;
u8 mb[2];
u8 sec = 0;


void Timer0Init()
{
	TMOD|=0X01;//ѡ��Ϊ��ʱ��0ģʽ��������ʽ1������TR0��������
	TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
	TL0=0X18;	
	TR0=1;//�򿪶�ʱ��			
}


void DigDisplay()
{
	u8 i;
	for(i=0;i<2;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ	
		}
		P0=smgduan[mb[i]];//���Ͷ���
		delay(1); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}
}


void main()
{	
	Timer0Init();
	while(1)
	{
		sec = at24c02_read_one_byte(EEPROM_ADDRESS);

	  	if(TF0==1)
		{
			TF0=0;
			TH0=0XFC;	//����ʱ������ֵ����ʱ1ms
			TL0=0X18;
			s++;
		}
		if(s==220)		 //����1sʱ�䣬����
		{	
			s = 0;
			sec++;
			if(sec==100) sec=0;	 //��ʱ��99������¿�ʼ
			at24c02_write_one_byte(EEPROM_ADDRESS,sec);
		}
		mb[0]=sec%10;	   //����λ
	    mb[1]=sec/10;	   //���ʮλ
		DigDisplay();
	}
}