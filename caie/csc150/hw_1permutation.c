#include <stdio.h>
unsigned char permutation(unsigned char x) {
	x = x ^ x;
	x = x * x;
	x = x + 10;
	
	return x;
}
unsigned char inverse(unsigned char y) {
	y = y - 10;
	y = y/y;
	y = y ^ y;
	return y;
}

int main(int argc, char *argv[]) {
	unsigned char x = 5;
	printf(permutation(x));
	printf(inverse(x));
}