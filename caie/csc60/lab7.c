/*--------------------------------------------------------------*/
/* Eric Cai */
// Section 03 CSC 60
/* Lab 7     */

#include <stdlib.h>
#include <stdio.h>
/* Function Prototypes */
void bitprint (int num);
int rotate_left(int num, int n);

/*--------------------------------------------------------------*/
int main (void)
{
    int a, left_count, shifted_num;
    printf("Eric Cai.  Lab 7.\n");
    
    do
    {
	/* read a signed integer */
	printf("\nEnter an integer value (0 to stop):  ");
	scanf("%d", &a); 

	if (a != 0)
	{
	    printf("\nEnter an integer value for the left shift:  ");
	    scanf("%d", &left_count); 
	    printf("\nOriginal is %i \n", a);
			
	    bitprint(a);
	    shifted_num = rotate_left (a, left_count);
	    bitprint(shifted_num);
	    printf("Shifted it is %i \n", shifted_num);
	}

    } while (a != 0);

    printf("\n\n");
    return EXIT_SUCCESS;		
}

/*--------------------------------------------------------------*/

void bitprint (int num)
{
    unsigned mask;
    int bit, count, nbits;

    /* determine the word size in bits and set the initial mask */
    nbits = 8 * sizeof(int);	/* finds number of bytes in an int 
				   and changes it to bits */
    mask = 0x1 << (nbits - 1);	/* place 1 in left most position 
				   starting place for the mask */

    for(count = 1; count <= nbits; count++)
    {
	bit = (num & mask) ? 1: 0;   /* set display bit on or off */
	printf("%x", bit);	     /* print display bit */
	if(count %4 == 0)
	    printf(" ");	     /* blank space after every 4th digit */
	mask >>= 1;		     /* shift mask 1 position to the right */
    }

    printf("\n\n");

    return;
}
/*--------------------------------------------------------------*/
/* Put your rotate_left function here                           */
int  rotate_left (int num, int n) {
	unsigned mask;
	int bit, count, nbits, lbit;

	nbits = 8 * sizeof(int);
	mask = 0x1 << (nbits - 1);

	for (count = 1; count <=n; count++ ) {
		bit = ( mask & num) >>nbits - 1;	
		num <<= 1;
		num |=  bit;
		
	}
	return num;
}	
/*--------------------------------------------------------------*/
