 #include<reg51.h>	

sbit DUANX = P2^6;		//��ѡ�źŵ�����������	
sbit WEIX = P2^7;		//λѡ�źŵ�����������	
sbit A = P2^4;
sbit B1 = P2^3;
sbit C = P2^2; // �������ʾ��λ��

#define uchar unsigned char  //�궨�壨Ԥ����ָ�������䣬���治�üӷֺţ�
#define uint unsigned int	  //�궨�壨�÷����������ƣ�

/*unsigned char code table[]={  //����ܸ�λ�����
0xfe,0xfd,0xfb,0xf7,
0xef,0xdf,0xbf,0x7f};*/

unsigned char code table2[]={  //�������ʾ�����
0x3f,0x06,0x5b,0x4f,0x66,
0x6d,0x7d,0x07,0x7f,0x6f};

void delay(uint z)  //��ʱ����
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
			//��һλ����ʮλ����
			A = 1;
			B1 = 1;
			C = 1;
			P0 = table2[time / 10];
			P0 = 0;
			delay(1000);
			//�ڶ�λ������λ����
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
		
		
		
		
		
		/*WEIX = 1;		 //��λѡ������
		P0=table[nums];	 //����λѡ�źţ���������
		WEIX = 0;		 //�ر�λѡ������
		for(nums2 = 9;nums2 >=0;nums2--)
		{
			DUANX = 1;		     //�򿪶�ѡ������
			P0=table2[nums2];	 //�����ѡ�źţ���ʾ����1�Ĵ���
			DUANX = 0;		     //�رն�ѡ������
			delay(1000);	     //������ʱ����	
		}*/
		
	}

}