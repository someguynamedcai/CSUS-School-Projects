/* Author(s): Eric Cai and Victor Tram Section 3.
 * This is a csc60mshell.c
 * This program serves as a skeleton for starting for lab 8.
 * Student is required to use this program to build a mini shell
 * using the specification as documented in direction.
 * Date: Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

#define MAXLINE 80
#define MAXARGS 20
#define MAX_PATH_LENGTH 50

/* function prototypes */
void process_input(int argc, char **argv);
int parseline(char *cmdline, char **argv);
void handle_redir(int count, char *argv[]);
	
/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
int main(void)
{
   	char cmdline[MAXLINE];
   	char *argv[MAXARGS];
   	int argc;
   	int status;
   	pid_t pid;
   	char *dir;
   	char *dirv;
  	  /* Loop forever to wait and process commands */
    while (1) {
	/* Print your shell name: csc60mshell (m for mini shell) */
	printf("csc60mshell> ");
	fgets(cmdline, MAXLINE, stdin);

	/* Call parseline to build argc/argv: their limits declared above */
	argc = parseline(cmdline, argv);
	/* If user hits enter key without a command, continue to loop again at the beginning */
	if (argc == 0) {
		continue;
	}
	/*  Hint: if argc is zero, no command declared */
	/*  Hint: look up for the keyword "continue" in C */

	/* Handle build-in command: exit, pwd, or cd  */
	if (strcmp(*argv, "exit") == 0) {
		exit(0);
		continue;
	}
	else if (strcmp(*argv, "pwd") == 0) {
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("Error");
		else
			printf("%s\n",cwd);
		continue;
	}
	else if (strcmp(argv[0], "cd") == 0) {
		if (argc == 1)
			dir = getenv("HOME");
		else
			dir = argv[1];

		if (chdir(dir) != 0) {
			printf("The directory cannot be found\n");
			continue;
		}
		continue;
	}	
	/* Else, fork off a process */
	else {
		pid = fork();
	
       		switch(pid) {
		 	case -1:
				perror("Shell Program fork error");
	       			exit(1);
	    		case 0:	
			/* I am child process. I will execute the command, call: execvp */
				process_input(argc, argv);
				break;
	    	 	default:
			/* I am parent process */
				/*	if (runningInBackground == 1) {
					sigset_t newmask, oldmask;
					sigemptyset( &newmask );
					sigaddset( &newmask, SIGINT );
					sigprocmask(SIG_BLOCK, &newmask, &oldmask );
					nextJobNumber++;
					for (count = 0; count < sizeof(argv); count++) {
						
					job_number[count] = nextJobNumber;
					jobsRunning++;

					sigprocmask( SIG_SETMASK, &oldmask, NULL );
				*/
				if(wait(&status) == -1)
		  	  		perror("Shell Program error");
				else
		    			printf("Child returned status: %d\n",status);
					break;
		} /* end of the switch */
	}	
    } /* end of the while */
} /* end of main */
/* ----------------------------------------------------------------- */
/*                  parseline                                        */
/* ----------------------------------------------------------------- */
/* parse input line into argc/argv format */

int parseline(char *cmdline, char **argv) {
	int count = 0;
	char *separator = " \n\t";
 
	argv[count] = strtok(cmdline, separator);
	while ((argv[count] != NULL) && (count+1 < MAXARGS)) {
		argv[++count] = strtok((char *) 0, separator);
    	}		
	return count;
}
/* ----------------------------------------------------------------- */
/*                  process_input                                    */
/* ----------------------------------------------------------------- */
void process_input(int argc, char **argv) {
    /* Step 1: Call handle_redir to deal with operators:            */
    /* * < , or  >, or both                                         */
	handle_redir(argc,argv);
    /* Step 2: perform system call execvp to execute command        */
    /* Hint: Please be sure to review execvp.c sample program       */
	if (execvp(argv[0], argv) == 0) {                           
		printf("Completed");                                    
        	_exit(-1);                                                  
    	}                                                             
}
/* ----------------------------------------------------------------- */
void handle_redir(int count, char *argv[]) {
/* Put your code here.  See pseudo-code in assignment directions     */
	int fd;
	int fileID;
	int newFD;
	int boolean = 0;
	int symbol = 0;

	if (strcmp(argv[0], ">") == 0 || strcmp (argv[0], "<") == 0) {
		symbol = 1;
	}
	
	if (count > 3) {
		fprintf(stderr, "Too many arguments.\n");
		boolean = 1;
		*argv = NULL;
	}
	else if (argv[0] == NULL || symbol == 1) {
		fprintf(stderr, "No command given.\n");
		boolean = 1;
		*argv = NULL;
	}

	else if(count == 2 && argv[1] == NULL) {
		fprintf(stderr, "No file given.\n");
		boolean = 1;
		*argv = NULL;
	}
	else if (count == 3 && argv[2] == NULL) {
		fprintf(stderr, "No redirection file given.\n");
		boolean = 1;
		*argv = NULL;
	}
	if (boolean == 0 && count == 3) {
		fileID = creat(argv[2], 0640);
		if (fileID < 0) {
			fprintf(stderr, "Error creating file.\n");
			exit(1);
		}
		dup2(fileID, 1);
		close(fileID);
		execl("/bin/ls","ls",0);
		if (strcmp(argv[1],">")) {
			fd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC|S_IRUSR|S_IWUSR);
	    		printf("%i\n", fd);
	      		dup2(fd, 1);         
			close(fd); 
	                       		
	    	} 
                else if(strcmp(argv[1], "<")) {	    	   
			fd = open(argv[2], O_RDONLY);
			dup2(fd, 0);
			close(fd);
		}
		if (fd == -1) {
			fprintf(stderr, "Error upon opening. \n");
		}
		argv[1]= NULL;
		boolean = 0;
	}
}
/* ----------------------------------------------------------------- */
/* ----------------------------------------------------------------- */
