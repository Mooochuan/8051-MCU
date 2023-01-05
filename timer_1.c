#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit k2=P3^2;sbit k3=P3^3;
sbit P21=P2^1;
sbit P22=P2^2;
sbit P23=P2^3;
sbit P24=P2^4;
sbit P00=P0^0;
sbit buzz=P3^7;
uchar number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar j=0;uchar tmp=0;uchar cnt=0;uchar i=5000;
void delay(uint k)
{while(k--);}
main()
{
	TMOD=0x01;
	TH0=0x3c;
	TL0=0xb0;
	ET0=1;
	IT0=1;
	IT1=1;
	EA=1;
	EX0=1;
	EX1=1;
	while(1)
	{
		switch(j)
		{
			case 0:P21=1;P22=1;P23=1;P24=0;P0=number[tmp%10];delay(1000);j++;break;
			case 1:P21=1;P22=1;P23=0;P24=1;P0=number[tmp/10%10];delay(1000);j++;break;
			case 2:P21=1;P22=0;P23=1;P24=1;P0=number[tmp/100%10];delay(1000);j++;break;
			case 3:P21=0;P22=1;P23=1;P24=1;P0=number[tmp/1000%10];delay(1000);j=0;break;
			default:break;
		}	
	}
}
void In0() interrupt 0
{
		delay(4000);
		if(k2==0)
			tmp++;	
}
void In1() interrupt 2
{
	TR0=1;
}
void Timer0() interrupt 1
{
	TH0=0x3c;
	TL0=0xb0;
	cnt++;
	if(cnt==20)
	{
		cnt=0;
		if(tmp!=0)
		{
		tmp--;
		}
		if(tmp==0)
		{
			buzz=0;
			delay(1000);
			buzz=1;
			ET0=0;
		}
    		
	}
}
	