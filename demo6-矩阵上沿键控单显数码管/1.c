#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char

/*
code uchar KEYVALUEARR[] = {
0x7e,'0',0xbe,'1',0xde,'2',0xee,'3',
0x7d,'4',0xbd,'5',0xdd,'6',0xed,'7',
0x7b,'8',0xbb,'9',0xdb,'.',0xeb,'+',
0x77,'-',0xb7,'*',0xd7,'/',0xe7,'='
};
*/

code uchar KEYVALUEARR2[] = {
0xc0,0xf9,0xa4,0xb0,
0x99,0x92,0x82,0xf8,
0x80,0x90,0x7f,0x7f,
0x7f,0x7f,0x7f,0x7f
};

/*return 0-15定义值*/
uchar KeyScan() {
    uchar x;
    P3 = 0x0f;
	if (P3 != 0x0f) {
	    switch (P3) {
		    case 0x0e : {
			    x = 0;
				break;
			}
			case 0x0d : {
			    x = 1;
				break;
			}
			case 0x0b : {
			    x = 2;
				break;
			}
			case 0x07 : {
			    x = 3;
				break;
			}
			default : {
			    break;
			}
		}
		P3 = 0xf0;
		if (P3 != 0xf0) {
		    switch (P3) {
			    case 0x70 : {
				    return 4*x+0;
				}
				case 0xb0 : {
				    return 4*x+1;
				}
				case 0xd0 : {
				    return 4*x+2;
				}
				case 0xe0 : {
				    return 4*x+3;
				}
				
			}
		}
	}
	return 0xff;
/*
	unsigned char i;
	unsigned char a = 0xfe;			// 1111 1110 
	for (i = 0; i < 4; i++) {		// 按行检测 先检测S0-S3 第一行
		P3 = a;
		if (P3 != a) {  			// 检测到了
			return P3;
		}
		a = _crol_(a, 1);			// 再检测S4-S7 第二行 再检测S8-S11 第三行 再检测S12-S15 第四行
	}
	return 0xff;  					// 默认返回全部高电平
*/
}


int main() {
    uchar key_value,now;
	uchar old = 0xff;
	while(1) {
	    key_value = KeyScan();	    // 键值
		
		now = KEYVALUEARR2[key_value];// 展示值
		
		if(old != now) { // 发生跳变
		    if (old == (old & now)) { // 下沿跳变
			    
			} else { // 上沿跳变 
			    P2 = old;
			}	  
		}
		old = now;
	}
	return 0;
}

/*
S0		0111 1110		7e
S1		1011 1110		be
S2		1101 1110		de
S3		1110 1110		ee
S4		0111 1101		7d
S5		1011 1101		bd
S6		1101 1101		dd
S7		1110 1101		ed
S8		0111 1011		7b
S9		1011 1011		bb
S10		1101 1011		db
S11		1110 1011		eb
S12		0111 0111		77
S13		1011 0111		b7
S14		1101 0111		d7
S15		1110 0111		e7

0		abcd ef			1100 0000
1       bc				1111 1001
2       abd eg			1010 0100
3		abcd g			1011 0000
4		bc fg			1001 1001
5		acd fg			1001 0010
6		acd efg			1000 0010
7		abc				1111 1000
8		abcd edf		1000 0000
9		abcd fg			1001 0000

@author:cming0420@gmail.com
@date:2023-3-16
@description:Matrix key control lighting effect	for C51 SCM
*/