//Eric Cai
//Section 04

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h> 
#include <iostream>

using namespace std;

int track;
int totald;

int main(int argc, char *argv[]){
	int track = 50;
	for (int i = 1; i < argc; i++) {
		cout << "Reading track " << atoi(argv[i]) << "\n"; 
		totald = totald + abs((track - atoi(argv[i])));
		track = atoi(argv[i]);
	}
	cout << "Total distance " << totald << "\n";
}
