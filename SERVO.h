#ifndef HARDWARE_SERVO_H
#define HARDWARE_SERVO_H

#include <reg52.h>

sbit SERVO_IO = P3^7;  //�趨PWM�����I/O�˿�
/*
����180����
t = 0.5ms������������-�����ת�� 0 �� 
t = 1.0ms������������-�����ת�� 45��
t = 1.5ms������������-�����ת�� 90��
t = 2.0ms������������-�����ת�� 135��
t = 2.5ms������������-�����ת��180
*/

extern unsigned char servo_pwm_val;

void SERVO_time1_init(void);

#endif
