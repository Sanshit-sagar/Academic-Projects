#include <vector> 
#include <queue>
#include <string> 
#include <utility> 
#include "disjointSet.h" 

using namespace std;


Node* disjointSet::find(Node* node) { 
		int currIndex = -1; 
		for(int i = 0; i<actorsVector.size(); i++) {
			if(actorsVector[i]->name.compare(node->name)==0) {
				currIndex = i; 
				}
			}
		while(index[currIndex] !=-1) { 
			currIndex = index[currIndex]; 
			}	 	
	
		Node* currNode = actorsVector[currIndex]; 
		return currNode; 
	} 

void disjointSet::unionSet(Node* first, Node* second) { 
		Node* one = find(first); 
		Node* two = find(second);
		if(one->name.compare(two->name)==0) { return; } 
		int oneIndex, twoIndex = -1; 
		for(int i = 0; i< actorsVector.size(); i++) { 
			if(actorsVector[i]->name.compare(one->name)==0) { 
				oneIndex = i; 
			}
			if(actorsVector[i]->name.compare(two->name)==0) { 
				twoIndex = i; 
			}
		} 
		index[oneIndex] = twoIndex; 
	}
