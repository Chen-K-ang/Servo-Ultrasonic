#include "SERVO.h"

// _nop_()��ʱһ����������
#include <reg52.h>
#include <intrins.h>

/*���pwmʹ�ö�ʱ����ʼ��*/
void SERVO_time1_init(void)//100΢��@12.000MHz
{
	TMOD &= 0x0F; //���ö�ʱ��ģʽ
	TMOD |= 0x10; //���ö�ʱ��ģʽ
	TL1 = 0x9C;   //���ö�ʱ��ֵ
	TH1 = 0xFF;   //���ö�ʱ��ֵ
	TF1 = 0;      //���TF1��־
	ET1 = 1;      //�򿪶�ʱ��1�ж�     
	EA = 1;       //�����ж�
	TR1 = 1;      //��ʱ��1��ʼ��ʱ
}

unsigned char servo_pwm_val = 0;
/*T1�ж�*/
void SERVO_pwm_ISR(void) interrupt 3
{
	static unsigned char count = 0;
	TR1 = 0; 
	TH1 = 0xFF; // 0.1ms
	TL1 = 0x9C;
	
	if (count <= servo_pwm_val) //5==0�� 15==90��
		SERVO_IO = 1;
	else
		SERVO_IO = 0;
	
	count++;
	if (count >= 200) //T = 20ms����
		count = 0;
	
	TR1 = 1; //����T0
}

