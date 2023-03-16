#include <reg51.h>
#include <intrins.h>

unsigned char KeyScan() {
	unsigned char i;
	unsigned char a = 0xfe;			// 1111 1110 
	for (i = 0; i < 4; i++) {		// 按行检测 先检测S0-S3 第一行
		P3 = a;
		if (P3 != a) {  			// 检测到了
			return P3;
		};
		a = _crol_(a, 1);			// 再检测S4-S7 第二行 再检测S8-S11 第三行 再检测S12-S15 第四行
	}
	return 0xff;  					// 默认返回全部高电平
}

int main() {
	unsigned int i;
	unsigned char mode = 0x00;		// 默认关灯状态
	unsigned char x = 0x7f; 		// 初始值 0111 1111
	unsigned char y = 0xfe;			//        1111 1110
	while(1) {
		switch(KeyScan()) {
			case 0x7e: {			// S0被按下
				mode = 0x01;		// 右流水灯模式
				break;				// 退出switch
			}
			case 0xbd: {			// S5被按下
				mode = 0x02;		// 左流水灯模式
				break;				// 退出switch
			}
			case 0xdb: {			// S10被按下
				mode = 0x03;		// 双向流水灯模式
				break;				// 退出switch
			}
			case 0xe7: {			// S15被按下
				mode = 0x00;		// 关灯模式
				break;				// 退出switch
			}
			default : {
				break;
			}
		}
		if(mode == 0x00) {
			P1 = 0xff;
			continue;
		}
		if(mode == 0x01) {
			P1 = x;			  				// 点亮
			x = _cror_(x, 1); 				// 循环右移
			y = _crol_(y, 1); 				// 同步左移
			for(i = 0; i < 500*12000; i++);	// 等待500ms
			continue;
		}
		if(mode == 0x02) {
			y = _cror_(y, 1); 				// 同步右移	  
			x = _crol_(x ,1); 				// 循环左移
			P1 = x;			  				// 点亮
			for(i = 0; i < 500*12000; i++);	// 等待500ms
			continue;
		}
		if(mode == 0x03) {
			P1 = x & y;       				// 点亮
			x = _cror_(x, 1); 				// 循环右移
			y = _crol_(y, 1); 				// 循环左移
			for(i = 0; i < 500*12000; i++);	// 等待500ms
			continue;
		}
	}
	return 0;
}

/*
S0		0111 1110		7e		√  -->
S1		1011 1110		be
S2		1101 1110		de
S3		1110 1110		ee
S4		0111 1101		7d
S5		1011 1101		bd		√  <--
S6		1101 1101		dd
S7		1110 1101		ed
S8		0111 1011		7b
S9		1011 1011		bb
S10		1101 1011		db		√  --><--
S11		1110 1011		eb
S12		0111 0111		77
S13		1011 0111		b7
S14		1101 0111		d7
S15		1110 0111		e7		√  ----

@author:cming0420@gmail.com
@date:2023-3-16
@description:Matrix key control lighting effect	for C51 SCM
*/