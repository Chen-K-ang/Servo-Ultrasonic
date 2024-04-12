#ifndef HARDWARE_HC_SR04_H
#define HARDWARE_HC_SR04_H

#include <reg52.h>
#include <intrins.h>

sbit SR04_TRIG = P1^7;
sbit SR04_ECHO = P3^2;

void SR04_init(void);
int SR04_get_distance(void);

#endif
