#include<reg51.h>
sbit P33=P3^3;
unsigned int s,i=0;

main()
{
	TMOD=0x29;
	SCON=0x50;
	TH1=0xf3;
	TL1=0xf3;
	TR1=1;
	TH0=0;
	TL0=0;
	ET0=1;
	EA=1;
	while(1){
	while(P33==1);
	TR0=1;
	while(P33==0);
	while(P33==1);
	TR0=0;
	s=(i*65536+TH0*256+TL0)/1000000;
	SBUF=s;}
	while(1)
		{
		if(TI==1)
			TI=0;
    }
}
void Timer1() interrupt 1
{
	i++;
	TH0=0;
	TL0=0;
}
/*=number[ms%10]number[ms/10%10]number[ms/100%10]number[ms/1000%10];delay(1000);j=0;break;*/
