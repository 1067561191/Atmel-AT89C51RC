#include <stdio.h>
#include "SEG.h"


int main() {
    unsigned char print_char_list[9]; // 显示的字符列表
    unsigned char print_code_list[8]; // 显示码列表
    float temp = 25.6; // 要显示的数据
	unsigned char j; // 循环计数变量
    sprintf(print_char_list,"C    %.1f",temp); // 解析显示字符串
	mapping(print_char_list, print_code_list); // 显示字符到显示码映射
	while (1) {
	    show(print_code_list); // 显示
		for (j = 0x00; j < 0xff; j++); // 防闪
	}
	return 0;
}