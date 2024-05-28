#include <REGX52.H>

/**
  * @brief  ��ʱ����ʼ����100us@12.000MHz
  * @param  ��
  * @retval ��
  */
void Timer1_Init(void)
{
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x9C;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ����ʼ��ʱ
	ET1=1;
	EA=1;
	PT1=0;
}


/*定时器中断函数模板
void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	TL1 = 0x9C;		//设置定时初值
	TH1 = 0xFF;		//设置定时初值
	T1Count++;
	if(T1Count>=1000)
	{
		T1Count=0;
		
	}
}
*/
