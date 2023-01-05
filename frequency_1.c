#include<reg51.h>
sbit k4=P3^4;
sbit P21=P2^1;
sbit P22=P2^2;
sbit P23=P2^3;
sbit P24=P2^4;
unsigned int counter=0;unsigned char j=0;
unsigned int H;unsigned int L;unsigned int tmp;
void delay(unsigned int k)
{while(k--);}
unsigned char number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
main()
{
	TMOD=0x15;
	TH1=0x3c;
	TL1=0xb0;
	TH0=0x00;
	TL0=0x00;
	ET1=1;
	EA=1;
	TF1=0;
	k4=1;
	while(k4==0);
	while(k4==1);
	TR1=1;
	TR0=1;
	for(counter=0;counter<20;counter++)
	{
		while(TF1==0);
		TH1=0x3c;
	  TL1=0xb0;
		TF1=0;
	}
	TR0=0;
	TR1=0;
	H=TH0;
		L=TL0;
		while(1)
		{
			tmp=H*256+L;
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
	