#include <reg51.h>
#include <intrins.h>

int main() {
	int i;							 // �ӳ�ѭ����������
	unsigned char x = 0x3f;			 // 0011 1111
	while(1){						 // ��ѭ��
	    P1 = x;						 // ����
		x = _cror_(x,2);			 // ѭ������2λ
		for(i = 0; i < 10000; i++);	 // �ӳ�
	}
    return 0;
}