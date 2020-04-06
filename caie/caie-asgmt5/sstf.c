//Eric Cai
//Section 04

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h> 
#include <fstream>
#include <sys/timeb.h>
#include <sched.h>
#include <iostream>

using namespace std;

int track;
int totald;
int chosen;

int main(int argc, char *argv[]){
	int track = 50;
	int best = 10000000;
	int count = 1;
	chosen = 0;
	int bestc;
	int differences[argc];
	for (int k = 1; k < argc; k++) {
			differences[k-1] = atoi(argv[k]);
	}
	for (int i = 0; i < argc-1; i++) {
		for (int j = 0; j < argc - 1; j++) {
			if (best > (abs(track - differences[j])) && ((differences[j] >= 0))) {
				best = (abs(track - differences[j]));
				bestc = j;
			}
		}
		cout << "Reading track " << differences[bestc] << "\n"; 
		totald = totald + best;
		track = differences[bestc];
		best = 10000000;
		differences[bestc] = -1;
	}
	cout << "Total distance " << totald << "\n";
}