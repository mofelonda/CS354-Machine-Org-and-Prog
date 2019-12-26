////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        division.c
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

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>

int successes = 0;

/* Signal Handler
 * 
 * Case 1: SIGFPE: Attempts to divide by 0. Prints error message, prints number
 * 	of successfully completed division operations, then gracefully terminates
 * 	instead of crashing.
 *
 * Case 2: SIGINT: Receives signal, prints number of successfully completed
 * 	division operations, then terminates.
 *
 * signal: denotes signal type
 * act: pointer to first sigaction struct
 * nullact: pointer to second sigaction struct
 */
static void signalHandler(int signal, siginfo_t *act, void *nullact) {
	switch (signal) {
		case SIGFPE:
			printf("Error: a division by 0 operation was attempted.\n");
			printf("Total number of operations completed successfully: %d\n", successes);
			printf("The program will be terminated.\n");
			exit(0);
		case SIGINT:
			printf("\nTotal number of operations successfully completed: %d\n", successes);
			printf("The program will be terminated.\n");
			exit(0);
	}
}

/* Main Function
 * 
 * Runs an infinite loop that:
 * 	Prompts the user for two integer values,
 * 	returns their quotient and remainder,
 * 	keeps count of how many divisions were successfully completed,
 * 	handles divide-by-zero errors (SIGFPE),
 * 	and handles Ctrl-C input (SIGINT).
 */
int main (int argc, const char *argv[]) {
	struct sigaction act, nullact;
	int buffSize = 100;
	char buffer[buffSize];
	int dividend;
	int divisor;
	int quotient;
	int remainder;

	memset (&act, 0, sizeof(act));
	act.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = signalHandler;

	// Divide-by-zero error signal
	if (sigaction(SIGFPE, &act, &nullact) < 0) {
		perror("Error handling signal");
		exit(0);
	}

	// Ctrl-C keyboard signal
	if (sigaction (SIGINT, &act, &nullact) < 0) {
		perror ("Error handling signal");
		exit(0);
	}

	// Run infinite loop
	while (1) {

		// Prompt for and retrieve both integer values
		printf("Enter first integer: ");
		if (fgets(buffer, buffSize, stdin) != NULL) {
			dividend = atoi(buffer);
		}
		printf("Enter second integer: ");
		if (fgets(buffer, buffSize, stdin) != NULL) {
			divisor = atoi(buffer);
		}

		// Calculate quotient and remainder
		quotient = dividend / divisor;
		remainder = dividend % divisor;

		// Print results
		printf("%d / %d is %d with a remainder of %d\n", dividend, divisor, quotient, remainder);

		// Increment successfully completed divisions
		successes++;
	}
	return 0;
}
