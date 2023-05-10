#include <reg51.h>
#include <stdio.h>
#include "SEG.h"
sbit P1_0 = 0x90;
unsigned char count_count = 0;		// 计数器溢出次数统计
unsigned long frequency = 0;

void inter1 () interrupt 1
{	
	static unsigned int timer_count = 0;
	timer_count++;
	TH0 = 0xfc;		// 重置定时器高位
	TL0 = 0x18;		// 重置定时器低位
	if (timer_count % 10 == 2) {	// 10毫秒/周期 频率100Hz
		P1_0 = 0;
	}
	if (timer_count % 10 == 0) {	// 10毫秒/周期 频率100Hz
		P1_0 = 1;
	}
	if (timer_count == 1000) {		// 每秒
	    timer_count = 0;
		frequency = count_count * 65536 + TH1 * 256 + TL1;
		count_count = 0;	// 统计完重置计数器溢出次数
		TH1 = 0;			// 统计完重置计数器高位
		TL1 = 0;			// 统计完重置计数器低位
		sprintf(print_char_list,"%08lu",frequency);
		mapping(print_char_list, print_code_list);
	}
}

void inter3 () interrupt 3
{
	count_count++;	// 溢出次数+1
}


int main() {
    TMOD = 0x51;	// 设置计时模式 01010001
	TH0 = 0xfc;		// 设置高位初始值
	TL0 = 0x18;		// 设置低位初始值
	//TH1 = 0x00;		// 设置高位初始值
	//TL1 = 0x00;		// 设置低位初始值						 
	IE = 0x8a;		// IE寄存器 中断请求允许响应 1000 1010  EA = 1; ET0 = 1;
    TR0 = 1;		// 开启定时器T0
	TR1 = 1;  		// 开启计数器T1
	while (1) {
		show(print_code_list);
	}
	return 0;
}