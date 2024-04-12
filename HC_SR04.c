#include "HC_SR04.h"

static void SR04_timer0_init(void) //@12.000MHz
{
	TMOD &= 0xF0; //设置定时器模式
	TMOD |= 0x09; //方式1 gate置1 P3.2 INT0脚
	TL0 = 0;      //设置定时初值
	TH0 = 0;      //设置定时初值
	TF0 = 0;      //清除TF0标志
	TR0 = 1;      //定时器0由P3.2置高电平开始计时
}

void SR04_init(void)
{
	SR04_timer0_init();
	SR04_TRIG = 0;
	SR04_ECHO = 0;
}

int SR04_get_distance(void)
{
	unsigned char i;
	unsigned char timeH, timeL;
	unsigned int time;
	unsigned int distance;
	unsigned int t;
	
	SR04_TRIG = 1;
	for (i = 0; i < 10; i++) {
		_nop_();
	}
	SR04_TRIG = 0;
	SR04_ECHO = 1;
	
	t = 0;
	while (!SR04_ECHO) {
		t++;
		_nop_();
		if (t > 30000) {
			return -1;	
		}
	}
	t = 0;
	while (SR04_ECHO) {
		t++;
		_nop_();
		if (t > 30000) {
			return -2;	
		}
	}
	
	//读取定时器计数值
	timeH = TH0;
	timeL = TL0;
	TH0 = 0;
	TL0 = 0;
	
	time = timeH * 256 + timeL;
	//计数超过了超声波理论测距值
	if (time > 18000)
		return -3;
	
	//距离340m/s / 2 ==> 17000cm/s
	distance = time * 1.7 / 100;
	
	return (distance);
}


