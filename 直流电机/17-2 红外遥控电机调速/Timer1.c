#include <REGX52.H>

/**
  * @brief  ¶¨Ê±Æ÷³õÊ¼»¯£¬100us@12.000MHz
  * @param  ÎÞ
  * @retval ÎÞ
  */
void Timer1_Init(void)
{
	TMOD &= 0x0F;		//ÉèÖÃ¶¨Ê±Æ÷Ä£Ê½
	TMOD |= 0x10;		//ÉèÖÃ¶¨Ê±Æ÷Ä£Ê½
	TL1 = 0x9C;		//ÉèÖÃ¶¨Ê±³õÖµ
	TH1 = 0xFF;		//ÉèÖÃ¶¨Ê±³õÖµ
	TF1 = 0;		//Çå³ýTF1±êÖ¾
	TR1 = 1;		//¶¨Ê±Æ÷¿ªÊ¼¼ÆÊ±
	ET1=1;
	EA=1;
	PT1=0;
}


/*å®šæ—¶å™¨ä¸­æ–­å‡½æ•°æ¨¡æ¿
void Timer1_Routine() interrupt 3
{
	static unsigned int T1Count;
	TL1 = 0x9C;		//è®¾ç½®å®šæ—¶åˆå€¼
	TH1 = 0xFF;		//è®¾ç½®å®šæ—¶åˆå€¼
	T1Count++;
	if(T1Count>=1000)
	{
		T1Count=0;
		
	}
}
*/
