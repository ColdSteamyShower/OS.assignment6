/*
Operating Systems: Assignment 6
Michael Kulinich
kulinich@chapman.edu

Ayden Best
bbest@chapman.edu

CPSC 380-01
*/

// library dependencies
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// separate code
#include "extractAddress.c"

// constants
#define NUM_PAGES 256 // also number of frames
#define PAGE_SIZE 256 // also size of frames
#define MAX_MEM 65536

// global objects



// main function start
int main(int argc, char* argv[])
{
  int testingValues[7];
  testingValues[0] = 1;
  testingValues[1] = 256;
  testingValues[2] = 32768;
  testingValues[3] = 32769;
  testingValues[4] = 128;
  testingValues[5] = 65534;
  testingValues[6] = 33555;

  for (int i=0 ; i<7 ; ++i)
  {
    printf("Value %d: Page %d, Offset %d\n",i+1,getPage(testingValues[i]),getOffset(testingValues[i]));
  }
};
