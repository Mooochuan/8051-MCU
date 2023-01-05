#include<reg51.h>
sbit P33=P3^3;
sbit P21=P2^1;
sbit P22=P2^2;
sbit P23=P2^3;
sbit P24=P2^4;
unsigned int ms,i=0;
unsigned char j=0;
unsigned char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void delay(unsigned int k)
{while(k--);}
main()
{
TMOD=0x01;
TH0=0;
TL0=0;
ET0=1;
EA=1;
while(P33==1);
TR0=1;
while(P33==0);
TR0=0;
while(1)
{
ms=(i*65536+TH0*256+TL0)/1000;
switch(j)
{
case 0:P21=1;P22=1;P23=1;P24=0;P0=number[ms%10];delay(1000);j++;break;
case 1:P21=1;P22=1;P23=0;P24=1;P0=number[ms/10%10];delay(1000);j++;break;
case 2:P21=1;P22=0;P23=1;P24=1;P0=number[ms/100%10];delay(1000);j++;break;
case 3:P21=0;P22=1;P23=1;P24=1;P0=number[ms/1000%10];delay(1000);j=0;break;
default:break;
}
}
}
void Timer0() interrupt 1
{
i++;
TH0=0;
TL0=0;
}