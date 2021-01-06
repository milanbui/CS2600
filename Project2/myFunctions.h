/*****************************************************************************************
 * File       : myFunctions.h
 * Assignment : Project 2
 ****************************************************************************************/
#include <stdio.h>  //printf
#include <stdlib.h> // atoi
#include <fcntl.h>  // open, mode
#include <unistd.h> // close, read

struct wordStats {
	char word[100];
	int  count;
	int  rank;
};

// Parses space delimited file with three fields corressponding to struct wordStats
// Returns lines read or -1 if there was error
int parseFile(struct wordStats words[], char *inFileName);

// Sorts array of structs of given size by count then by rank if needed
void sort(struct wordStats *words, int size); 
