#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG if(1)

extern int FreqCounter[256];

void countRep(char *fileName);

void printFrequency(int array[256]);
