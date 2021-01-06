/*****************************************************************************************
 * File       : myFunctions.c
 * Assignment : Project 2
 ****************************************************************************************/
#include <stdio.h>  // printf
#include <stdlib.h> // atoi
#include <fcntl.h>  // open, mode
#include <unistd.h> // read, close

struct wordStats {
	char word[100];
	int  count;
	int  rank;
};

/* 
 * Parses space delimited file with three fields per line, corresponding to fields in
 * struct wordStats. 
 * Returns the number of lines/records read or -1 if an error occurred 
 */
int parseFile(struct wordStats words[], char *inFileName) {
	
	int BUFF_SIZE = 100;
	int INT_SIZE  = sizeof(int);

	char buffer[ BUFF_SIZE ];
	char integer[ INT_SIZE ];

	int segment = 0;
	int segmentIndex = 0;
	int recordIndex  = 0;

	int bytesRead;
	int inFileFd;

	// Opens input file with given name
	inFileFd = open( inFileName, O_RDONLY );
	if( inFileFd < 0 ) {
		printf( "Error opening \"%s\".\n", inFileName );
		return -1;
	}

	// Reads input file and parses >> storing information in array of structs of type wordStats	
	bytesRead = read( inFileFd, buffer, BUFF_SIZE );
	while( bytesRead != 0 ) {

		for( int index = 0; index < bytesRead; index++ ) {
			char tempChar = buffer[ index ];

			// If space or end of line, add null to end of field and store.
			// Increments/resets necessary variables
			if( tempChar == ' ' || tempChar == '\n' ) {
				if( segment % 3 == 0 ) {
					words[ recordIndex ].word[ segmentIndex ] = '\0';

					segmentIndex = 0;
					segment++;
				}
				else if( segment % 3 == 1 ) {
					integer[ segmentIndex ] = '\0';
					words[ recordIndex ].count = atoi( integer );

					segmentIndex = 0;
					segment++;
				}
				else if( segment % 3 == 2 ) {
					integer[ segmentIndex ] = '\0';
					words[ recordIndex ].rank = atoi( integer );

					segment = 0;
					segmentIndex = 0;
					recordIndex++;
				}
			}
			else {
				if( segment % 3 == 0 ) {
					words[ recordIndex ].word[ segmentIndex++ ] = tempChar;
				}
				else if( segment % 3 == 1 || segment % 3 == 2) {
					integer[ segmentIndex++ ] = tempChar;
				}
			}
		}

		bytesRead = read( inFileFd, buffer, BUFF_SIZE );
	}

	// Closes file
	if( close( inFileFd ) < 0 ) {
		printf( "Error closing \"%s\".\n", inFileName );
		return -1;
	}

	return recordIndex;
				 
}


// Sorts array of structs of given size. (bubble sort)
void sort(struct wordStats *words, int size) {
	struct wordStats temp;

	// Iterates from end of array
	for ( int i = size - 1; i >= 0; i-- ) {

		for ( int j = i - 1; j >= 0; j-- ) {
			// if this element count is larger than the previous element
			// or if count is equal and this rank is higher than previous item's rank
			// swap 
			if( words[i].count > words[j].count || 
				( words[i].count == words[j].count && 
				words[i].rank < words[j].rank) ) {

				temp = words[i];
				words[i] = words[j];
				words[j] = temp;
			}
		}
	}	
}
