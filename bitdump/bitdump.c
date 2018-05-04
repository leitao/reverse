#include <stdio.h>
#include <stdlib.h>

void dumpall(int *b, int first, int last){
	int i = 0;
	int z = 0;
	int n =4;
	int y;

	// Result
	unsigned long f = 0;

	for (y = 0 ; y <= n; y++){
		for (; z< y*(64/n) ; z++){
			if (z >= first && z < last) {
				f = f << 1;
				printf("%2d ", b[z]);
				if (b[z]){
					f = f | 0x1;
				} 
			}
			else
				printf("-- ");
		}
		printf("\n");
		for (; i< y*(64/n); i++){
			if (i >= first && i < last)
				printf("%2d ", i);
			else
				printf("-- ");
		}
		printf("\n\n");
	}

	printf("\n");
	printf("Result = %lx\n", f);
}

int main(int argc, char **argv){
	unsigned long n = 0;
	unsigned int first, last;
	unsigned int b[64];
	int i;

	if (argc == 2) {
		first = 0;
		last = 64;
	} else if (argc <4) {
		printf("Please use %s <NUM> <initial bit> <final bit>\n", argv[0]);
		exit(-1);
	} else {
		first = atoi(argv[2]);
		last = atoi(argv[3]);
	}

	if (last > 63)
		last = 64;
	if (first < 0)
		first = 0;

	n = strtoul(argv[1], NULL, 0);


#ifdef PRINT
	printf("num is %lx\n", n);
#endif
	for (i = 0; i <= 63; i++) {
#ifdef PRINT
		printf("%d %x\n\n", i, n>>(63-i));
#endif
		b[i] = (n >> (63 - i)) & 0x1;
	}

	dumpall(b, first, last);
}

