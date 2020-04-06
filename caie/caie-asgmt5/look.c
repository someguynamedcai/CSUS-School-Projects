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
	int turndifference[argc];
	int turn = 0;
	for (int k = 1; k < argc; k++) {
			differences[k-1] = atoi(argv[k]);
			turndifference[k-1] = -1;
	}
	for (int i = 0; i < argc-1; i++) {
		for (int j = 0; j < argc - 1; j++) {
			if (track = differences[j] < 0) {
				turndifference[j] = differences[j];
			}
			if (best > ((track - differences[j])) && ((differences[j] >= 0)) && (track-differences[j] > 0)) {
				best = (abs(track - differences[j]));
				bestc = j;
			}
		}
		for (int a = 0; a < argc; a++) {
			if (best > abs((track - differences[a])) && ((differences[a] >= 0))) {
				best = (abs(track - differences[a]));
				bestc = a;
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