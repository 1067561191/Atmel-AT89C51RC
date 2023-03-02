#include <reg51.h>
#include <intrins.h>

int main() {
	int i;							 // 延迟循环条件变量
	unsigned char x = 0x3f;			 // 0011 1111
	while(1){						 // 死循环
	    P1 = x;						 // 点亮
		x = _cror_(x,2);			 // 循环右移2位
		for(i = 0; i < 10000; i++);	 // 延迟
	}
    return 0;
}