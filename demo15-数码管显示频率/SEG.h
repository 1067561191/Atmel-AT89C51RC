#include <reg51.h>
#include <intrins.h>

extern unsigned char print_char_list[];
extern unsigned char print_code_list[];

void mapping(unsigned char *, unsigned char *);

void show(unsigned char *);