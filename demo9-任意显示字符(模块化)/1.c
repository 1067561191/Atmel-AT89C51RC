#include <stdio.h>
#include "SEG.h"


int main() {
    unsigned char print_char_list[9]; // ��ʾ���ַ��б�
    unsigned char print_code_list[8]; // ��ʾ���б�
    float temp = 25.6; // Ҫ��ʾ������
	unsigned char j; // ѭ����������
    sprintf(print_char_list,"C    %.1f",temp); // ������ʾ�ַ���
	mapping(print_char_list, print_code_list); // ��ʾ�ַ�����ʾ��ӳ��
	while (1) {
	    show(print_code_list); // ��ʾ
		for (j = 0x00; j < 0xff; j++); // ����
	}
	return 0;
}