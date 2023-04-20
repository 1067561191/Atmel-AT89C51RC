#include <stdio.h>
#include "SEG.h"

unsigned char old = 0xfe, now = 0xfe;
unsigned char step = 0;
unsigned char flow_count = 0;
unsigned char second = 56, minute = 57, hour = 8, day = 20, month = 4;
unsigned int year = 2023; // int类型必须最后定义


/**
 * 根据当前年月返回当前月最大天数
 */
unsigned char month_days() {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) { // 大月
	    return 31;
	}
    if (month == 4 || month == 6 || month == 9 || month == 11) { // 小月
	    return 30;
	}
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) { // 闰年
	    return 29;
    } else {
	    return 28;
	}
	
}

/**
 * 依次检测各时间单位阈值
 */
void range_time() {
    if (second == 60) {
		second = 0;
		flow_count = 16;
        minute++;
	}
    if (minute == 60) {
		minute = 0;
		hour++;
	}
	if (hour == 24) {
		hour = 0;
		day++;
	}
	if ((month_days() + 1) == day) {
		day = 1;
		month++;
	}
	if (month == 13) {
		month = 1;
		year++;
	}
}

void key_change_up() {
    P3 = 0xfe;
	now = P3;
    if (old != now && now == 0xfe) { // 发生上沿跳变
		if (old == 0xbe) { // S1
		    step++;
	        TR0 = 0; // 暂停计时器
			if (step == 1) {
				sprintf(print_char_list,"51    %02d",(int)hour);
			}
			if (step == 2) {
				sprintf(print_char_list,"52    %02d",(int)minute);
			}
		    if (step == 3) {
			    step = 0;
				sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
			    TR0 = 1; // 重启计时器
			} 
		} 
		if (old == 0xde && step == 1) { // S2
			hour++;
			range_time();
			sprintf(print_char_list,"51    %02d",(int)hour);
		}
		if (old == 0xde && step == 2) { // S2
			minute++;
			range_time();
			sprintf(print_char_list,"52    %02d",(int)minute);
		} 
		if (old == 0xee && step == 1) { // S3
			hour = hour == 0 ? 0 : hour - 1;
			sprintf(print_char_list,"51    %02d",(int)hour);
		}
		if (old == 0xee && step == 2) { // S3
			minute = minute == 0 ? 0 : minute - 1;
			sprintf(print_char_list,"52    %02d",(int)minute);
	    }
		mapping(print_char_list, print_code_list);
	}
	old = now;
}

/**
 * 定时器T0中断方法
 */
void timer0() interrupt 1
{
    static unsigned char timer_count = 0;
    //////////////////////中断基本处理-开始//////////////////////
	timer_count++; // 计数+1				  
	TH0 = 0x3c; // 重置高位
	TL0 = 0xb0; // 重置低位
    //////////////////////中断基本处理-结束//////////////////////
	//*********************************************************//
	//////////////////////中断业务逻辑-开始//////////////////////
	if (flow_count == 0 && P1 != 0xff && timer_count % 4 == 0) {
	    P1 = 0xff;
	}
	if (flow_count > 0 && timer_count % 4 == 0) {
	    P1 = _crol_(0xfe,16 - flow_count--);
	}
    if (timer_count == 20 || timer_count == 40 || timer_count == 60) { // 显示时间 0-3秒
		second++;
		range_time();
		sprintf(print_char_list,"%02d-%02d-%02d",(int)hour,(int)minute,(int)second);
	}
	if (timer_count == 80 || timer_count == 100 || timer_count == 120) { // 显示日期 3-6秒
	    second++;
		range_time();
	    sprintf(print_char_list,"%04d%02d%02d",year,(int)month,(int)day);
	}
	if (timer_count == 120) {
	    timer_count = 0;
	}
	mapping(print_char_list, print_code_list);
	//////////////////////中断业务逻辑-结束//////////////////////
}

int main() {
	sprintf(print_char_list,"3----075");
	mapping(print_char_list, print_code_list);
    TMOD = 0x01; // 设置计时模式
	TH0 = 0x3c; // 设置高位初始值
	TL0 = 0xb0;	// 设置低位初始值
	IE = 0x82; // IE寄存器控制 1000 0010  EA = 1; ET0 = 1;
    TR0 = 1; // 开启计时器T0
	while (1) {
		key_change_up();
	    show(print_code_list); // 显示
	}
	return 0;
}