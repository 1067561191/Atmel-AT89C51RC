#include <stdio.h>
#include "SEG.h"


unsigned char second = 56, minute = 57, hour = 8;



/**
 * 依次检测各时间单位阈值
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
 * 外部中断0中断方法
 */
void inter0() interrupt 0
{
	hour++;
	range_time();
	sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
}

/**
 * 定时器T0中断方法
 */
void inter1() interrupt 1
{
    static unsigned char timer_count = 0;
    //////////////////////中断基本处理-开始//////////////////////
	timer_count++; // 计数+1				  
	TH0 = 0x3c; // 重置高位
	TL0 = 0xb0; // 重置低位
    //////////////////////中断基本处理-结束//////////////////////
	//*********************************************************//
	//////////////////////中断业务逻辑-开始//////////////////////
    if (timer_count == 20) { // 显示时间 +秒
	    timer_count = 0;
		second++;
		range_time();
		sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
	}
	mapping(print_char_list, print_code_list);
	//////////////////////中断业务逻辑-结束//////////////////////
}
/**
 * 外部中断1中断方法
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
    TMOD = 0x01; // 设置计时模式
	TH0 = 0x3c; // 设置高位初始值
	TL0 = 0xb0;	// 设置低位初始值
	IE = 0x87; // IE寄存器控制 1000 0111  EA = 1; EX1 = 1; ET0 = 1; EX0 = 1;
    TR0 = 1; // 开启计时器T0
	IT0 = 1; // 开启外部中断0下沿 P3.2
	IT1 = 1; // 开启外部中断1下沿 P3.3
	while (1) {
	    show(print_code_list); // 显示
	}
	return 0;
}