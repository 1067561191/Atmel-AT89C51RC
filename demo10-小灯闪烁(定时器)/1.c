#include <reg51.h>

int main() {
	unsigned char i = 0; // 计时次数默认值1
    TR0 = 1; // 开启计时器T0
    TMOD = 0x01; // 设置计时模式
	TH0 = 0x3c; // 设置高位初始值
	TL0 = 0xb0;	// 设置低位初始值
	P1 = 0xfe; // 默认开灯
	while (1) {
	    if (TF0 == 1) { // 溢出--完成计时了
		    TF0 = 0; // 重置完成状态
			TR0 = 1; // 再次开启计时器T0
			TH0 = 0x3c; // 再次设置高位初始值
	        TL0 = 0xb0; // 再次设置低位初始值
			i++; // 计时次数+1
		}
		if (i == 20) { // 当完成20次计数时
			if (P1 == 0xfe) { // 如果是开灯状态
		    	P1 = 0xff; // 关灯
			} else { // 如果是关灯状态
		    	P1 = 0xfe; // 开灯
			}
			i = 0; // 重置计时次数
		}	
	}
	return 0;
}