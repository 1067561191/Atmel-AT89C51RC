#include <reg51.h>
#include <intrins.h>
sbit S0 = P3^0; // -----> 右移流水灯
sbit S1 = P3^1; // <----- 左移流水灯
sbit S2 = P3^2; // --><-- 双向流水灯
sbit S3 = P3^3; // 关灯键

int main() {
	int i;
	unsigned char mode = 0x03;	// 初始 关灯状态
	unsigned char x = 0x7f; // 初始值 0111 1111
	unsigned char y = 0xfe;	//        1111 1110
	while(1){
	    if(S0 == 0) {  // 摁下S0
			mode = 0x00;   // 流水灯状态
		}
		if(S1 == 0) {  // 摁下S1
			mode = 0x01;	// 流水灯状态
		}
		if(S2 == 0) {  // 摁下S2
			mode = 0x02;   // 双向流水灯状态
		}
		if(S3 == 0) {  // 摁下S3
			mode = 0x03;   // 关灯状态
		}
		if(mode == 0x03){
			P1 = 0xff;  // 关灯
			continue;
		}
		if(mode == 0x00) // 摁下S0   -----> 右移流水灯
		{			  
			P1 = x;			  // 点亮
			x = _cror_(x, 1); // 循环右移
			y = _crol_(y, 1); // 同步左移
			for(i = 0; i < 10000; i++);
			continue;
		}
		if(mode == 0x01) // 摁下S1   <----- 左移流水灯
		{	
		    y = _cror_(y, 1); // 同步右移	  
			x = _crol_(x ,1); // 循环左移
			P1 = x;			  // 点亮
			for(i = 0; i < 10000; i++);
			continue;
		}
		if(mode == 0x02) // 摁下S2	--><-- 双向流水灯
		{
			P1 = x & y;       // 点亮
			x = _cror_(x, 1); // 循环右移
			y = _crol_(y, 1); // 循环左移
			for(i = 0; i < 10000; i++);
			continue;
		}
	}
	return 0;
}