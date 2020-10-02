#include <iostream>
/*
 *reading bits from the istream
 */
class BitInputStream {
  private: 
    std::istream& input;
    unsigned char buffer = 0; 
    int count = 0;     

  public:
  /*
   *Initialize the objct of the istream
   * for buffer and the count
   */
    BitInputStream(std::istream& in): input(in)
	{ 
		 buffer = 0; 
		 count = 0;  
	}
    /**
     * This method will read the input from the buffer from 
     * left to right and then check if the bit read is 0 or
     * 1 to decode later. The method will keep reading the 
     * bits going to the right to be used later.
     * Parameters: None.
     */
    int readBit(); 
};