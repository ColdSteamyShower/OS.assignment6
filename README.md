# Operating Systems: Assignment 6
Michael Kulinich
kulinich@chapman.edu

Ayden Best
bbest@chapman.edu

CPSC 380-01

## Task: Using Threads and Mutex/Conting Semaphores for the producer-consumer problem
The objective of this assignment consists of writing a C/C++ program that translates logical to physical addresses for a virtual address space of size 216 = 65,536 bytes. Your program will read from a file containing logical addresses and, using a TLB as well as a page table, will translate each logical address to its corresponding physical address and output the value of the byte stored at the translated physical address. The goal behind this project is to simulate the steps involved in translating logical to physical addresses.


## Assignment Notes
- Reading a list of 16-bit numbers, where the first 8 bits represent a page number 0-255, and the last 8 bits represent an offset 0-255
- Page Number is a virtual address that we will use to keep track of where memory is. We will have a page table as an array where an index is the page number, and the contents of that index are actual addresses in memory. We do this so we can use physical memory without necessarily having to put all memory of a program in one spot and potentially building fragmented memory that can't be used.
- Frames are the actual blocks in physical memory. A program's memory may be broken up sporadically across different frames on the physical memory, but the page table will let the program find its memory in order by telling the program where to look on the physical memory to access it's 1st, 2nd, 3rd, etc, chunks of memory.
- Offset is the address of a house if the page number was the street of a house. Once we get to the right frame, the offset will tell us where in that 256-bit chunk to look for our memory
- In a frame at a particular offset, we can expect to find some data. Print this.
- If we are reading a page that has not been read yet, that is called a page fault. We must open the .bin file and load up that page content. We then link that page to the next available frame in physical memory. From then on, any time we access that page, it is already on the page table and we can quickly look in physical memory. Looking in physical memory is more efficient than reading the disk, but our size is more limited so we should only put memory on it if the program asks for it, because it may ask for it again
- Program will start with many page faults, because we need to access pages that are not yet in memory and are only in the .bin file on the disk. After a while, we will continue accessing similar pages and can skip reading the disk by looking in physical memory. Physical memory faster than disk, but its size is more expensive
- On another scale, we can use a TLB. Its a smaller faster block of memory on the CPU. We can store recently accessed pages on it, and check the TLB first when we get a page number. If the page we need is found on the TLB, we can use that table to load the physical address of the memory we want, and it will save some time since the TLB runs much faster than the page table, which is on the cache. If we do not find our page on the TLB, this is a TLB miss and we must resort to reading the slower page table on the cache. On the system, the TLB is faster because the memory it resides on can be checked faster than a page table can be accessed
- When we get a TLB miss, we should store that page on the TLB because that page we just checked might be needed again soon. We need to use some method of deciding which TLB entry to get overwrite if the TLB is full


### Compile and Deployment

**Linux**
Run 'make'
Ensure BACKING_STORE.bin is located in directory

Makefile operations:
- use gcc compiler for vmmgr.c only

```
// create the object file
gcc vmmgr.c                                      

./vmmgr <address list file>

```

### Sample output
```
Address #1: [Virtual Page 66] [Physical Frame 0] [Offset = 20] Resulted in Char:
Address #2: [Virtual Page 244] [Physical Frame 1] [Offset = 29] Resulted in Char:
Address #3: [Virtual Page 117] [Physical Frame 2] [Offset = 246] Resulted in Char: 
Address #4: [Virtual Page 209] [Physical Frame 3] [Offset = 179] Resulted in Char: l
Address #5: [Virtual Page 156] [Physical Frame 4] [Offset = 249] Resulted in Char:
...
...
...
Address #996: [Virtual Page 66] [Physical Frame 0] [Offset = 175] Resulted in Char: �
Address #997: [Virtual Page 34] [Physical Frame 181] [Offset = 236] Resulted in Char:
Address #998: [Virtual Page 38] [Physical Frame 174] [Offset = 201] Resulted in Char:
Address #999: [Virtual Page 177] [Physical Frame 179] [Offset = 251] Resulted in Char: ~
Address #1000: [Virtual Page 47] [Physical Frame 10] [Offset = 75] Resulted in Char: �

Virtual Memory Simulation Complete
 Addresses Read: 1000
 TLB Hits: 54/1000 (0.054000%)
 Page Faults: 244/1000 (0.244000%)
 ```
