/* Reverse 64 bits double word and print bitwise */

#include <stdio.h>
#include <stdlib.h>

#define SPR_TEXASR_FC		0xFE00000000000000
#define SPR_TEXASR_ABORT        0x100000000
#define SPR_TEXASR_SUSP         0x80000000
#define SPR_TEXASR_HV           0x20000000
#define SPR_TEXASR_PR           0x10000000
#define SPR_TEXASR_FS           0x8000000
#define SPR_TEXASR_EXACT        0x4000000
#define SPR_TEXASR_ROT          0x2000000
#define SPR_TEXASR_TL           0xFFF;

long long unsigned texasr;


void dump_texasr(long long unsigned f){
	if (f & SPR_TEXASR_ABORT) {
		printf("[ABORT]");
		texasr |= SPR_TEXASR_ABORT;
	}
	if (f & SPR_TEXASR_SUSP ) {
		printf("[SUSP]");
		texasr |= SPR_TEXASR_SUSP;
	}
	if (f & SPR_TEXASR_HV) {
		printf("[HV]");
		texasr |= SPR_TEXASR_HV;
	}
	if (f & SPR_TEXASR_PR) {
		printf("[PR]");
		texasr |= SPR_TEXASR_PR;
	}
	if (f & SPR_TEXASR_FS) {
		printf("[FS]");
		texasr |= SPR_TEXASR_FS;
	}
	if (f & SPR_TEXASR_EXACT) {
		printf("[EXACT]");
		texasr |= SPR_TEXASR_EXACT;
	}
	if (f & SPR_TEXASR_ROT) {
		printf("[ROT]");
		texasr |= SPR_TEXASR_ROT;
	}
	if (f & SPR_TEXASR_FC) {
		printf("[RC = %llx ]", (f & SPR_TEXASR_FC) >> 56);
		texasr |= SPR_TEXASR_FC & f;
	}
	printf("\n");
}


/* Printf bits of a double word */
void printbit(unsigned long long x){
	int i;

	for (i = 0; i <=63; i++){
		if ( x & (1ULL << (63 - i))){
			printf("%u", 1);
		}
		else
			printf("%u", 0);
	}
}



int main(int argc, char **argv){
	unsigned long long f;
        if (!argv[1]){
                printf("please use %s [word]\n", argv[0]);
                return -1; 
        }
	f = strtoull(argv[1], NULL, 16);
        printf("TEXASR       : 0x%016llx\n", f);
	printf("Bitwise   : ");
	printbit(f);
	printf("\n");	
	printf("Flags set  :");
	dump_texasr(f);
	printf("\nXOR       : ");
	printbit(texasr ^ f);
	printf("\n");
        return 0;
}

