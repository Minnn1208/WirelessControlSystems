/*√Î±Ì



*/
#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit wela=P2^7;
sbit dula=P2^6;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void init();
void display(uchar fen,miao1,miao2);
void delay(uchar);
uchar tt,fen,miao1,miao2,temp;
void main()
{
init();
while(1)
{ fen=temp/100; //?????????fen,miao1,miao2.??;
miao1=temp%100/10;
miao2=temp%10;
display(fen,miao1,miao2);
if(tt==10) //????????????,??,???????,????10????????,
//???1,??miao2????,????;
{
tt=0;
temp++;
if(temp==200)// ?????????200???;
temp=0;
}
}
}
void display(uchar fen,miao1,miao2)
{
wela=1;
P0=0xfe;
wela=0;
dula=1;
P0=table[fen];
dula=0;
delay(5);
wela=1;
P0=0xfd;
wela=0;
dula=1;
P0=table[miao1];
dula=0;
delay(5);
wela=1;
P0=0xfb;
wela=0;
dula=1;
P0=table[miao2];
dula=0;
delay(5);
}
void delay(uchar z)
{
uchar x,y;
for(x=z;x>0;x--)
for(y=110;y>0;y--);
}
void init()
{
temp=0;
TMOD=0x10;
TH1=(65536-10000)/256;//?????????1?????;
TL1=(65536-10000)%256;//??
EA=1;
ET1=1; //??
TR1=1; //??
}
void timer1() interrupt 3 //?????
{
TH1=(65536-10000)/256;
TL1=(65536-10000)%256;
tt++;
}