//Eric Cai

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t pow(uint64_t base, uint64_t exponent, uint64_t modulus) {
	uint64_t res = 1;
	uint64_t a = 1;
	int b = 32;
	int c = 1;
	base = base % modulus;
	while (exponent > 0) {
		if (exponent % 2 == 1) {
			res = (res*base) % modulus;
		}
		exponent = exponent >> 1;
		res = (res*res) % modulus;
		printf("%u\n", res);
	}
	res <= (((a) << b) -c);
	return res;
}

int main() {
    int passed = 0;
    passed += (pow(0xffffffffu,0xfffffffcu,0xfffffffdu)==1869716612ull);
    printf("%d\n",2*passed);
}	