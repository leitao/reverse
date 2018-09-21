/* Reverse 64 bits double word and print bitwise */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PSL_VEC         0x02000000UL    /* AltiVec/SPE vector unit available */
#define PSL_VSX         0x00800000UL    /* Vector-Scalar unit available */
#define PSL_EE          0x00008000UL    /* external interrupt enable */
#define PSL_RESERVED    0x003F8000UL    /* Reserved */
#define PSL_PR          0x00004000UL    /* privilege mode (1 == user) */
#define PSL_FP          0x00002000UL    /* floating point enable */
#define PSL_ME          0x00001000UL    /* machine check enable */
#define PSL_FE0         0x00000800UL    /* floating point interrupt mode 0 */
#define PSL_FE1         0x00000100UL    /* floating point interrupt mode 1 */
#define PSL_PMM         0x00000004UL    /* performance monitor mark */
#define PSL_RI          0x00000002UL    /* recoverable interrupt */
#define PSL_POW         0x00040000UL    /* power management */
#define PSL_ILE         0x00010000UL    /* interrupt endian mode (1 == le) */
#define PSL_SE          0x00000400UL    /* single-step trace enable */
#define PSL_BE          0x00000200UL    /* branch trace enable */
#define PSL_IR          0x00000020UL    /* instruction address relocation */
#define PSL_DR          0x00000010UL    /* data address relocation */
#define PSL_LE          0x00000001UL    /* endian mode (1 == le) */
#define PSL_CM          0x80000000UL    /* Computation Mode (64-bit) */
#define PSL_HV          0x1000000000000000UL    /* hyper-privileged mode */
#define PSL_SF          0x8000000000000000UL    /* 64-bit addressing */
#define PSL_HTM         0x0000000100000000UL
#define PSL_HTM         0x0000000100000000UL
#define PSL_HTM_TRA     0x0000000400000000UL    /* Hardware Transactional Memory State */
#define PSL_HTM_TSU     0x0000000200000000UL    /* Hardware Transactional Memory State */

unsigned long long msr = 0;

void dump_msr(long long unsigned f){
	if (f & PSL_VEC) {
		printf("[VEC]");
		msr |= PSL_VEC;
	}
	if (f & PSL_VSX) {
		printf("[VSX]");
		msr |= PSL_VSX;
	}
	if (f & PSL_EE) {
		printf("[EE]");
		msr |= PSL_EE;
	}
	if (f & PSL_PR) {
		printf("[PR]");
		msr |= PSL_PR;
	}
	if (f & PSL_FP) {
		printf("[FP]");
		msr |= PSL_FP;
	}
	if (f & PSL_ME) {
		printf("[ME]");
		msr |= PSL_ME;
	}
	if (f & PSL_FE0) {
		printf("[FE0]");
		msr |= PSL_FE0;
	}
	if (f & PSL_FE1) {
		printf("[FE1]");
		msr |= PSL_FE1;
	}
	if (f & PSL_PMM) {
		printf("[PMM]");
		msr |= PSL_PMM;
	}
	if (f & PSL_RI) {
		printf("[RI]");
		msr |= PSL_RI;
	}
	if (f & PSL_POW) {
		printf("[POW]");
		msr |= PSL_POW;
	}
	if (f & PSL_ILE) {
		printf("[ILE]");
		msr |= PSL_ILE;
	}
	if (f & PSL_SE) {
		printf("[SE]");
		msr |= PSL_SE;
	}
	if (f & PSL_BE) {
		printf("[BE]");
		msr |= PSL_BE;
	}
	if (f & PSL_IR) {
		printf("[IR]");
		msr |= PSL_IR;
	}
	if (f & PSL_DR) {
		printf("[DR]");
		msr |= PSL_DR;
	}
	if (f & PSL_LE) {
		printf("[LE]");
		msr |= PSL_LE;
	}
	if (f & PSL_CM) {
		printf("[CM]");
		msr |= PSL_CM;
	}
	if (f & PSL_HV) {
		printf("[HV]");
		msr |= PSL_HV;
	}
	if (f & PSL_SF) {
		printf("[SF]");
		msr |= PSL_SF;
	}
	if (f & PSL_HTM) {
		printf("[HTM]");
		msr |= PSL_HTM;
	}
	if (f & PSL_HTM_TRA) {
		printf("[TRA]");
		msr |= PSL_HTM_TRA;
	}
	if (f & PSL_HTM_TSU) {
		printf("[TSU]");
		msr |= PSL_HTM_TSU;
	}
	if (f & PSL_RESERVED) {
		printf("[Reserved]");
		msr |= PSL_RESERVED & f;
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
	char *spec;

        if (!argv[1]){
                printf("please use %s [word]\n", argv[0]);
                return -1; 
        }
	spec = argv[2];

	f = strtoull(argv[1], NULL, 16);
        printf("MSR       : 0x%016llx\n", f);

	if (spec != NULL) {
		if (!strcmp(spec, "PR")) {
			printf("MSR[PR] is %s\n", f & PSL_PR ? "Enabled" : "Disabled");
			return 0;
		}
	}
	
	printf("Bitwise   : ");
	printbit(f);
	printf("\n");	
	printf("Flags set  :");
	dump_msr(f);
	printf("\nXOR       : ");
	printbit(msr ^ f);
	printf("\n");
        return 0;
}

