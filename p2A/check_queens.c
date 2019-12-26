////////////////////////////////////////////////////////////////////////////////
// Main File:        check_queens.c
// This File:        check_queens.c
// Other Files:      n/a
// Semester:         CS 354 SPRING 2019
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
#include <stdlib.h>  
#include <string.h>   
 
char *COMMA = ",";
  
/* COMPLETED:
 * Retrieves from the first line of the input file,
 * the number of rows and columns for the board.
 * 
 * fp: file pointer for input file
 * rows: pointer to number of rows
 * cols: pointer to number of columns
 */
void get_dimensions(FILE *fp, int *rows, int *cols) {  
        char *line = NULL;  
        size_t len = 0;  
        if (getline(&line, &len, fp) == -1) {  
                printf("Error in reading the file\n");  
                exit(1);  
        }  
           
        char *token = NULL; 
        token = strtok(line, COMMA);
        *rows = atoi(token); 
           
        token = strtok(NULL, COMMA); 
        *cols = atoi(token);
}      


/* Returns 1 if and only if there exists at least one pair
 * of queens that can attack each other.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * rows: number of rows
 * cols: number of columns
 */
int check_queens(int **board, int rows, int cols) {
       	int queen = 0;	
	// This for loop checks for pairs of queens in the
	// same column. Returns true if there is a pair.
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(*(*(board+i)+j) == 1) {
				queen++;
			}
			if(queen >= 2)	{
				printf("true\n");
				return 1;
			}
		}
		queen = 0;
	}
	// This for loop checks for pairs of queens in
	// the same row. Returns true if there is a pair.
        for(int j = 0; j < cols; j++) {
                for(int i = 0; i < rows; i++) {
                        if(*(*(board+i)+j) == 1) {
                                queen++;
                        }
                        if(queen >= 2) {
                                printf("true\n");
                                return 1;
                        }
                }
		queen = 0;
        }
	// This for loop checks for pairs of queens in the
	// same diagonal. Returns true if there is a pair.
	// This function was returning a segmentation fault
	// so it has been commented out; I left it because
	// I'd like to return to it later
/*	for(int k = 0; k <= rows + cols - 2; k++) {
		for(int j = 0; j <= k; j++) {
			int i = k - j;
			if(i < cols && j < rows) {
				if(board[i][j] == 1) {
                                	queen++;
                        	}
                        	if(queen >= 2) {
                                	printf("true\n");
                                	return 1;
				}
			}
			queen = 0;
		}
	}
	// Creates a transposed version of the 2D array
	int **backwardsboard = (int**)malloc(rows * sizeof(int*));
        for(int i = 0; i < rows; i++) {
                backwardsboard[i] = malloc(sizeof(int) * cols);
        }

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			backwardsboard[(rows-1)-i][j] = board[j][i];
		}
	}
	// Checks for pairs of queens diagonally in the
	// transposed 2D array
	for(int k = 0; k <= rows + cols - 2; k++) {
                for(int j = 0; j <= k; j++) {
                        int i = k - j;
                        if(i < cols && j < rows) {
                                if(backwardsboard[i][j] == 1) {
                                	queen++;
                        	}
                        	if(queen >= 2) {
                                	printf("true\n");
                                	return 1;
                        	}
                	}
                	queen = 0;
        	}
	}*/
	// This function compares each array by their subsets to
	// find pairs of queens in a diagonal position. Returns true
	// if a pair is found.
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(*(*(board+i)+j) == 1){
				for(int a = 0; a < rows; a++){
					for(int b = 0; b < cols; b++){
						if(*(*(board+a)+b) == 1 && a != i && b != j){
							int rowsSubset = i - a;
                                                        int colsSubset = j - b;
                                                        if(rowsSubset == colsSubset){
                                                        	printf("true\n");
                                                                return 1;
							}
						}
					}
				 }
			}
		}
	}
	printf("false\n");
        return 0;
}     


/* This program prints true if the input file has any pair
 * of queens that can attack each other, and false otherwise
 * 
 * argc: CLA count
 * argv: CLA value 
 */
int main(int argc, char *argv[]) {        

        // Checks if number of command-line arguments is correct.
        if(argc != 2) {
		printf("Usage: ./check_queens <input_filename>");
		exit(1);
	}

        //Open the file and check if it opened successfully.
        FILE *fp = fopen(*(argv + 1), "r");
        if (fp == NULL) {
                printf("Cannot open file for reading\n");
                exit(1);
        }


        //Declare local variables.
        int rows, cols;


        // Calls get_dimensions to retrieve the board dimensions.
	get_dimensions(fp, &rows, &cols);


        // Dynamically allocates a 2D array of dimensions retrieved above.
	int **board = (int**)malloc(rows * sizeof(int*));
	for(int i = 0; i < rows; i++) {
		board[i] = malloc(sizeof(int) * cols);
	}
        

        //Read the file line by line.
        //Tokenize each line wrt comma to store the values in your 2D array.
        char *line = NULL;
        size_t len = 0;
        char *token = NULL;
        for (int i = 0; i < rows; i++) {

                if (getline(&line, &len, fp) == -1) {
                        printf("Error while reading the file\n");
                        exit(1);        
                }

                token = strtok(line, COMMA);
                for (int j = 0; j < cols; j++) {
                        // Initializes 2D array.
                        *(*(board+i)+j) = atoi(token);
                        token = strtok(NULL, COMMA);    
                }
        }

        // Calls the function check_queens and prints the appropriate
        // output depending on the function's return value.
	check_queens(board, rows, cols);
        
        
	// Frees memory allocated for 2D array
	for(int i = 0; i < rows; i++) {
		free(board[i]);
	}
	free(board);
		


        //Close the file.
        if (fclose(fp) != 0) {
                printf("Error while closing the file\n");
                exit(1);        
        }

        return 0;
}      
