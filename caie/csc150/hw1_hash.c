#include <stdio.h>
unsigned int xor_buf(unsigned char buf[], int nbytes,unsigned int acc) {
    int i = 0;
	for (i=0; i<nbytes; i++) {
        acc = 33*acc + buf[i];
	}
    return acc;
}
int main(int argc, char *argv[]) {
    unsigned char buf[128];
    unsigned int acc = 5383;
    int bytes_read  = fread(buf,1,sizeof(buf),stdin);
    while (bytes_read > 0) {
		acc = xor_buf(buf,bytes_read,acc);
        bytes_read  = fread(buf,1,sizeof(buf),stdin);
    }
    printf("%u\n",acc);
}