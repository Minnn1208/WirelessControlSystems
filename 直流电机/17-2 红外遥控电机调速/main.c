#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"

void main()
{
    unsigned char Command, Speed = 0; // 设置初始速度为0
    unsigned int DutyCycle = 0; // 占空比

    Motor_Init();
    IR_Init();
    while(1)
    {
        if(IR_GetDataFlag())    // 如果接收到数据帧
        {
            Command=IR_GetCommand();        // 获取遥控器指令码
            
            if(Command==IR_1){Speed++; if(Speed > 3) Speed = 3;}    // 按IR_1键时速度加一
            if(Command==IR_2){Speed--; if(Speed < 0) Speed = 0;}    // 按IR_2键时速度减一
            
            if(Speed==0){Motor_SetSpeed(0); DutyCycle = 0;}    // 速度输出
            if(Speed==1){Motor_SetSpeed(50); DutyCycle = 25;} // 占空比为25%
            if(Speed==2){Motor_SetSpeed(75); DutyCycle = 50;} // 占空比为50%
            if(Speed==3){Motor_SetSpeed(100); DutyCycle = 75;} // 占空比为75%
        }
        Nixie(1,DutyCycle/100);    // 数码管显示占空比百位
        Nixie(2,(DutyCycle%100)/10);    // 数码管显示占空比十位
        Nixie(3,DutyCycle%10);    // 数码管显示占空比个位
    }
}

