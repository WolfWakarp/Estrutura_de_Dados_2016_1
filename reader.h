#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG if(0)

extern int FreqCounter[256];
extern unsigned char *file_string;

void count_rep(char *fileName);

void store_string(char *fileName);

void printFrequency(int array[256]);
