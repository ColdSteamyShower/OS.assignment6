#define OFFSET_CHUNK 8
#define MASK 255 // 8-bit mask collects last 8 bits: 11111111

/*
/////How shifting works:
>> and << operators on ints relocate bits

19<<1 -> 19 in binary: 00010011 -> shift all left by 1 -> 00100110 -> 38

/////How masking works:
& logical operator can apply over individual bits of two values
19&15
->
19 in binary: 10011  Apply AND over each bit
15 in binary: 01111           vvv
binary result:00011

Goal: We want bits 17-32 as the value, 9-16 as the page and 1-8 as the offset
Solution:
We shift in chunks until the desired value's 8-bit chunk is at the end
Use & and a mask to only save the last 8 bits
*/

// returns the page number of an address
unsigned getPage(unsigned address)
{
  return (address >> OFFSET_CHUNK)&MASK; // move over the page number bits to front then mask to get the last 8 bits
}

// returns the offset of an address
unsigned getOffset(unsigned address)
{
  // bits that represent the offset are already at the front
  return address&MASK; // mask to get the last 8 bits
}
