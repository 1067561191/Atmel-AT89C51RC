#include "SEG.h"

code unsigned char KEY_VALUE_MAP[] = {
'0',0xc0,'1',0xf9,'2',0xa4,'3',0xb0,
'4',0x99,'5',0x92,'6',0x82,'7',0xf8,
'8',0x80,'9',0x90,'-',0xbf,'.',0x7f,
' ',0xff,'C',0xc6
};

void mapping(unsigned char * print_char_list, unsigned char * print_code_list) {
	unsigned char i,j,k = 0;
    for (i = 0; i < 8; i++, k++) {
	    for (j = 0; j < 14; j++) {
		    if (print_char_list[k] == KEY_VALUE_MAP[j * 2]) {
			    print_code_list[i] = KEY_VALUE_MAP[j * 2 + 1];
				break;
			}
		}
		if (print_char_list[k + 1] == '.') {
		    print_code_list[i] = print_code_list[i] & 0x7f;
			k++;
		}
	}

}

void show(unsigned char * print_code_list) {
    static unsigned char i = 0,x = 0xfe;
	unsigned char j;
	P2 = 0xff;
	P2 = print_code_list[i];
	P0 = x;
	x = _crol_(x,1);
	for (j = 0x00; j < 0xff; j++);
	i++;
	if (i == 8) {
	    i = 0;
	}
}