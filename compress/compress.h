#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG if(0)

extern int FreqCounter[256];

//conta a quantidade de repetição de cada caractere
void count_rep(char *fileName);

void printFrequency(int array[256]);
