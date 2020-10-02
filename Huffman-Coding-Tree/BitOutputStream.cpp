
#include "BitOutputStream.h"
#define EMPTY 8
#define ONE 0x00000001
/*
 * write bits into the buffer.
 */
void BitOutputStream::writeBit(int bit) {

if(output.good()) {
buffer = buffer |(bit << (7-count)); 
count++;

if(count==8) 
	{ 
	flush(); 
	}
  }
}
/*
 * flush the buffer when full.
 */ 
void BitOutputStream::flush() {
output.put(buffer); 
output.flush(); 
buffer = 0; 
count = 0; 
}