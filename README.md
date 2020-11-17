# Operating Systems: Assignment 6
Michael Kulinich
kulinich@chapman.edu

Ayden Best
bbest@chapman.edu

CPSC 380-01

## Task: Using Threads and Mutex/Conting Semaphores for the producer-consumer problem
The objective of this assignment consists of writing a C/C++ program that translates logical to physical addresses for a virtual address space of size 216 = 65,536 bytes. Your program will read from a file containing logical addresses and, using a TLB as well as a page table, will translate each logical address to its corresponding physical address and output the value of the byte stored at the translated physical address. The goal behind this project is to simulate the steps involved in translating logical to physical addresses.





### Compile and Deployment

**Linux**
Run 'make'

Makefile operations:
- use gcc compiler
- create a static library for the checksum function
```
// create the object file
gcc -c ip_checksum.c                                      

//archive object file to make a static library
ar -rc libip_checksum.a ip_checksum.o

// tell the compiler to look in our library
gcc prodcon.c -L. -lip_checksum -o prodcon -lrt -lpthread

./prodcon [buffer size]

```

### Sample output
