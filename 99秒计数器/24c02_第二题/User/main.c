#include<reg52.h>
#include<24c02.h>
#include<serial_debug.h>

sbit K1=P3^1;
sbit K2=P3^0;

void main()
{ 
  UartInit();
	while(1)
	{
		at24c02_write_one_byte(10,20);
		printf("%bd \r\n",at24c02_read_one_byte(10));	
		while(1){
			if(K1 == 0){
				iic_stop();
				if(K2 == 0){
					break;
				}
			break;
			}
		} break;
	}
	
	
	
	
	
	
}