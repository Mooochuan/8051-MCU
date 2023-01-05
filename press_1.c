#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit k2=P3^2;sbit k3=P3^3;
sbit P00=P0^0;
uchar cnt=0;uchar a=0;
void delay(uint k)
{while(k--);}

main()
{
	TMOD=0x01;
	TH0=0x3c;
	TL0=0xb0;
	ET0=1;
	EA=1;
	IT0=0;
	EX0=1;
	EX1=1;
	P2=0xfe;
	P00=1;
	while(1)
	{
		if(a==1){
			if(k3==1)
			{
				delay(4000);
				if(k3==1) break;
			}
		}
	}	
}
void In0() interrupt 0
{
	TR0=1;
}	
void In1() interrupt 2
{
	TR0=1;
	a=1;	
}
void Timer0() interrupt 1
{
	TH0=0x3c;
	TL0=0xb0;
	cnt++;
	if(cnt==20)
	{
		cnt=0;
		P00=~P00;	
	}
}
