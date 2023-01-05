#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit buzz=P3^7;
uchar counter=0;
uint i=0;
unsigned char number[]={0xf9,0x90,0x90,0xb0,0xb0,0xf9,0x99,0xf9,0xf8,0xc0,0xa4};
void delay(uint k)
{while(k--);}
main()
{
	TMOD=0x21;
	SCON=0x50;
	TH0=0x3c;
	TL0=0xb0;
	TH1=0xf3;
	TL1=0xf3;
	TR1=1;
	ET0=1;
	EA=1;
	EX0=1;
	IT0=1;
	TR0=1;
	while(1);
}
void timer0() interrupt 1
{
	TH0=0x3c;
	TL0=0xb0;
	counter++;
	if(counter==20)
	{
		SBUF=number[i];
		i++;
		if(i>10)
		{
			i=0;
		}
		counter=0;	
	}
}	
void in0() interrupt 0
{
	buzz=0;
			delay(10000);
			buzz=1;
			ET0=0;
}
void serial() interrupt 4
{
	if(TI==1)
		TI=0;
}
/*#include <reg51.h> 
sbit k2=P3^2;
sbit buzz=P3^7;
int num=0,i=0;
char ch;
delay(int j)
{
	while(j--);
}
main()
{
	TMOD=0x21;
	SCON=0x50;
  PCON=0x00;	
	TH1=256-1000000/32/2400; 	   	
	TL1=256-1000000/32/2400;	
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	IE=0x92;
	TR1=1;		     	
  TR0=1;		 	
	EA=1;	
	while(k2==1)
	{
		if(num==20)
		{
			num=0;
			SBUF=ch;
			if(i==15)
				i=-1;
			i++;
		}
	}
	buzz=0;
	delay(400000);
	buzz=1;
	while(1);
}
void serial() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
}*/
