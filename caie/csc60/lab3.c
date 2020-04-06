/* ---------------
 * Eric Cai
 * Lab 3          */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
 double radius, height, area, volume;
 FILE *FILE_IN;
 FILE *FILE_OUT;

 FILE_IN = fopen("lab3.dat", "r");
 if (FILE_IN == NULL) {
   printf("Error on opening the input file \n");
   exit(EXIT_FAILURE); 
 }

 FILE_OUT = fopen("lab3.out", "w");
 if (FILE_OUT == NULL) {
   printf("Error on opening the output file\n");
   exit(EXIT_FAILURE);
 }

 fprintf(FILE_OUT, "\nEric Cai. Lab 3 involving Cylinders.\n\n");
 fprintf(FILE_OUT, " Radius     Height     Top Area    Volume\n");
 fprintf(FILE_OUT, "--------   --------   ----------  ---------\n");
		
 while((fscanf(FILE_IN, "%lf%lf%", &radius, &height)) == 2) {
   area = M_PI*radius*radius;
   volume = M_PI*radius*radius*height;
   fprintf(FILE_OUT, "%7.3f %9.3f %12.3f %10.3f\n", radius, height, area, volume);
 }
 fclose(FILE_IN);
 fclose(FILE_OUT);

 return EXIT_SUCCESS;
}
/*-----------------------------*/
