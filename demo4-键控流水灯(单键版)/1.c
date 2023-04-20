#include<reg51.h>
#include<intrins.h>
sbit S1 = P3^0;

int main() {
	unsigned char mode = 0x00; 	// Ĭ�Ϲص�		0x00 �ص� 0x01 ��Ч1 0x02 ��Ч2 ...
	unsigned char x = 0x7f;		// 0111 1111
	unsigned char y = 0xfe;		// 1111 1110
	unsigned int i,j; 			// ѭ������
	while(1) {
		while(S1 == 0){ 					// S1 ����
			for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);			// 500ms
			if(S1 != 0){ 					// ����[0-500]ms
				P1 = 0xff;					// �ص���ʾ
				mode = 0x00;				// �ص�ģʽ
				break;						// �˳�while(S1 == 0)ѭ��
			} else {	 					// ����[500-1000]ms
				P1 = 0x7f;					// �ƹ���ʾ0111 1111
				mode = 0x01;				// ��Ч1ģʽ
				for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);		// 500ms
				if(S1 != 0){ 				// ����[500-1000]ms
					break;					// �˳�while(S1 == 0)ѭ��
				} else {					// ����[1000-1500]ms
					P1 = 0x3f;				// �ƹ���ʾ0011 1111
					mode = 0x02;			// ��Ч2ģʽ
					for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);	// 500ms
					if(S1 != 0){			// ����[1000-1500]ms
						break;				// �˳�while(S1 == 0)ѭ��
					} else {				// ����[1500-2000]ms
						P1 = 0x1f;			// �ƹ���ʾ0001 1111
						mode = 0x03;		// ��Ч3ģʽ
						for(i = 0; i < 500; i++) for(j = 0; j < 12000; j++);// 500ms
						break;				// �˳�while(S1 == 0)ѭ��
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