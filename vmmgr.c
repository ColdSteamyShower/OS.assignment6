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
//#include <unistd.h>

// separate code
#include "extractAddress.c"
#include "data.c"

// globals
#define BUFFER_SIZE 8

/////////////////////////
// Main Function Start //
/////////////////////////
  int main(int argc, char* argv[])
  {
    // check to make sure the file is run correctly
    if (argc != 2) {
        printf("Usage Error: ./vmmgr.c <addresses file>\n");
        exit(1);
    }


    // create file streams to read from
    FILE *backingStore = fopen("BACKING_STORE.bin", "r");
    if (backingStore == NULL){
      perror("Error locating BACKING_STORE.bin\n");
      exit(1);
    }

    FILE *addressFile = fopen(argv[1], "r");
    if (addressFile == NULL){
      perror("Error locating address file: File not found\n");
      exit(1);
    }

    FILE *output = fopen("VM Report.txt","w");
    if (addressFile == NULL){
      perror("Error opening output file \"VM Report.txt\". Unable to send statistics\n");
      exit(1);
    }

    // initialize page Table
    for(int i=0 ; i < NUM_PAGES ; ++i){
      pageTable[i] = -1;
    }

    //hit/miss rate counter
    int addressReads = 0;
    int tlbHits = 0;
    int pageFaults = 0;


    // loop until we hit EOF of address file
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, addressFile))
    {
      //sleep(1);
      ++addressReads;

    // get data from the integer
      unsigned vAddress = atoi(buffer);
      unsigned page = getPage(vAddress);
      unsigned offset = getOffset(vAddress);
      // Got page


    // Try TLB
      unsigned pFrame = tlbCheck(page);
      if (pFrame == -1){
      ///// TLB miss -> get from page table and add to TLB
        pFrame = pageTable[page];

        // if the page is unassigned, we have a page fault!
        if (pFrame == -1){
          ++pageFaults;

          // physical address set to next available frame on physical memory
          pFrame = nextFrame;
          nextFrame++;


          // copy data from disk to physical memory
          signed char *pageTablePointer = &mainMemory[pFrame*FRAME_SIZE];
          fseek(backingStore, (page*FRAME_SIZE), SEEK_SET);
          fread(pageTablePointer, sizeof(char), FRAME_SIZE, backingStore);
          pageTable[page] = pFrame;
        }
        // got frame

        // add page and frame to TLB
        tlbPush(page, pFrame);

      } else {
      ///// TLB hit, we got the address quickly from the TLB
        ++tlbHits;
        // no TLB changes
      }

      // report information
      // to console
      printf("\33[32m Reading Address \33[33m#%d\n", addressReads);
      printf("\33[32m Virtual Page: \33[33m%d \33[32m--- Physical Frame: \33[33m%d \33[32m--- Offset: \33[33m%d\n", page, pFrame, offset);
      printf("\33[32m Value at location: \33[33m%c\33[0m\n\n", mainMemory[pFrame*FRAME_SIZE + offset]);

      // to report file
      fprintf(output, "Address #%d: [Virtual Page %d] [Physical Frame %d] [Offset = %d] Resulted in Char: %c\n", addressReads, page, pFrame, offset, mainMemory[pFrame*FRAME_SIZE + offset]);
    }

    // final report
    // to console
    printf("\33[32mVirtual Memory Simulation Complete\n");
    printf("\33[32mAddresses Read: \33[33m%d\n", addressReads);
    printf("\33[32mTLB Hits: \33[33m%d/%d (%f\%)\n", tlbHits, addressReads, (tlbHits/(float)addressReads));
    printf("\33[32mPage Faults: \33[33m%d/%d (%f\%)\33[0m\n", pageFaults, addressReads, (pageFaults/(float)addressReads));

    // to report file
    fprintf(output, "\nVirtual Memory Simulation Complete\n Addresses Read: %d\n TLB Hits: %d/%d (%f\%)\n Page Faults: %d/%d (%f\%)\n", addressReads, tlbHits, addressReads, (tlbHits/(float)addressReads), pageFaults, addressReads, (pageFaults/(float)addressReads));

    // cleanup
    fclose(backingStore);
    fclose(addressFile);
    fclose(output);
  };
