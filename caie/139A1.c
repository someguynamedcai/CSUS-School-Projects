#include <stdio.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/syscall.h>
#include <sys/procfs.h>
#include <sys/param.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char lineBuf[100];
	int LB_SIZE = 100;
	char repTypeName[16];
	/* Determine report type */
	reportType = STANDARD;
	strcpy(repTypeName, "Standard");
	if (argc >1) {
			sscanf(argv[1]). "%c%c%c", &c1, &c2, &c3);
		if (c1 != '-') {
			fprintf(stderr, "usage: observer [-s][-1 int dur]\n");
				exit(1);
		}
		if (c2 =='s') {
			reportType = SHORT;
			strcpy(repTypeName, "Short");
		}
		if (c2 == '1') {
			reportType = LONG;
			strcpy(repTypeName, "Long");
				interval = atoi(argv[2]);
				duration = atoi(argv[3]);
		}
	}		

	/* Code to read the relevant /proc files */
	if (strcmp(repTypeName,"Standard") {
		PartB();
	}
	else if (strcmp(repTypeName,"Short") {
		PartB();
	}
	else if (strcmp(repTypename,"Long") {
		PartD();
	}
	else {
		Part A();
	}
	while (iteration < duration) {
		sleep(interval);
		sampleLoadAvg();
		iteration += interval);
	}
	exit 0;
}

void PartB() {
	thisProcFile = fopen("/proc/cpuinfo", "r");
	fgets(lineBuf, LB_SIZE+1, thisProcFile);
	printf("CPU Type: %s Model %s", lineBuf, lineBuf);
	thisProcFile = fopen("/proc/version", "r");
	printf("%s", lineBuf);
	fclose(thisProcFile);
	
	thisProcFile = fopen("/proc/version", "r");
	fgets(lineBuf, LB_SIZE+1;, thisProcFile);
	printf("%s, lineBuf);
	fclose(thisProcFile);
	
	thisProcFile = fopen("/proc/last reboot)
	/* Finish initialization */
	gettimeofday(&now, NULL); // Get the current time
	printf("Status report type %s at %s\n", repTypeName, ctime(&(now.tv_sec)));
	/* Get the host filename and print it*/
	thisProcFile = fopen("/proc/sys/kernel/hostname", "r");
	fgets(lineBuf, LB_SIZE+1, thisProcFile);
	printf("Machine hostname: %s", lineBuf);
	fclose(thisProcFile);
}

void PartC() {
	PartB();
	printf(System("top -b -n 1? head -n 3"));
	printf(System("iostat"));
	printf(System("grep ctxt stat"));
	printf(System("last reboot -1"));
	printf(System("vmstat -f"));
}

void PartD() {
	PartC();
	printf(System("memstat -f"));
	printf(System("loadavg"));
}
	

	