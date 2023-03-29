#include <reg51.h>
#include <intrins.h>
#include <stdio.h>

code unsigned char KEY_VALUE_MAP[] = {
'0',0xc0,'1',0xf9,'2',0xa4,'3',0xb0,
'4',0x99,'5',0x92,'6',0x82,'7',0xf8,
'8',0x80,'9',0x90,'-',0xbf,'.',0x7f,
' ',0xff,'C',0xc6
};

unsigned char show_list[9] = {0,0,0,0,0,0,0,0,0};
unsigned char value_list[8] = {0,0,0,0,0,0,0,0};

void show(unsigned char * p);

int main() {
    float temp = 25.6;		  
	unsigned char i,j,k = 0;
    sprintf(show_list,"C    %.1f",temp);
	for (i = 0; i < 8; i++, k++) {
	    for (j = 0; j < 14; j++) {
		    if (show_list[k] == KEY_VALUE_MAP[j * 2]) {
			    value_list[i] = KEY_VALUE_MAP[j * 2 + 1];
				break;
			}
		}
		if (show_list[i + 1] == '.') {
		    value_list[i] = value_list[i] & 0x7f;
			k++;
		}
	}
	while (1) {
	    
	    show(value_list);
	}
	return 0;
}

void show(unsigned char * p) {
    static unsigned char i = 0,x = 0xfe,j;
	P2 = 0xff;
	P2 = p[i];
	P0 = x;
	for (j = 0x00; j < 0xff; j++);
	x = _crol_(x,1);
	i++;
	if (i == 8) {
	    i = 0;
	}
}
