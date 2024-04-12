#include <reg52.h>
#include "HC_SR04.h" //超声波
#include "delay.h"
#include "SERVO.h"   //舵机

#define SERVO_LIMIT 30 //30cm内舵机转动
void main()
{
	int distance = 0;
	SR04_init();
	SERVO_time1_init();
	servo_pwm_val = 5;
	while (1) {
		//读取距离值
		distance = SR04_get_distance();
		
		//读取报错，距离值不真实，置0
		if (distance < 0) 
			distance = 0;
		if (distance < SERVO_LIMIT) {
			servo_pwm_val = 25;    //转到180°，具体看"SERVO.h"
		}
		delay_ms(200);

		delay_ms(1000);
		servo_pwm_val = 25;
		delay_ms(1000);
		servo_pwm_val = 5;
	}
}
