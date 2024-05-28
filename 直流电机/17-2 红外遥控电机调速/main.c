#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

void main()
{
    unsigned char Command, Speed = 0; // ���ó�ʼ�ٶ�Ϊ0
    unsigned int DutyCycle = 0; // ռ�ձ�

    Motor_Init();
    IR_Init();
    while(1)
    {
        if(IR_GetDataFlag())    // ������յ�����֡
        {
            Command=IR_GetCommand();        // ��ȡң����ָ����
            
            if(Command==IR_1){Speed++; if(Speed > 3) Speed = 3;}    // ��IR_1��ʱ�ٶȼ�һ
            if(Command==IR_2){Speed--; if(Speed < 0) Speed = 0;}    // ��IR_2��ʱ�ٶȼ�һ
            
            if(Speed==0){Motor_SetSpeed(0); DutyCycle = 0;}    // �ٶ����
            if(Speed==1){Motor_SetSpeed(50); DutyCycle = 25;} // ռ�ձ�Ϊ25%
            if(Speed==2){Motor_SetSpeed(75); DutyCycle = 50;} // ռ�ձ�Ϊ50%
            if(Speed==3){Motor_SetSpeed(100); DutyCycle = 75;} // ռ�ձ�Ϊ75%
        }
        Nixie(1,DutyCycle/100);    // �������ʾռ�ձȰ�λ
        Nixie(2,(DutyCycle%100)/10);    // �������ʾռ�ձ�ʮλ
        Nixie(3,DutyCycle%10);    // �������ʾռ�ձȸ�λ
    }
}

