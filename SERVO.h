#ifndef HARDWARE_SERVO_H
#define HARDWARE_SERVO_H

#include <reg52.h>

sbit SERVO_IO = P3^7;  //设定PWM输出的I/O端口
/*
对于180°舵机
t = 0.5ms——————-舵机会转动 0 ° 
t = 1.0ms——————-舵机会转动 45°
t = 1.5ms——————-舵机会转动 90°
t = 2.0ms——————-舵机会转动 135°
t = 2.5ms——————-舵机会转动180
*/

extern unsigned char servo_pwm_val;

void SERVO_time1_init(void);

#endif
