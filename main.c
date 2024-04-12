#include <reg52.h>
#include "HC_SR04.h" //������
#include "delay.h"
#include "SERVO.h"   //���

#define SERVO_LIMIT 30 //30cm�ڶ��ת��
void main()
{
	int distance = 0;
	SR04_init();
	SERVO_time1_init();
	servo_pwm_val = 5;
	while (1) {
		//��ȡ����ֵ
		distance = SR04_get_distance();
		
		//��ȡ��������ֵ����ʵ����0
		if (distance < 0) 
			distance = 0;
		if (distance < SERVO_LIMIT) {
			servo_pwm_val = 25;    //ת��180�㣬���忴"SERVO.h"
		}
		delay_ms(200);

		delay_ms(1000);
		servo_pwm_val = 25;
		delay_ms(1000);
		servo_pwm_val = 5;
	}
}
