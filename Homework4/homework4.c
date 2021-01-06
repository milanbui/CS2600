/************************************************************************************************
 * Name  : Milan Bui
 * Date  : 16 Nov 2020
 * Class : CS2600
 * Assignmenti : Homework 4
 * Description : Prompts user for an integer until 1000 values have been entered or a value 
 *               outside the range of -1000 and 1000 inclusive (-1000 <= val <= 1000). Calculates
 *               the average of the values entered. Displays the number of values entered, the
 *               min and max, and the average.
 ************************************************************************************************/
#include <stdio.h>

void main() {
	// Variable declaration
	int count = 0;	// Number of integers entered
	int sum = 0;	// Sum of all integers entered
	int min;
	int max;
	int value;
	float avg;

	// PROC - prompts for input while value entered is between -1000 and 1000
	//        or until 1000 values have been entered.	
	do {
		// INPUT - prompts for input from user of an integer
		printf( "Enter a value: " );
		scanf( "%i", &value );

		if ( value >= -1000 && value <= 1000 ) {
	
			// Sets value of min and max	
			if ( count == 0 ) {
				min = value;
				max = value;
			}
			else if ( value < min ) {
				min = value;
			}
			else if ( value > max ) {
				max = value;
			}

			// Calculates sum of all valid integers entered
			sum = sum + value;

			// Increments
			count = count + 1;
		}
		
			 
	} while ( count < 1000 && (value >= -1000 && value <= 1000) );
	
	// Calculates average of values entered
	avg = ( sum * 1.0 ) / count;

	// OUTPUT - displays results
	printf( "\nNumber of values entered: %i\n", count );
	printf( "Minimum: %i\n", min );
	printf( "Maximum: %i\n", max );
	printf( "Average: %f\n", avg );

}
