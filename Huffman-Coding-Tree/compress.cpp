#include "HCNode.h" 
#include "HCTree.h"
#include <vector> 
#include <queue> 
#include <iostream>
#include <fstream>

using namespace std; 

int main(int argc, char *argv[]) {
	int totalBits = 0; 
	if(argc<3) 
	{ 
		std::cout << "Not enough arguments" << std::endl; 
	}
	
	ifstream file;
	std::vector<int> characters(256, 0); 
	file.open(argv[1], std::ifstream::in); 
	unsigned char currChar; 
	while(1) {
		if(file.is_open()) {
		currChar = file.get();
		if((!(file.good()) || (file.eof()))) { break; }
		characters[(int)currChar]++;
		}
	}
	file.close(); 
	
	HCTree* tree = new HCTree();
        tree->build(characters);
	ofstream out; 
	out.open(argv[2], std::ofstream::out); 
	
	//FIND MORE EFFICIENT MANNER TO IMPLEMENT THIS 
	//THIS IS THE WRITING OF THE FILE HEADER
	for(int i = 0; i<256; i++) {
		out << characters[i]; 
		totalBits+=characters[i];
	}
        
	cout << "total bits are : " << totalBits << endl;
	file.open(argv[1], std::ifstream::in); 	
	unsigned char charToEncode; 
	
	BitOutputStream stream = BitOutputStream(out); 	
	int counter = 0; 
	while(counter<totalBits) {
		charToEncode = file.get(); 
		if(file.eof()) { break; } 
		tree->encode(charToEncode, stream);
	}
	stream.flush(); 
	file.close(); 
	out.close(); 
}  