#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar counter=0;
main()
{
	SCON=0x50;
	TMOD=0x21;
	TH1=0xf3;
	TL1=0xf3;
	TH0=0x3c;
	TL0=0xb0;
	ES=1;
	EA=1;
	TR1=1;
	while(RI==0);
	RI=0;
	SBUF=SBUF+1;
	while(TI==0);
	TI=0;
	while(1);
}
void serial() interrupt 4
{
	if(RI==1)
	{
		RI=0;
		SBUF=SBUF+1;
	}
	if(TI==1)
		TI=0;
}
void timer0() interrupt 1
{
	TH0=0x3c;
	TL0=0xb0;
	counter++;
	if(counter==20)
	{
		SBUF=1;
		counter=0;	
	}
}