/*  Eric Cai                                           */
/*  Lab 5 using pointers and arrays                    */
/*  A simple driver for testing your sub function      */

#include <stdio.h>
#include <stdlib.h>


/*  a function prototype */
void do_average(int x[], int npts, double *average, int *gtr);

/*--------------------------------------------------------------------*/					 
int main(void)
{
	int c, greater;
	int stuff[]  = {6, 1, 35, 58, 46, 7, 70, 2, 9, 19, 21, 83, 10};
		  /* preset values so focus is on the pointers  */
	int npts = 13;
	double average;


	printf("\n\nEric Cai, Lab 5 output.\n");

	printf("\nThe numbers are:  \n");
	for(c = 0; c < npts;  c++)
	{
		printf("%4i", stuff[c]);
	}
	printf("\n\n");

	do_average(stuff, npts, &average, &greater);
			 /* in     in    output    output   */

	printf("The average is:  %5.2f\n\n", average);
	printf("The number of values > average is:  %2i\n\n",  greater);

	return EXIT_SUCCESS;
}
/*--------------------------------------------------------------------*/

void do_average(int x[], int npts, double *average, int *gtr) { 
	int ngtr = 0;
	int total = 0;
	int count;
	int avg = 0; 
	for (count = 0; count < npts; count++) {
        	total = x[count] + total;
   	}
   	avg = total / npts;
	*average = avg;
   	for (count = 0; count < npts; count++) {
      		if (x[count] > avg) {
         		ngtr++;
      		}
   	}
	*gtr = ngtr;	
        return;
}                                       
/*  This function returns via pointers, the double average value of a */              
/*  one-dimensional integer array, and number of values in the array  */
/*  that are greater than the average.                                */








/*--------------------------------------------------------------------*/
