/* Reverse 64 bits double word and print bitwise */

#include <stdio.h>
#include <stdlib.h>

/* Reverse bit */
char reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

/* Reverse word (32 bits) */
int reversew(int w){
        char a, b, c, d;
	int final;

        a = (char) ((w & 0x000000ff));
        b = (char) ((w & 0x0000ff00)>>8);
        c = (char) ((w & 0x00ff0000)>>16);
        d = (char) ((w & 0xff000000)>>24);

	a = reverse(a);
	b = reverse(b);
	c = reverse(c);
	d = reverse(d);

	final = d | c<<8 | b<<16 | a<<24;
        return final;
}

/* Reverse double word (64  bits) */
long long reversedw(long long dw){
	int a, b;
	long long final;
	
	a = (int) ((dw & 0xffffffff00000000) >> 32);
	b = (int) (dw & 0x00000000ffffffff);

	final = reversew(b);
        final = final << 32 | reverse(a);

	return final;
}

/* Printf bits of a double word */
void printbit(long long x){
	int i;

	for (i = 0; i <=63; i++){
		if ( x & (1ULL << (63 - i)))
			printf("%u", 1);
		else
			printf("%u", 0);
	}
}

int main(int argc, char **argv){
	long long f;
        if (!argv[1]){
                printf("please use %s [word]\n", argv[0]);
                return -1; 
        }
	f = atoll(argv[1]);
        printf("Converting: 0x%016llx (", f);
	printbit(f);
        f = reversedw(f);
	printf(")\nResult is : 0x%016llx (", f); 
	printbit(f);
	printf(")\n");

        return 0;
}

