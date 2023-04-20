#include <stdio.h>
#include "SEG.h"

// ����Ҫ��ʾ�����ݵĳ�ʼֵ
unsigned char second = 50, minute = 59, hour = 23;
// ��ʱ����Ĭ��ֵ   
unsigned char count = 0;

// ��ʱ��T0�ж�����
void timer0() interrupt 1
{
    //////////////////////�жϻ�������-��ʼ//////////////////////
	count++; // ����+1
    //TF0 = 0; // ���ü�ʱ�����״̬ CPU��Ӧ�жϺ��Զ����� ���������Ԥ				  
	TH0 = 0x3c; // ���ø�λ
	TL0 = 0xb0; // ���õ�λ
	TR0 = 1; // ���ü�ʱ������״̬
    //////////////////////�жϻ�������-����//////////////////////
	//*********************************************************//
	//////////////////////�ж�ҵ���߼�-��ʼ//////////////////////
    if (count == 20) { // �����20�μ���ʱ
		count = 0; // ���ü�ʱ����
		second++;
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
	//////////////////////�ж�ҵ���߼�-����//////////////////////
}

int main() {
    // ��ʾ���ַ��б�
    unsigned char print_char_list[8];
    // ��ʾ���б�
    unsigned char print_code_list[8];

    TR0 = 1; // ������ʱ��T0
    TMOD = 0x01; // ���ü�ʱģʽ
	TH0 = 0x3c; // ���ø�λ��ʼֵ
	TL0 = 0xb0;	// ���õ�λ��ʼֵ
	IE = 0x82; // IE�Ĵ������� 1000 0010  EA = 1; ET0 = 1;
	while (1) {
	    sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second); // ������ʾ�ַ���
	    mapping(print_char_list, print_code_list); // ��ʾ�ַ�����ʾ��ӳ��
	    show(print_code_list); // ��ʾ
	}
	return 0;
}