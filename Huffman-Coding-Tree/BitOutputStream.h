#include <iostream>
/*
 * Write bits to the ostream
 *
 */
class BitOutputStream {
  private: 
    std::ostream& output;
    unsigned char buffer=0; 
    int count=0;     

  public:
   /*
    *Initialize the buffer and the count into 0.
    */
    BitOutputStream(std::ostream& out): output(out)
	{
	buffer = 0; 
	count = 0; 
	}
    /*
     * The function will write bits into the buffer going from 
     * the least bit into the buffer. then the method will flush
     * the buffer if the buffer is full (8 bit) and then write 
     * to it again.
     * Parameters: int bit which is the bit to write to the buffer.
     *
     */
    void writeBit(int bit);
    /*
     *The function will empty the buffer when needed.
     */ 
    void flush();  
};
