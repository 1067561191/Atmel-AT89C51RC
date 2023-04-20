#include <reg51.h>
sbit P1_0 = 0x90;
unsigned char second = 56, minute = 57, hour = 8;
unsigned char rate_x = 0;
unsigned char rate_sum = 0;


void inter1 () interrupt 1
{	
	static unsigned char timer_count = 0;
	timer_count++;
	TH0 = 0xfc; // ���ø�λ
	TL0 = 0x17; // ���õ�λ
	if (timer_count == rate_x) {
	    P1_0 = ~P1_0;
	}
	if (timer_count == rate_sum) {
	    P1_0 = ~P1_0;
		timer_count = 0;
	}
}


int main() {
	rate_x = 2;		// ����
	rate_sum = rate_x + 1;
    TMOD = 0x11;	// ���ü�ʱģʽ 00000001
	TH0 = 0xfc;		// ���ø�λ��ʼֵ
	TL0 = 0x17;		// ���õ�λ��ʼֵ
	IE = 0x8f;		// IE�Ĵ������� 1000 0010  EA = 1; ET0 = 1;
    TR0 = 1;		// ������ʱ��ʱ��T0
	while (1) {
	}
	return 0;
}