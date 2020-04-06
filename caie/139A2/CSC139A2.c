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

void RR(int timequantum, vector<int> process, vector<int> bTimes,vector<int> arrival){
	int time = 0;
	int done = 0;
	int count = 0;
	vector<int> queue;
	vector<int> obTimes = bTimes;
	float cputime = 0;
	float waittime = 0;
	float responsetime = 0;
	float turnaroundtime = 0;	
	while (done != process.size()) {
		for (int i = 0; i < arrival.size(); i++) {
			if (arrival[i] == time) {
				queue.push_back(process[i]);
				count++;
				//cout << "Process " << (queue[i] + 1) << " in spot " << count << "\n";
			}
		}
		if (queue.size() > 0) {
			if (bTimes[(queue[0])] == 0) {
				done ++;
				if (done != process.size()) {
					waittime = waittime + time;
				}
				done++;
				turnaroundtime = turnaroundtime + (time - arrival[count]);
				cout << "Removed Process " << queue[0] + 1 << "\n";
				if (queue.size() == 1) {
					break;
				}
				else {
					queue.erase(queue.begin());
				}
			}
			else {
				if (time != 0) {
					if (bTimes[queue[0]] == obTimes[queue[0]] - 1) {
						responsetime = responsetime + time;
					}
					bTimes[queue[0]] --;
					cout << "Process " << (queue[0] + 1) << " Time: " << time << " | " << bTimes[queue[0]] << " left\n" ;
				}
			}	
		}
		if (time % timequantum == 0 && time > 0) {
			if (bTimes[(queue[0])] == 0) {
				done ++;
				if (done != process.size()) {
					waittime = waittime + time;
				}
				done++;
				turnaroundtime = turnaroundtime + (time - arrival[count]);
				cout << "Removed Process " << queue[0] + 1 << "\n";
				if (queue.size() == 1) {
					break;
				}
				else {
					queue.erase(queue.begin());
				}
			}
			queue.push_back(queue[0]);
			queue.erase(queue.begin());
			cout << "Switch Process \n";
		}
		time++;
	}
	cout << "Average cpu usage: 100%\n";
	cout << "Average waiting time: " << waittime << "\n";
	cout << "Average response time: " << responsetime << "\n";
	cout << "Average turnaround time: " << turnaroundtime << "\n";
}

void SRTF(vector<int> process, vector<int> bTimes, vector<int> arrival){
	int time = 0;
	int done = 0;
	int count = 0;
	vector<int> queue;
	float cputime = 0;
	float waittime = 0;
	float responsetime = 0;
	float turnaroundtime = 0;	
	while (done != 	process.size()) {
		for (int i = 0; i < arrival.size(); i++) {
			if (arrival[i] == time) {
				queue.push_back(process[i]);
				cout << "Process " << (queue[i] + 1) << " in spot " << queue.size() << "\n";
				count++;
			}
			if (queue.size() > 1) {
				for (int j = 0; j < queue.size(); j++) {
					for (int k = j; k < queue.size(); k++) {
						if (bTimes[queue[j]] > bTimes[queue[k+1]]) {
							cout << "Moved Process " << queue[j] + 1 << " to end\n";
							cout << "Process " << queue[k+1] + 1 << " to front\n";
							queue.push_back(queue[j]);
							queue.insert(queue.begin(), queue[k+1]);
							queue.erase(queue.begin());
							queue.resize(process.size());
							break;
						}
					}
				}
			}
		}
		if (queue.size() > 0) {
			if (bTimes[(queue[0])] == 0) {
				done ++;
				if (done != process.size()) {
					waittime = waittime + time;
				}
				done++;
				turnaroundtime = turnaroundtime + (time - arrival[count]);
				cout << "Removed Process " << queue[0] + 1 << "\n";
				if (queue.size() == 1) {
					break;
				}
				else {
					queue.erase(queue.begin());
				}
			}
			else {
				if (time != 0) {
					bTimes[queue[0]] --;
					cout << "Process " << (queue[0] + 1) << " Time: " << time << " | " << bTimes[queue[0]] << " left\n" ;
				}
			}	
		}
		time++;
	}
	cout << "Average cpu usage: 100%\n";
	cout << "Average waiting time: " << waittime << "\n";
	cout << "Average response time: " << responsetime << "\n";
	cout << "Average turnaround time: " << turnaroundtime << "\n";
}
	

void FCFS(vector<int> process, vector<int> bTimes, vector<int> arrival) {
	int time = 0;
	int done = 0;
	int count = 0;
	vector<int> queue;
	vector<int> obTimes = bTimes;
	float cputime = 0;
	float waittime = 0;
	float responsetime = 0;
	float turnaroundtime = 0;	
	while (done != process.size()) {
		for (int i = 0; i < arrival.size(); i++) {
			if (arrival[i] == time) {
				queue.push_back(process[i]);
				count++;
				cout << "Process " << (queue[i] + 1) << " in spot " << count << "\n";
			}
		}
		if (queue.size() > 0) {
			if (bTimes[(queue[0])] == 0) {
				done ++;
				if (done != process.size()) {
					waittime = waittime + time;
				}
				done++;
				cout << "Switch Process \n";
				turnaroundtime = turnaroundtime + (time - arrival[queue[0]]);
				cout << "Removed Process " << queue[0] + 1 << "\n";
				if (queue.size() == 1) {
					break;
				}
				else {
					queue.erase(queue.begin());
				}
			}
			else {
				if (time != 0) {
					if (bTimes[queue[0]] == obTimes[queue[0]] - 1) {
						responsetime = responsetime + time;
					}
					bTimes[queue[0]] --;
					cout << "Process " << (queue[0] + 1) << " Time: " << time << " | " << bTimes[queue[0]] << " left\n" ;
				}
			}
		}
		time++;
	}
		
	waittime = waittime/ process.size();
	responsetime = responsetime/ process.size();
	turnaroundtime = turnaroundtime/ process.size();
	cout << "Average cpu usage: 100% \n";
	cout << "Average waiting time: " << waittime << "\n";
	cout << "Average response time: " << responsetime << "\n";
	cout << "Average turnaround time: " << turnaroundtime << "\n";
}

int main(int argc, char *argv[]){
	int i = 0;
	int tq;
	int pnum;
	string format;
	int count = 0;
	FILE *fptr;
	string file;
	int process;
	int arrival;
	int bTimes;
	vector<int> processq;
	vector<int> arrivalq;
	vector<int> bTimesq;
	if(argc > 4){
		fprintf(stderr, "Invalid number of arguments!\n");
		exit(-1);
	}
	else {
		if (argc == 4) {
			tq = atoi(argv[3]);
		}
		format = argv[2];
		file = argv[1];
	}
	ifstream inFile(file.c_str());
	fptr = fopen(file.c_str(),"r");
	if (format == "RR") {
		cout << "RR " << tq << "\n";
        while ( ! inFile.eof() ) {
			inFile >> process;
			inFile >> arrival;
			inFile >> bTimes;
			processq.push_back (process - 1);
			arrivalq.push_back(arrival);
			bTimesq.push_back(bTimes);
		}
		processq.pop_back();
		arrivalq.pop_back();
		bTimesq.pop_back();
		RR(tq, processq,bTimesq,arrivalq);
		inFile.close();
	}
	
	else if (format == "SRTF") {
		cout << "SRTF\n";
        while ( ! inFile.eof() ) {
			inFile >> process;
			inFile >> arrival;
			inFile >> bTimes;
			processq.push_back(process - 1);
			arrivalq.push_back(arrival);
			bTimesq.push_back(bTimes);

		}
		processq.pop_back();
		arrivalq.pop_back();
		bTimesq.pop_back();
		SRTF(processq,bTimesq,arrivalq);
		inFile.close();
	}
	
	else if (format == "FCFS") {
		cout << "FCFS\n";
		while ( ! inFile.eof() ) {
			inFile >> process;
			inFile >> arrival;
			inFile >> bTimes;
			processq.push_back (process - 1);
			arrivalq.push_back(arrival);
			bTimesq.push_back(bTimes);
		}
		processq.pop_back();
		arrivalq.pop_back();
		bTimesq.pop_back();
		FCFS(processq,bTimesq,arrivalq);
		inFile.close();
	}
	else {
		cout << "Error";	
	}
}


