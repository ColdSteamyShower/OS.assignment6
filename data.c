
//////////////////////////////////////
// TLB (Translation Look-aside Buffer)
//     Creates a TLb named 'tlb' and provides check and push functionality

  #define TLB_SIZE 16     // assignment calls for 16 TLB entries

  struct tlbEntry {
    int page;  // virtual memory address
    int frame; // physical memory address
  };

  struct tlbEntry tlb[TLB_SIZE];
  int tlbIndex = 0;

  // takes a page number and returns a frame number if page is on TLB
  // returns -1 if TLB miss
  int tlbCheck(unsigned page)
  {
    for (int i=0 ; i < TLB_SIZE ; ++i)
    {
      if (tlb[i].page == page){
        return tlb[i].frame;
      }
    }
    return -1;
  }

  // Adds page to TLB under FIFO
  // no return
  void tlbPush(unsigned page, unsigned frame)
  {
    tlb[tlbIndex].page = page;
    tlb[tlbIndex].frame = frame;
    tlbIndex = (tlbIndex + 1) % TLB_SIZE;
  }

//
//////////////////////////////////////

//////////////
// Page Table
//

  #define NUM_PAGES 256   // assignment calls for 2^8 page table entries

  int pageTable[NUM_PAGES]; // assignment calls for a page table with 2^8 entries



//
//////////////

///////////////////
// Physical Memory
//    Assignment demands 256*256 bytes of physical memory in 256 frames of 256 bytes each

  #define NUM_FRAMES 256
  #define FRAME_SIZE 256

  // we will find the signed byte at locations in the memory, so we will simulate it with a signed char (which is size of 1 byte)
  signed char mainMemory[NUM_FRAMES*FRAME_SIZE];

  // keep track of next free frame
  int nextFrame = 0;

//
///////////////////
