#include <reg51.h>
#include <intrins.h>
sbit S0 = P3^0; // -----> 右移流水灯
sbit S1 = P3^1; // <----- 左移流水灯
sbit S2 = P3^2; // --><-- 双向流水灯

int main() {
	int i;
	unsigned char x = 0x7f; // 初始值 0111 1111
	unsigned char y = 0xfe; //        1111 1110
	while(1){
		if(S0 == 0) // 摁下S0   -----> 右移流水灯
		{			  
			P1 = x;			  // 点亮
			x = _cror_(x, 1); // 循环右移
			y = _crol_(y, 1); // 同步左移
			for(i = 0; i < 10000; i++);
		}
		if(S1 == 0) // 摁下S1   <----- 左移流水灯
		{		  
			x = _crol_(x ,1); // 循环左移
			y = _cror_(y, 1); // 同步右移
			P1 = x;			  // 点亮
			for(i = 0; i < 10000; i++);
		}
		if(S2 == 0) // 摁下S2	--><-- 双向流水灯
		{
			P1 = x & y; // 点亮
			x = _cror_(x, 1); // 循环右移
			y = _crol_(y, 1); // 循环左移
			for(i = 0; i < 10000; i++);
		}
	}
	return 0;
}