#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

code uchar DISPLAY_VALUE[] = {
0xc0,0xf9,0xa4,0xb0,
0x99,0x92,0x82,0xf8,
0x80,0x90,0xbf
};



int main() {
    uchar index[8] = {10,10,10,10,10,10,10,10};
	uchar min = 0,sec = 0,hour = 0,x = 0xfe,i;
	uchar j, k = 0;
	while (1) {
	    if (k == 80) {
		    k = 0;
		    sec++;
		}
		if (sec == 60) {
		    sec = 0;
			min++;
		}
		if (min == 60) {
		    min = 0;
			hour++;
		}
		if (hour == 24) {
		    hour = 0;
		}
	    index[0] = hour / 10;
	    index[1] = hour % 10;
	    index[3] = min / 10;
	    index[4] = min % 10;
	    index[6] = sec / 10;
	    index[7] = sec % 10;
	    for (i = 0; i < 8; i++) {				  
		    P2 = 0xff; 							// ¹ØµÆ ·À¹íÉÁ
			P2 = DISPLAY_VALUE[index[i]];		// ¿ªµÆ
			P0 = x;								// Ñ¡ÔñÐÅºÅ
			for (j = 0x00; j < 0xff; j++);		// ·ÀÉÁ
		    x = _crol_(x,1);					// Ñ¡ÔñÐÅºÅ×óÒÆ
		}
		k++;
	}
	return 0;
}
