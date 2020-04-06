//Eric Cai
//Section 01

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <stdio.h> 
#include <fstream>
#include <sys/timeb.h>
#include <sched.h>
#include <iostream>

using namespace std;

void RR(int timequantum, int process[], int bTimes[], FILE *fp){
	int time = 0;
	int done = 1;
	int tempproc;
	int queue[sizeof(process) - 1];
	fp = fopen("output.txt", "wt");
	fprintf(fp, "RR %d\n", timequantum);
	for (int i = 0; i < sizeof(process) - 1; i++) {
		queue[i] = process[i];
	}
	fprintf(fp,"%d %d", time, queue[0]);
	while (done != sizeof(process)) {
		if (bTimes[queue[0] - 1] != 0) {
			bTimes[queue[0] - 1]--;
		}
		else {
			done++;
			tempproc = queue[0];
			for (int i = 0; i < sizeof(process) - done; i++) {
				queue[i] = queue[i+1];
			}
			queue[sizeof(process) - 2] = tempproc;
			tempproc = 0;
		}
		if (time % timequantum == 0) {
			if (time == 0) {
				cout << "\n" << time << " " << queue[0] << "\n";
			}
			else {
				cout << "\n" << time << " " << queue[0] << "\n";
				tempproc = queue[0];
				for (int i = 0; i < sizeof(process) - done; i++) {
					queue[i] = queue[i+1];
				}
				queue[sizeof(process) - 2] = tempproc;
				tempproc = 0;
				for (int i = 0; i < sizeof(process) - done; i++) {
					cout << "\n" << queue[i] << " ";
					cout << "" << bTimes[queue[i] - 1] << " ";
					fprintf(fp,"%d %d", time, queue[0]);
				}
			}
		}
		time++;
	}
	fclose(fp);
}

void SJF(int process[], int bTimes[], FILE *fp){
	int time = 0;
	int done = 1;
	int tempproc;
	int queue[sizeof(process) - 1];
	int min = queue[0];
	fp = fopen("output.txt", "wt");
	fprintf(fp, "SJF");
	for (int i = 0; i < sizeof(process) - 1; i++) {
		queue[i] = process[i];
	}
	for (int i = 0; i < sizeof(process) - 1; i++) {
		for (int j = 0; j < sizeof(process) - 1; j++) {
			if (queue[i] > queue[j+1]) {
				queue[i] = queue[j+1];
			}
		}
	}
	fprintf(fp, "0 %d", queue[0]);
	
	for (int i = 0; i < sizeof(queue); i++) {
		for (int j = 0; j < queue[i]; j++) {
			bTimes[queue[i]-1] --;
			time++;
		}
		fprintf(fp,"%d %d", time, queue[i]);
	}
	fclose(fp);
}


void PR_noPREMP(int process[], int bTimes[], int arrival[], int priority[], FILE *fp){
	int time = 0;
	int done = 1;
	int tempproc;
	int queue[sizeof(process) - 1];
	fp = fopen("output.txt", "wt");
	for (int i = 0; i < sizeof(process) - 1; i++) {
		queue[i] = process[i];
	}
	fprintf(fp, "PR_noPREMP");
	fclose(fp);


}

void PR_withPREMP(int process[], int bTimes[], int arrival[], int priority[], FILE *fp){
	int time = 0;
	int done = 1;
	int tempproc;
	int queue[sizeof(process) - 1];
	fp = fopen("output.txt", "wt");
	for (int i = 0; i < sizeof(process) - 1; i++) {
		queue[i] = process[i];
	}
	fprintf(fp, "PR_withPREMP");
	fclose(fp);

}


int main() {
	int i = 0;
	int tq;
	int pnum;
	int skip;
	string format;
	int x;
	FILE *fptr;
	ifstream inFile("input.txt");
	fptr = fopen("input.txt","r");
	
	inFile >> format;
	if (format == "RR") {
		inFile >> tq;
		inFile >> pnum;
		cout << "RR " << tq << "\n";
		int process[pnum];
		int bTimes[pnum];
		for (int i = 0; i < pnum; i++) {
			inFile >> process[i];
			inFile >> skip;
			inFile >> bTimes[i];
			inFile >> skip;
		}
		RR(tq, process,bTimes, fptr);
	}
	
	else if (format == "SJF") {
		cout << "SJF";
		inFile >> pnum;
		cout << "RR " << tq << "\n";
		int process[pnum];
		int bTimes[pnum];
		for (int i = 0; i < pnum; i++) {
			inFile >> process[i];
			inFile >> skip;
			inFile >> bTimes[i];
			inFile >> skip;
		}
		SJF(process,bTimes, fptr);
	}
	
	else if (format == "PR_noPREMP") {
		cout << "PR_noPREMP";
		inFile >> pnum;
		cout << "RR " << tq << "\n";
		int process[pnum];
		int bTimes[pnum];
		int arrival[pnum];
		int priority[pnum];
		for (int i = 0; i < pnum; i++) {
			inFile >> process[i];
			inFile >> arrival[i];
			inFile >> bTimes[i];
			inFile >> priority[i];
		}
		PR_noPREMP(process,bTimes,arrival,priority,fptr);
	}
	
	else if (format == "PR_withPREMP") {
		cout << "PR_withPREMP";
		inFile >> pnum;
		cout << "RR " << tq << "\n";
		int process[pnum];
		int bTimes[pnum];
		int arrival[pnum];
		int priority[pnum];
		for (int i = 0; i < pnum; i++) {
			inFile >> process[i];
			inFile >> arrival[i];
			inFile >> bTimes[i];
			inFile >> priority[i];
		}
		PR_withPREMP(process,bTimes,arrival,priority, fptr);
	}
	
	//while (fscanf()
}


