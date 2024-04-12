#include "HC_SR04.h"

static void SR04_timer0_init(void) //@12.000MHz
{
	TMOD &= 0xF0; //���ö�ʱ��ģʽ
	TMOD |= 0x09; //��ʽ1 gate��1 P3.2 INT0��
	TL0 = 0;      //���ö�ʱ��ֵ
	TH0 = 0;      //���ö�ʱ��ֵ
	TF0 = 0;      //���TF0��־
	TR0 = 1;      //��ʱ��0��P3.2�øߵ�ƽ��ʼ��ʱ
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
	
	//��ȡ��ʱ������ֵ
	timeH = TH0;
	timeL = TL0;
	TH0 = 0;
	TL0 = 0;
	
	time = timeH * 256 + timeL;
	//���������˳��������۲��ֵ
	if (time > 18000)
		return -3;
	
	//����340m/s / 2 ==> 17000cm/s
	distance = time * 1.7 / 100;
	
	return (distance);
}


