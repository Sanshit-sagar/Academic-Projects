#include "HCNode.h"
#include "HCTree.h"
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
        if(argc<3) {
                std::cout << "Not enough arguments" << std::endl;
        }

        ifstream file;
        file.open(argv[1], std::ifstream::in);
        std::vector<int> characters(256, 0);
        int currFreq = 0;
	int counter = 0; 
	int totalBits = 0;
	while(counter<256) {
                currFreq = file.get(); 
                if(file.eof()) { break; }
		currFreq = currFreq - 48; 
		characters[counter] = currFreq; 
		totalBits += currFreq;
                cout << "curr freq .." << currFreq << endl;
		counter++;        
	}
	
	HCTree* tree = new HCTree();
        tree->build(characters);
	
    	std::ofstream out (argv[2], std::ofstream::out);
	BitInputStream stream(file); 		
	
	for(int i=0; i<totalBits; i++) {
		char curr = tree->decode(stream); 
		out.put(curr); 
	}
	cout << "Closing files " << endl; 
        file.close();
        out.close();
	return 0; 
}