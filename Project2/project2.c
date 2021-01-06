/*****************************************************************************************
 * Name  : Milan Bui
 * Date  : 21 Nov 2020
 * Class : CS 2600
 * File  : project2.c
 * Project 2 :
 *      Program reads in a space-delimited file, build an array of structs, and prints out
 *      a sorted report. 
 *      File format   >> word count rank
 *      Output format >> count : word (rank)
 ****************************************************************************************/ 
#include "myFunctions.h" // contains struct, parseFile(), and sort(), stdlib.h, stdio.h, 
			 // fcntl.h, and unistd.h

int main() {
	// Variables
	int BUFF_SIZE = 100;
	char inFileName[]  = "input.txt";
	char outFileName[] = "project2.output";

	struct wordStats words[5000];		// Array of structs containing word, count,
						// and rank
	char buffer[BUFF_SIZE];
	int index = 0;				// Index to iterate through buffer
	int bytes;				// Number of bytes written 
	int outFileFd;
	int recordsRead;
	int results;				// Results of file functions

	// Opens output file and checks for error
	outFileFd = open( outFileName, O_WRONLY | O_CREAT | O_TRUNC, 0600 );
	
	if ( outFileFd < 0 ) {
		printf( "Error opening \"%s\".\n", outFileName );
		return 1;
	}

	// Parses the file and returns # records read or -1 if there was an error
	recordsRead = parseFile( words, inFileName );

	if( recordsRead == -1 ) {
		return 1;
	}
	
	// Sorts the records read
	sort(words, recordsRead);

	// Formats the string and writes to output file, checking for errors
	bytes = sprintf(buffer, "Records read in : %i\n", recordsRead );
	results = write( outFileFd, buffer, bytes);
	if( results <= 0 ) {
		printf("Error writing bytes.\n");
		return 1;
	}

	// Formatting record information and writing to output file, checking for errors
	index = 0;
	
	while ( index < recordsRead ) {
		
		bytes = sprintf(buffer, "%10i : %s (%i)\n", words[index].count, 
				words[index].word, words[index].rank);

		results = write( outFileFd, buffer, bytes );
		if( results <= 0 ) {
			printf("Error writing bytes.\n");
			return 1;	
		}

		index++;

	}
	
	// Closes output file, checks for error
	if( close( outFileFd ) < 0 ) {
		printf( "Error closing \"%s\".\n", outFileName );
		return 1;
	}	

	// Return 0 -> complete run without errors.	
	return 0;
}
