#include <stdio.h>
#include "SEG.h"


unsigned char second = 56, minute = 57, hour = 8;



/**
 * ���μ���ʱ�䵥λ��ֵ
 */
void range_time() {
    if (second == 60) {
		second = 0;
        minute++;
	}
    if (minute == 60) {
		minute = 0;
		hour++;
	}
	if (hour == 24) {
		hour = 0;
	}
}

/**
 * �ⲿ�ж�0�жϷ���
 */
void inter0() interrupt 0
{
	hour++;
	range_time();
	sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
}

/**
 * ��ʱ��T0�жϷ���
 */
void inter1() interrupt 1
{
    static unsigned char timer_count = 0;
    //////////////////////�жϻ�������-��ʼ//////////////////////
	timer_count++; // ����+1				  
	TH0 = 0x3c; // ���ø�λ
	TL0 = 0xb0; // ���õ�λ
    //////////////////////�жϻ�������-����//////////////////////
	//*********************************************************//
	//////////////////////�ж�ҵ���߼�-��ʼ//////////////////////
    if (timer_count == 20) { // ��ʾʱ�� +��
	    timer_count = 0;
		second++;
		range_time();
		sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
	}
	mapping(print_char_list, print_code_list);
	//////////////////////�ж�ҵ���߼�-����//////////////////////
}
/**
 * �ⲿ�ж�1�жϷ���
 */
void inter2() interrupt 2
{
	minute++;
	range_time();
	sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
}

int main() {
	sprintf(print_char_list,"3----075");
	mapping(print_char_list, print_code_list);
    TMOD = 0x01; // ���ü�ʱģʽ
	TH0 = 0x3c; // ���ø�λ��ʼֵ
	TL0 = 0xb0;	// ���õ�λ��ʼֵ
	IE = 0x87; // IE�Ĵ������� 1000 0111  EA = 1; EX1 = 1; ET0 = 1; EX0 = 1;
    TR0 = 1; // ������ʱ��T0
	IT0 = 1; // �����ⲿ�ж�0���� P3.2
	IT1 = 1; // �����ⲿ�ж�1���� P3.3
	while (1) {
	    show(print_code_list); // ��ʾ
	}
	return 0;
}