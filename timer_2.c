#include<reg51.h>

#define RldTmr(fr) 65536 - (11059200 / 12) / (fr << 1)
#define FuDian(n) (n << 1) / 3
typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned long ULONG;
sbit k2=P3^2;sbit k3=P3^3;

sbit P21=P2^1;
sbit P22=P2^2;
sbit P23=P2^3;
sbit P24=P2^4;
sbit P00=P0^0;
sbit buzz=P3^7;
UCHAR number[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
UCHAR j=0;UCHAR tmp=0;UCHAR cnt=0;UCHAR i=5000;
void delay(UINT k)
{while(k--);}
UINT code noteFreq[] = {    //?? 1-7 ??? 1-7???????
    523, 587, 659, 698, 784, 880, 988,
    1047, 1175, 1319, 1397, 1568, 1760, 1976
};
UINT code tmrRld[] = {      //?? 1-7 ??? 1-7?????????
    RldTmr(523), RldTmr(587), RldTmr(659), RldTmr(698), RldTmr(784), RldTmr(880), RldTmr(988),
    RldTmr(1047), RldTmr(1175), RldTmr(1319), RldTmr(1397), RldTmr(1568), RldTmr(1760), RldTmr(1976),
};
UCHAR code musicNote[] = {      //??
    1, 2, 3, 2,
    3, 2, 3, 5,
    5

};
UCHAR code noteDuration[] = {       //???????,4??4???,8??8???,16??16???
    FuDian(8), FuDian(8), 4, 4,
    4, 4, FuDian(8), 4,
    FuDian(8)

};
bit enable = 1, tmrFlg = 0;
UCHAR T0RH = 0XFF, T0RL = 0X00;
 
void Delay(UINT n);
void PlayMusic(UCHAR speed);
void PlayMusic(UCHAR speed) {
    UCHAR i;
    UCHAR idx;
    UINT cont = 0;
    UINT durationCnt = 0;	//???????????????
    UINT soundCnt = 0;		//???????????????
    for (i = 0; i < sizeof (musicNote); ) {
        while (!tmrFlg) ;
        tmrFlg = 0;
        if (cont == 0) {
            idx = musicNote[i] - 1;
            T0RH = tmrRld[idx] >> 8;
            T0RL = tmrRld[idx];
            durationCnt = (ULONG)240 * (ULONG)noteFreq[idx] / ((ULONG)noteDuration[i] * (ULONG)speed);
            soundCnt = durationCnt - (durationCnt >> 2);	//????????3/4??,?1/4??
            enable = 1;
            cont++;
        }
        else {
            if (cont == durationCnt) {
                cont = 0;
                i++;
            }
            else {
                cont++;
                if (cont == soundCnt) {
                    enable = 0;
                }
            }
        }
    }
}
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
		delay(400000);
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
			PlayMusic(72);
			delay(40000u);
			ET0=0;
		}
    		
	}
}

