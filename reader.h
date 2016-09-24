
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG if(1)

extern int FreqCounter[256];
extern unsigned char file_string[100000];

void countRep(char *fileName);

void store_string(char *fileName);

void printFrequency(int array[256]);
