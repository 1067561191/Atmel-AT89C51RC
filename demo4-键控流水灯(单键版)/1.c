#include<reg51.h>
#include<intrins.h>
sbit S1 = P3^0;

int main() {
	unsigned char mode = 0x00; 	// 默认关灯		0x00 关灯 0x01 灯效1 0x02 灯效2 ...
	unsigned char x = 0x7f;		// 0111 1111
	unsigned char y = 0xfe;		// 1111 1110
	unsigned int i,j; 			// 循环变量
	while(1) {
		while(S1 == 0){ 					// S1 摁下
			for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);			// 500ms
			if(S1 != 0){ 					// 长摁[0-500]ms
				P1 = 0xff;					// 关灯提示
				mode = 0x00;				// 关灯模式
				break;						// 退出while(S1 == 0)循环
			} else {	 					// 长摁[500-1000]ms
				P1 = 0x7f;					// 灯光提示0111 1111
				mode = 0x01;				// 灯效1模式
				for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);		// 500ms
				if(S1 != 0){ 				// 长摁[500-1000]ms
					break;					// 退出while(S1 == 0)循环
				} else {					// 长摁[1000-1500]ms
					P1 = 0x3f;				// 灯光提示0011 1111
					mode = 0x02;			// 灯效2模式
					for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);	// 500ms
					if(S1 != 0){			// 长摁[1000-1500]ms
						break;				// 退出while(S1 == 0)循环
					} else {				// 长摁[1500-2000]ms
						P1 = 0x1f;			// 灯光提示0001 1111
						mode = 0x03;		// 灯效3模式
						for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);// 500ms
						break;				// 退出while(S1 == 0)循环
					}
				}
			}
		}

		if(mode == 0x00) {
			P1 = 0xff;
			continue;
		}
		if(mode == 0x01) {
			P1 = x;
			x = _cror_(x, 1);
			y = _crol_(y, 1);
			for(i = 0; i < 250; i++) for(j = 0; j < 12000; j++);	// 250ms
			 // 12HMz 1ms
			continue;
		}
		if(mode == 0x02) {
			P1 = x;
			x = _crol_(x, 1);
			y = _cror_(y, 1);
			for(i = 0; i < 250; i++) for(j = 0; j < 12000; j++);	// 250ms
			continue;
		}
		if(mode == 0x03) {
			P1 = x & y;
			x = _cror_(x, 1);
			y = _crol_(y, 1);
			for(i = 0; i < 250; i++) for(j = 0; j < 12000; j++);	// 250ms
			continue;
		}
	}
	return 0;
}