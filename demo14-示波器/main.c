#include <reg51.h>
sbit P1_0 = 0x90;
unsigned char second = 56, minute = 57, hour = 8;
unsigned char rate_x = 0;
unsigned char rate_sum = 0;


void inter1 () interrupt 1
{	
	static unsigned char timer_count = 0;
	timer_count++;
	TH0 = 0xfc; // 重置高位
	TL0 = 0x17; // 重置低位
	if (timer_count == rate_x) {
	    P1_0 = ~P1_0;
	}
	if (timer_count == rate_sum) {
	    P1_0 = ~P1_0;
		timer_count = 0;
	}
}


int main() {
	rate_x = 2;		// 比例
	rate_sum = rate_x + 1;
    TMOD = 0x11;	// 设置计时模式 00000001
	TH0 = 0xfc;		// 设置高位初始值
	TL0 = 0x17;		// 设置低位初始值
	IE = 0x8f;		// IE寄存器控制 1000 0010  EA = 1; ET0 = 1;
    TR0 = 1;		// 开启定时计时器T0
	while (1) {
	}
	return 0;
}