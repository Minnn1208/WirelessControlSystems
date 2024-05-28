#include "iic.h"

void iic_start(void)
{
	IIC_SDA=1;
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SDA=0;	
	delay_10us(1);
	IIC_SCL=0;
	delay_10us(1);
}


void iic_stop(void)
{	
	IIC_SDA=0;
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SDA=1;	
	delay_10us(1);			
}


void iic_ack(void)
{
	IIC_SCL=0;
	IIC_SDA=0;	//SDAΪ�͵�ƽ
	delay_10us(1);
   	IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;
}


void iic_nack(void)
{
	IIC_SCL=0;
	IIC_SDA=1;	//SDAΪ�ߵ�ƽ
	delay_10us(1);
   	IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;	
}


u8 iic_wait_ack(void)
{
	u8 time_temp=0;
	
	IIC_SCL=1;
	delay_10us(1);
	while(IIC_SDA)	//�ȴ�SDAΪ�͵�ƽ
	{
		time_temp++;
		if(time_temp>100)//��ʱ��ǿ�ƽ���IICͨ��
		{	
			iic_stop();
			return 1;	
		}			
	}
	IIC_SCL=0;
	return 0;	
}


void iic_write_byte(u8 dat)
{                        
    u8 i=0; 
	   	    
    IIC_SCL=0;
    for(i=0;i<8;i++)	//ѭ��8�ν�һ���ֽڴ������ȴ����ٴ���λ
    {              
        if((dat&0x80)>0) 
			IIC_SDA=1;
		else
			IIC_SDA=0;
        dat<<=1; 	  
		delay_10us(1);  
		IIC_SCL=1;
		delay_10us(1); 
		IIC_SCL=0;	
		delay_10us(1);
    }	 
}

u8 iic_read_byte(u8 ack)
{
	u8 i=0,receive=0;
   	
    for(i=0;i<8;i++ )	//ѭ��8�ν�һ���ֽڶ������ȶ����ٴ���λ
	{
        IIC_SCL=0; 
        delay_10us(1);
		IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA)receive++;   
		delay_10us(1); 
    }					 
    if (!ack)
        iic_nack();
    else
        iic_ack();  
		  
    return receive;
}
