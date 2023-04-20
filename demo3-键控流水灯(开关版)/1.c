#include <reg51.h>
#include <intrins.h>
sbit S0 = P3^0; // -----> ������ˮ��
sbit S1 = P3^1; // <----- ������ˮ��
sbit S2 = P3^2; // --><-- ˫����ˮ��
sbit S3 = P3^3; // �صƼ�

int main() {
	int i;
	unsigned char mode = 0x03;	// ��ʼ �ص�״̬
	unsigned char x = 0x7f; // ��ʼֵ 0111 1111
	unsigned char y = 0xfe;	//        1111 1110
	while(1){
	    if(S0 == 0) {  // ����S0
			mode = 0x00;   // ��ˮ��״̬
		}
		if(S1 == 0) {  // ����S1
			mode = 0x01;	// ��ˮ��״̬
		}
		if(S2 == 0) {  // ����S2
			mode = 0x02;   // ˫����ˮ��״̬
		}
		if(S3 == 0) {  // ����S3
			mode = 0x03;   // �ص�״̬
		}
		if(mode == 0x03){
			P1 = 0xff;  // �ص�
			continue;
		}
		if(mode == 0x00) // ����S0   -----> ������ˮ��
		{			  
			P1 = x;			  // ����
			x = _cror_(x, 1); // ѭ������
			y = _crol_(y, 1); // ͬ������
			for(i = 0; i < 10000; i++);
			continue;
		}
		if(mode == 0x01) // ����S1   <----- ������ˮ��
		{	
		    y = _cror_(y, 1); // ͬ������	  
			x = _crol_(x ,1); // ѭ������
			P1 = x;			  // ����
			for(i = 0; i < 10000; i++);
			continue;
		}
		if(mode == 0x02) // ����S2	--><-- ˫����ˮ��
		{
			P1 = x & y;       // ����
			x = _cror_(x, 1); // ѭ������
			y = _crol_(y, 1); // ѭ������
			for(i = 0; i < 10000; i++);
			continue;
		}
	}
	return 0;
}