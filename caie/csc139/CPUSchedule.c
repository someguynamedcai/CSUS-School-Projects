/*
Eric Cai 
Section 01
Tested on Linux
Architecture:          i686
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                4
On-line CPU(s) list:   0-3
Thread(s) per core:    1
Core(s) per socket:    2
Socket(s):             2
Vendor ID:             GenuineIntel
CPU family:            6
Model:                 37
Model name:            Intel(R) Xeon(R) CPU E5-2640 0 @ 2.50GHz
Stepping:              1
CPU MHz:               2500.000
BogoMIPS:              5000.00
Hypervisor vendor:     VMware
Virtualization type:   full
L1d cache:             32K
L1i cache:             32K
L2 cache:              256K
L3 cache:              15360K
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/timeb.h>
#include <semaphore.h>
#include <fstream>

using namespace std;
ifstream inFile;


void RR(){}

void SJF(){}


void PR_noPREMP(){}

void PR_withPREMP(){}

int main(int argc, char *argv[]) { 
	pthread_t_tid[10];
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	inFile.open("input.txt");
	
	if (pthread_attr_getschedpolicy(&attr, &policy) != 0) {
		fprintf(stderr, "Unable to get policy.\n");
	}
	else {
		if (policy == SCHED_OTHER) printf("SCHED_OTHER\n"); 
		else if (policy == SCHED_RR) printf("SCHED_RR\n"); 
		else if (policy == SCHED_FIFO) printf("SCHED_FIFO\n"); 
    }
	
	/* set the scheduling policy - FIFO, RR, or OTHER */ 
	if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) 
		fprintf(stderr, "Unable to set policy.\n"); 
	/* create the threads */
	for (i = 0; i < NUM_THREADS; i++) 
		pthread_create(&tid[i],&attr,runner,NULL); 
	/* now join on each thread */
	for (i = 0; i < NUM_THREADS; i++) 
		pthread_join(tid[i], NULL); 
	
	inFile.close();

}
 
/* Each thread will begin control in this function */ 
void *runner(void *param)
{ 
   /* do some work ... */ 
   pthread_exit(0); 
} 	
}

