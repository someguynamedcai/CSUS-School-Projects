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

int pnum, frames, preq,page, pfault;
ifstream inFile;
ifstream inFile2;
ifstream inFile3;
ifstream inFile4;

void FIFO(int frameq[]) {
	int done = 0;
	int count = 0;
	int fnum = 0;
	int FIFO = 0;
	int check = -1;
	//Reset array
	for (int i = 0; i < frames; i++) {
			frameq[i] = -1;
	}
	while (done != 1) {
		inFile >> page;
		for (int i = 0; i < frames; i++) {
			if (page == frameq[i]) {
				check = i;
				break;
			}
		}
		if (count > frames & check == -1) {
			cout << "Page " << frameq[FIFO] << " unloaded from Frame " << FIFO << ", Page " << page << " loaded into Frame " << FIFO << "\n";
			frameq[fnum] = page;
			fnum++;
			FIFO++;
			pfault++;
		}
		else if (check != -1) {
			cout << "Page " << page << " already in Frame " << check << "\n";
		}
		else {
			frameq[fnum] = page;
			cout << "Page " << page << " loaded into Frame " <<  fnum << "\n";
			fnum++;
			pfault++;
		}
		count++;
		if (count > frames && fnum == frames) {
			fnum = 0;
		}
		if (FIFO == frames) {
			FIFO = 0;
		}
		check = -1;
		if (count == preq) done = 1;
	}
	cout << "Page faults : " << pfault << "\n";
	inFile.close();
}
void OPT() {
	int done = 0;
	int count = 0;
	int fnum = 0;
	int check = -1;
	int next = 0;
	int time = 0;
	int best = 0;
	int hightime = 0;
	pfault = 0;
	int OPTIMAL[frames];
	int FUTURE[frames];
	inFile3 >> page >> page >> page;
	inFile4 >> next >> next >> next;
	for (int c = 0; c < frames; c++) {
		OPTIMAL[c] = -1;
		FUTURE[c] = 100000;
	}
	while (done != 1) {
		inFile3 >> page;
		inFile4 >> next;
		for (int i = 0; i < frames; i++) {
			if (page == OPTIMAL[i]) {
				check = i;
				break;
			}	
		}
		if (count > frames & check == -1) {	
			for (int fut = 0; fut < preq - count - 1; fut++) {
				inFile4 >> next;
				for (int fut2 = 0; fut2 < frames; fut2++) {
					if (next == OPTIMAL[fut2]) {
						FUTURE[fut2] = time;
					}
				}
				time++;	
			}
			
			for (int sort = 0; sort < frames; sort++) {
				if (hightime < FUTURE[sort]) {
					hightime = FUTURE[sort];
					best = sort;
				}
			}
			cout << "Page " << OPTIMAL[best] << " unloaded from Frame " << best << ", Page " << page << " loaded into Frame " << best << "\n";
			OPTIMAL[best] = page;
			fnum++;
			pfault++;
			for (int reset = 0; reset < frames; reset++) {
				FUTURE[reset] = 10000;
			}
			inFile4.close();
			inFile4.open("input.txt");
			for (int resetif = 0; resetif < count+4; resetif++) {
				inFile4 >> best;
			}
			hightime = 0;
			best = 0;
			time = 0;
		}
		else if (check != -1) {
			cout << "Page " << page << " already in Frame " << check << "\n";
				OPTIMAL[fnum] == page;
		}
		else {
			OPTIMAL[fnum] = page;
			cout << "Page " << page << " loaded into Frame " <<  fnum << "\n";
			OPTIMAL[fnum] = page;
			fnum++;
			pfault++;
		}
		count++;
		if (count > frames && fnum == frames) {
			fnum = 0;
		}
		check = -1;
		if (count == preq) done = 1;
	}
	cout << "Page faults : " << pfault << "\n";
	inFile3.close();
	inFile4.close();
}

void LRU() {
	int done = 0;
	int count = 0;
	int fnum = 0;
	int check = -1;
	int time = 0;
	int ctime = 0;
	int cpage = 0;
	int cf = 0;
	int LRU[2][frames];
	pfault = 0;
	for (int c = 0; c < frames; c++) {
		LRU[0][c] = -1;
		LRU[1][c] = -1;
	}
	
	while (done != 1) {
		inFile >> page;
		for (int i = 0; i < frames; i++) {
			if (page == LRU[0][i]) {
				check = i;
				break;
			}
		}
		if (count > frames & check == -1) {
			ctime = 0;
			for (int a = 0; a < frames; a++) {
				if (LRU[1][a] > ctime) {
					ctime = LRU[1][a];
					cpage = LRU[0][a];
					cf = a;
				}
			}
			cout << "Page " << cpage << " unloaded from Frame " << cf << ", Page " << page << " loaded into Frame " << cf << "\n";
			LRU[1][cf] = 0;
			LRU[0][cf] = page;
			fnum++;
			pfault++;
		}
		else if (check != -1) {
			cout << "Page " << page << " already in Frame " << check << "\n";
			LRU[1][check] = 0;
		}
		else {
			LRU[0][fnum] = page;
			LRU[1][fnum] = 0;
			cout << "Page " << page << " loaded into Frame " <<  fnum << "\n";
			fnum++;
			pfault++;
		}
		count++;
		if (count > frames && fnum == frames) {
			fnum = 0;
		}
		
		check = -1;
		
		//Time counter 
		for (int t = 0; t < frames; t++) {
			LRU[1][t]++;
		}
		
		if (count == preq) done = 1;
	}
	cout << "Page faults : " << pfault << "\n";
	inFile.close();
}

int main(int argc, char *argv[]){
	int i = 0;
	int frameq[frames];
	string format;
	FILE *fptr;
	string file;
	
	if(argc > 3){
		fprintf(stderr, "Invalid number of arguments!\n");
		exit(-1);
	}
	else {
		format = argv[2];
		file = argv[1];
		inFile.open(file.c_str());
		inFile2.open(file.c_str());
		inFile3.open(file.c_str());
		inFile4.open(file.c_str());

		fptr = fopen(file.c_str(),"r");		
	}
	
	if (format == "FIFO") {
		cout << "FIFO" << "\n";
		inFile >> pnum;
		inFile >> frames;
		inFile >> preq;
		FIFO(frameq);
	}
	
	else if (format == "LRU") {
		cout << "LRU" << "\n";
		inFile >> pnum;
		inFile >> frames;
		inFile >> preq;
		LRU();
	}
	
	else if (format == "OPT") {
		cout << "OPT" << "\n";
		inFile >> pnum;
		inFile >> frames;
		inFile >> preq;
		OPT();
	}
	else {
		cout << "Error\n";
	}
}

