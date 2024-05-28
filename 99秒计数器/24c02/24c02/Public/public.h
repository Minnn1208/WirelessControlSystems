#ifndef _public_H
#define _public_H

#include "reg52.h"

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;


void delay_10us(u16 ten_us);
void delay_ms(u16 ms);
void delay(u16 i);

#endif
