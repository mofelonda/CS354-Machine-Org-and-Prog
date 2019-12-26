/*
* Name: Mo Felonda
*/

#include <stdio.h>

int arr[3000][500];

int main(int argc, const char * argv[]) {
	int row,col;

	for (col = 0; col < 500; col++) {
		for (row = 0; row < 3000; row++) {
            		arr[row][col] = row + col;
        	}
	}
return 0;
}
