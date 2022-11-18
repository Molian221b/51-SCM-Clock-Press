#include <REGX52.H>
#include "LCD1602.h"	
#include "Delayms.h"
#include "MatrixKey.h"
#include "Timer0.h"
#define uchar unsigned char
void press();
sbit key = P3^1;//S3键
uchar hour = 2;
uchar min = 35;
uchar sec = 50;

void main(){
	LCD_Init();
	LCD_ShowString(1,1,"Clock");
	LCD_ShowString(2,1,"  :  :");
	Timer0Init();
	delayms(1000);
	while(1){
		press();
		LCD_ShowNum(2,1,hour,2);
		LCD_ShowNum(2,4,min,2);
		LCD_ShowNum(2,7,sec,2);
	}
}
void press(){
	if(key==0){delayms(10);
	while(key==0);
	delayms(10);
	min+=1;
	if(min>=60){min=0;hour+=1;if(hour>=24){hour=0;}}
	}
}
void Timer0_Routine() interrupt 1{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	T0Count++;
	if(T0Count>=1000){
		T0Count = 0;
		sec++;
		if(sec>=60){
			sec=0;
			min++;
			if(min>=60){
				min=0;
				hour++;
				if(hour>=24){
					hour=0;
				}
			}
		}
	}
}
