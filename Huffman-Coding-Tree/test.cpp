#include "HCTree.h"
#include "HCNode.h" 

int main(int argc, char** argv) 
{	
	std::vector<int> freqs(256);
	 
	freqs[97] = 5;
	freqs[98] = 7;
	freqs[99] = 8;
	freqs[100] = 21;
	freqs[101] = 25;
	HCTree* tree = new HCTree(); 
	tree->build(freqs); 
	//std::cout << "Done with the tester." << std::endl; 
	const char toEncode = 'a';
	std::ofstream ofs ("test.txt", std::ofstream::out);  
	BitOutputStream stream = BitOutputStream(ofs) ; 
	tree->encode(toEncode, stream);  
	//std::ifstream ifs ("test.txt", std::ifstream::in); 
	//tree->decode(ifs); 
	
	return 0; 

} 