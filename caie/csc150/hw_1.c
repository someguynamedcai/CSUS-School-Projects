#include <stdio.h>
unsigned char permutation(unsigned char x) {
	x = x ^ 5;
	x = ~x;
	x = x + 1;
	
	return x;
}
unsigned char inverse(unsigned char y) {
	y = y - 1;
	y = ~y;
	y = y ^ 5;
	return y;

}