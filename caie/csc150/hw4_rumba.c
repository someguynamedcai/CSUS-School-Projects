#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "chacha20_simple.h"

unsigned char chain[64] = {0};
unsigned char xblocks[];
chacha20_setup(
unsigned char compression(unsigned char *chain[], unsigned char x_i[]) {
	unsigned char M_1[48];
	unsigned char M_2[48];
	unsigned char M_3[48];
	unsigned char M_4[48];
	
	for (int bytes = 0; bytes < 48; bytes++) {
		M_1[bytes] = x_i[bytes];
	}
	for (int bytes = 0; bytes < 48; bytes++) {
		M_2[bytes] = x_i[bytes+48];
	}
	for (int bytes = 0; bytes < 48; bytes++) {
		M_3[bytes] = x_i[bytes+96];
	}
	for (int bytes = 0; bytes < 48; bytes++) {
		M_4[bytes] = x_i[bytes+144];
	}
	return chacha20_block(chain,M_1,64) ^ chacha20_block(chain,M_2,64) ^ chacha20_block(chain,M_3,64) ^ chacha20_block(chain,M_4,64); 
}

void rumba(unsigned char out[32], unsigned char in[], int n) {
	int pad = 0;
	do {
		in[pad] = 1;
		in[pad+1] = 0;
		pad++;
	}
	while (n % 128 != 0);
	
	for (int chunk = 0; chunk < (n/128); chunk++) {
		for (int sep = 0; sep < 128; sep++) {
			xblocks[chunk] = in[sep];
		}
	}
	
	
	for (int i = 0; i < n; n++) {
		chain[i] = compression(chain,xblocks[i]);
	}

	memcpy(out,chain,32);
}

int main() {
    unsigned char in[4096];
    unsigned char check[32];
    unsigned char result1[32];
    unsigned char result2[32];
    int score = 0;
    
    for (int i=0; i<4096; i++)
        in[i] = (unsigned char)(i*i+i+13);
	
    rumba(check, in, 4096);
    
    rumba(result2, in, 0);
    if (memcmp(result1,result2,32)==0) score += 25;

    rumba(result2, in, 1);
    if (memcmp(result1,result2,32)==0) score += 25;

    rumba(result2, in, 256);
    if (memcmp(result1,result2,32)==0) score += 25;

    rumba(result2, in, 4000);
    if (memcmp(result1,result2,32)==0) score += 25;

    rumba(result1, in, 4096);
    if (memcmp(result1,check,32)!=0) printf("Data altered!\n");
    
    printf("%d.%d\n",score/10,score%10);
}