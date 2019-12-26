////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        sendsig.c
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

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* Main Function
 *
 * Sends either SIGINT or SIGUSR1 given a PID and input from the user.
 */
int main(int argc, char *argv[]) {
	
	// Check number of command line arguments
	if (argc != 3) {
                printf("Usage: <signal type> <pid>\n");
		exit(0);
        }

	// Stores program ID
	int pid = atoi(argv[2]);

	// Stores signal to determine correct one to send
	int userStr = strcmp("-u", argv[1]);
	int userInt = strcmp("-i", argv[1]);

	// Checks argv and sends signal accordingly
	if (userInt == 0) {
		if (kill(pid, SIGINT) == -1) {
			perror("Error handling signal");
			exit(0);
		}
	}
	else if (userStr == 0) {
		if (kill(pid, SIGUSR1) == -1) {
			perror("Error handling signal");
			exit(0);
		}
	}
	else {
		perror("Invalid signal");
		exit(0);
	}
	return 0;
}
