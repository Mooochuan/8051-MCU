#include<reg51.h>
unsigned char counter=0;
sbit p21=P2^1;
unsigned char number[]={0xf9,0x90,0x90,0xb0,0xb0,0xf9,0x99,0xf9,0xf8,0xc0,0xa4};
unsigned char i=0;
main()
{
	TMOD=0X10;
	TH1=0X3C;
	TL1=0xb0;
	ET1=1;
	EA=1;
	TF1=0;
	TR1=1;
	p21=0;
	while(1);
}
void Timer1() interrupt 3 using 0
{
      TH1=0X3c;
			TL1=0XB0;
			counter++;
			if(counter==20)
			{
				P0=number[i++];
				if(i>10)
				{i=0;}
				counter=0;
			}
			}
	
	