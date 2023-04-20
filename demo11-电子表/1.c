#include <stdio.h>
#include "SEG.h"

// 定义要显示的数据的初始值
unsigned char second = 50, minute = 59, hour = 23;
// 计时次数默认值   
unsigned char count = 0;

// 定时器T0中断请求
void timer0() interrupt 1
{
    //////////////////////中断基本处理-开始//////////////////////
	count++; // 计数+1
    //TF0 = 0; // 重置计时器溢出状态 CPU响应中断后自动清零 无需软件干预				  
	TH0 = 0x3c; // 重置高位
	TL0 = 0xb0; // 重置低位
	TR0 = 1; // 重置计时器启动状态
    //////////////////////中断基本处理-结束//////////////////////
	//*********************************************************//
	//////////////////////中断业务逻辑-开始//////////////////////
    if (count == 20) { // 当完成20次计数时
		count = 0; // 重置计时次数
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
	//////////////////////中断业务逻辑-结束//////////////////////
}

int main() {
    // 显示的字符列表
    unsigned char print_char_list[8];
    // 显示码列表
    unsigned char print_code_list[8];

    TR0 = 1; // 开启计时器T0
    TMOD = 0x01; // 设置计时模式
	TH0 = 0x3c; // 设置高位初始值
	TL0 = 0xb0;	// 设置低位初始值
	IE = 0x82; // IE寄存器控制 1000 0010  EA = 1; ET0 = 1;
	while (1) {
	    sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second); // 解析显示字符串
	    mapping(print_char_list, print_code_list); // 显示字符到显示码映射
	    show(print_code_list); // 显示
	}
	return 0;
}