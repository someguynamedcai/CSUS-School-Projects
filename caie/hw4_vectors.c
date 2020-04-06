#include <stdio.h>
#include <string.h>

void rumba(unsigned char out[32], unsigned char in[], int n);

int main() {
    unsigned char in[4096];
    unsigned char result[32];
    int score = 0;
    
    for (int i=0; i<4096; i++)
        in[i] = (unsigned char)(i*i+i+13);

    rumba(result, in, 0);
    for (int i=0; i<32; i++) printf("%02X",result[i]); printf("\n");

    rumba(result, in, 1);
    for (int i=0; i<32; i++) printf("%02X",result[i]); printf("\n");

    rumba(result, in, 256);
    for (int i=0; i<32; i++) printf("%02X",result[i]); printf("\n");

    rumba(result, in, 4000);
    for (int i=0; i<32; i++) printf("%02X",result[i]); printf("\n");

}
