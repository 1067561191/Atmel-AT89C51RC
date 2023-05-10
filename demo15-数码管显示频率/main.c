#include <reg51.h>
#include <stdio.h>
#include "SEG.h"
sbit P1_0 = 0x90;
unsigned char count_count = 0;		// �������������ͳ��
unsigned long frequency = 0;

void inter1 () interrupt 1
{	
	static unsigned int timer_count = 0;
	timer_count++;
	TH0 = 0xfc;		// ���ö�ʱ����λ
	TL0 = 0x18;		// ���ö�ʱ����λ
	if (timer_count % 10 == 2) {	// 10����/���� Ƶ��100Hz
		P1_0 = 0;
	}
	if (timer_count % 10 == 0) {	// 10����/���� Ƶ��100Hz
		P1_0 = 1;
	}
	if (timer_count == 1000) {		// ÿ��
	    timer_count = 0;
		frequency = count_count * 65536 + TH1 * 256 + TL1;
		count_count = 0;	// ͳ�������ü������������
		TH1 = 0;			// ͳ�������ü�������λ
		TL1 = 0;			// ͳ�������ü�������λ
		sprintf(print_char_list,"%08lu",frequency);
		mapping(print_char_list, print_code_list);
	}
}

void inter3 () interrupt 3
{
	count_count++;	// �������+1
}


int main() {
    TMOD = 0x51;	// ���ü�ʱģʽ 01010001
	TH0 = 0xfc;		// ���ø�λ��ʼֵ
	TL0 = 0x18;		// ���õ�λ��ʼֵ
	//TH1 = 0x00;		// ���ø�λ��ʼֵ
	//TL1 = 0x00;		// ���õ�λ��ʼֵ						 
	IE = 0x8a;		// IE�Ĵ��� �ж�����������Ӧ 1000 1010  EA = 1; ET0 = 1;
    TR0 = 1;		// ������ʱ��T0
	TR1 = 1;  		// ����������T1
	while (1) {
		show(print_code_list);
	}
	return 0;
}