#ifndef _display_H
#define _display_H

#include "public.h"


#define SMG_A_DP_PORT	P0	//ʹ�ú궨������ܶ����

//���������λѡ�źſ��ƽ�
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

void Timer0Init();
void DigDisplay();

#endif
