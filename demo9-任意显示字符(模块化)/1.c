#include <stdio.h>
#include "SEG.h"


int main() {
    unsigned char print_char_list[9];
    unsigned char print_code_list[8];
    float temp = 25.6;
	unsigned char j;
    sprintf(print_char_list,"C    %.1f",temp);
	mapping(print_char_list, print_code_list);
	while (1) {
	    show(print_code_list);
		for (j = 0x00; j < 0xff; j++);
	}
	return 0;
}