#include<reg51.h>
#define uchar unsigned char
sbit P00=P0^0;
uchar count=0;

main()
{
	TMOD=0x01;
	TH0=0x3c;
	TL0=0xb0;
	ET0=1;
	EA=1;
	P2=0xfe;
	TR0=1;
	P00=1;
	while(1);		
}
void timer0() interrupt 1
{
	TH0=0x3c;
	TL0=0xb0;
	count++;
	if(count==2)
	{
		count=0;
		P00=~P00;
	}	
}

	