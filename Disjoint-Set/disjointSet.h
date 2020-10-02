#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP

#include <utility>
#include <vector>
#include <queue>
#include <string>
#include "Node.h"
#include "Edge.h"
#include <iostream>

using namespace std; 

class disjointSet {
protected: 
	
public: 
	std::vector<Node*> actorsVector;
	std::vector<int> index;  

	disjointSet(std::vector<Node*> actorNodes) 
	{ 
		int vectorSize = actorNodes.size(); 
		for(int i = 0; i<vectorSize; i++) {
			index.push_back(-1); 
			actorsVector.push_back(actorNodes[i]);  	
		}
	}; 

	Node* find(Node* node); 
	void unionSet(Node* first, Node* second); 
};

#endif 