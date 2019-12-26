////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      sendsig.c division.c
// Semester:         CS 354 Spring 2019
//
// Author:           Mo Felonda
// Email:            felonda@wisc.edu
// CS Login:         felonda
//           
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//           
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//           
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>

// So alarm goes off after 3 seconds
int threeSec = 3;
// Tally of SIGUSR1 receptions
int usr1count = 0;

/* Signal Handler
 *
 * Case 1: SIGALARM: Prints PID and time and re-arms alarm
 *	
 * Case 2: SIGUSR1: Tallies SIGUSR1 receptions
 *
 * Case 3: SIGINT (Ctrl-C): Prints SIGUSR1 tally and exits
 *
 * signal: denotes signal type
 * act: pointer to first sigaction struct
 * nullact: pointer to second sigaction struct
 */
static void signalHandler(int signal, siginfo_t *act, void *nullact) {
	time_t currTime;

	switch (signal) {
		case SIGALRM: 
			if (time(&currTime) == -1) {
				perror("Time error");
				exit(0);
			}
			printf("PID: %d | Current Time: %s", getpid(), ctime(&currTime));
			if (alarm(threeSec) != 0) {
				printf("Alarm error.\n");
				exit(0);
			}
			return;
		case SIGUSR1:
			usr1count++;
			printf("SIGUSR1 caught!\n");
			return;
		case SIGINT:
			printf("\nSIGINT received.\n");
			printf("SUGUSR1 was received %d times. Exiting now.\n", usr1count);
			exit(0);
	}
}

/* Main Function
 *
 * Runs an infinite loop that can be terminated with Ctrl-C
 * Handles SIGALRM, SIGUSR1, and SIGINT signals
 */
int main(int argc, const char *argv[]) {

	// Welcome message
        printf("Pid and time will be printed every 3 seconds.\n");
        printf("Enter ^C to end the program.\n");

	struct sigaction act, nullact;
	memset(&act, 0, sizeof(act));
	act.sa_flags = 0;
	act.sa_sigaction = signalHandler;

	// When signals are received, pass to signalHandler
	if (sigaction(SIGALRM, &act, &nullact) < 0) {
		perror ("Error handling signal");
		exit(0);
	}
	if (sigaction(SIGUSR1, &act, &nullact) < 0) {
		perror ("Error handling signal");
		exit(0);
	}
	if (sigaction(SIGINT, &act, &nullact) < 0) {
		perror ("Error handling signal");
		exit(0);
	}

	// Set alarm to send signal every 3 seconds
	if (alarm(threeSec) != 0) {
		printf("Alarm error.\n");
		exit(0);
	}

	// Run infinite loop
	while (1){
	}

	return 0;
}
