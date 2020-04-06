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
#include <vector>


using namespace std;

void RR(int timequantum, vector<int> process, vector<int> bTimes[] vector<int> arrival[]){
	int time = 0;
	int done = 1;
	int tempproc;
	int queue[process.size() - 1];
	int cputime;
	int waittime;
	int responsetime;
	int turnaroundtime;
	printf("RR\n");
	for (int i = 0; i < process.size()  - 1; i++) {
		queue[i] = process.at(i);
	}
	printf("%d %d", time, queue[0]);
	while (done != process.size()) {
		if ((bTimes.at(queue[0]) - 1) != 0) {
			bTimes.at([queue[0]) --;
		}
		else {
			done++;
			tempproc = queue[0];
			for (int i = 0; i <process.size()  - done; i++) {
				queue[i] = queue[i+1];
			}
			queue[process.size() - 2] = tempproc;
			tempproc = 0;
		}
		if (time % timequantum == 0) {
			if (time == 0) {
				cout << "\n" << time << " " << queue[0] << "\n";
			}
			else {
				cout << "\n" << time << " " << queue[0] << "\n";
				tempproc = queue[0];
				for (int i = 0; i < process.size()  - done; i++) {
					queue[i] = queue[i+1];
				}
				queue[process.size() - 2] = tempproc;
				tempproc = 0;
				for (int i = 0; i < process.size() - done; i++) {
					cout << "\n" << queue[i] << " ";
					cout << "" << bTimes.at([queue[i] - 1]) << " ";
					printf("%d %d", time, queue[0]);
				}
			}
		}
		time++;
	}
	cout << "Average cpu usage: " + cputime;
	cout << "Average waiting time: " + waittime;
	cout << "Average response time: " + responsetime;
	cout << "Average turnaround time: " + turnaroundtime;
}

void SRTF(vector<int> process[], vector<int> bTimes[] vector<int> arrival[]){
	int time = 0;
	int done = 1;
	int tempproc;
	int queue[sizeof(process) - 1];
	int min = queue[0];
	int cputime;
	int waittime;
	int responsetime;
	int turnaroundtime;
	printf(fp, "SRTF");
	queue[0] = bTimes[0];
	for (int i = 0; i < process.size()  - 1; i++) {
		if (queue[0] > bTimes[i]) {
			for (int j = 0; j < process.size()  - 1; j++) {
				queue[j] = queue[j+1];
			}
			queue[0] = bTimes[i];
		}
	}
	while (done != process.size() ) {
		if ((bTimes.at(queue[0]) - 1) != 0) {
			bTimes.at([queue[0]) --;
		}
		else {
			done++;
			waittime = waittime + time;
			responsetime = responsetime + (time - arrival[count];
			turnaroundtime = turnaroundtime + (time - arrival[count]);
			for (int i = 0; i < process.size() - done; i++) {
				queue[i] = queue[i+1];
			}
			count++;
		}
	cout << "Average cpu usage: " + cputime;
	cout << "Average waiting time: " + waittime;
	cout << "Average response time: " + responsetime;
	cout << "Average turnaround time: " + turnaroundtime;
}
	


void FCFS(vector<int> process[], vector<int> bTimes[], vector<int> arrival[]){
	int time = 0;
	int done = 1;
	int count = 0;
	int queue[process.size() - 1];
	int cputime;
	int waittime;
	int responsetime;
	int turnaroundtime;
	for (int i = 0; i < process.size() - 1; i++) {
		queue[i] = process[i];
	}
	printf("FCFS\n");
	printf("%d %d", time, queue[0]);
	while (done != process.size()) {
		if ((bTimes.at(queue[0]) - 1) != 0) {
			bTimes[(queue[0])] --;
			cout << "Process" + (count + 1) + "Time: " + time;
		}
		else {
			done++;
			waittime = waittime + time;
			responsetime = responsetime + (time - arrival[count];
			turnaroundtime = turnaroundtime + (time - arrival[count]);
			for (int i = 0; i < process.size()  - done; i++) {
				queue[i] = queue[i+1];
			}
			count++;
		}
	}
	waittime = waittime/ process.size() 
	responsetime = responsetime/ process.size() ;
	turnaroundtime = turnaroundtime/ process.size();
	cout << "Average cpu usage: 100%";
	cout << "Average waiting time: " + waittime;
	cout << "Average response time: " + responsetime;
	cout << "Average turnaround time: " + turnaroundtime;
}

int main(int argc, char *argv[]){
	int i = 0;
	int tq;
	int pnum;
	string format;
	int count = 0;
	FILE *fptr;	
	int process;
	int arrival;
	int bTimes;
	vector<int> processq;
	vector<int> arrivalq;
	vector<int> bTimesq;
	if(argc > 3){
		fprintf(stderr, "Invalid number of arguments!\n");
		exit(-1);
	}
	else {
		if (argc == 3) {
			tq = argv[2];
		}
		else {
			format = argv[1];
			file = argv[0];
			ifstream inFile(file);
			fptr = fopen(file,"r");
		}
		
	}
	if (format == "RR") {
		cout << "RR " << tq << "\n";
        while ( ! inFile.eof() )
			inFile >> process;
			inFile >> arrival;
			inFile >> bTimes;
			processq.insert(count, process);
			arrivalq.insert(count, arrival);
			bTimesq.insert(count,bTimes);
			count++;
		}
		RR(process,bTimes,arrival);
	}
	
	else if (format == "SRTF") {
		cout << "SRTF";
		cout << "SRTF " << tq << "\n";

        while ( ! inFile.eof() )
			inFile >> process;
			inFile >> arrival;
			inFile >> bTimes;
			processq.insert(count, process);
			arrivalq.insert(count, arrival);
			bTimesq.insert(count,bTimes);
			count++;
		}
		SRTF(process,bTimes,arrival);
	}
	
	else if (format == "FCFS") {
		cout << "FCFS";
		cout << "FCFS " << tq << "\n";
        while ( ! inFile.eof() )
			inFile >> process;
			inFile >> arrival;
			inFile >> bTimes;
			processq.insert(count, process);
			arrivalq.insert(count, arrival);
			bTimesq.insert(count,bTimes);
			count++;
		}
		FCFS(process,bTimes,arrival);
	}
	else {
		cout << "Error";
}


