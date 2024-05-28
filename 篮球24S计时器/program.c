 #include<reg51.h>	

sbit DUANX = P2^6;		//段选信号的锁存器控制	
sbit WEIX = P2^7;		//位选信号的锁存器控制	
sbit A = P2^4;
sbit B1 = P2^3;
sbit C = P2^2; // 数码管显示的位置

#define uchar unsigned char  //宏定义（预处理指令，不是语句，后面不用加分号）
#define uint unsigned int	  //宏定义（用法和上面类似）

/*unsigned char code table[]={  //数码管各位的码表
0xfe,0xfd,0xfb,0xf7,
0xef,0xdf,0xbf,0x7f};*/

unsigned char code table2[]={  //数码管显示的码表
0x3f,0x06,0x5b,0x4f,0x66,
0x6d,0x7d,0x07,0x7f,0x6f};

void delay(uint z)  //延时函数
{
	unsigned int x,y;
	for(x = z; x > 0; x--){
		for(y=3000;y>0;y--);
	}		
}

void main(){
	//uchar nums,nums2;
	uint time;
	while(1){
		for(time = 24; ;time--){   
			//第一位数（十位数）
			A = 1;
			B1 = 1;
			C = 1;
			P0 = table2[time / 10];
			P0 = 0;
			delay(1000);
			//第二位数（个位数）
			A = 1;
			B1 = 1;
			C = 0;
			P0 = table2[time % 10];
			P0 = 0;
			delay(1000);
			if(time / 10 < 0){
				time = 24;
			}
		}
		
		
		
		
		
		/*WEIX = 1;		 //打开位选锁存器
		P0=table[nums];	 //送入位选信号，调用数组
		WEIX = 0;		 //关闭位选锁存器
		for(nums2 = 9;nums2 >=0;nums2--)
		{
			DUANX = 1;		     //打开段选锁存器
			P0=table2[nums2];	 //送入段选信号，显示数字1的代码
			DUANX = 0;		     //关闭段选锁存器
			delay(1000);	     //调用延时函数	
		}*/
		
	}

}