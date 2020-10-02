#include "HCTree.h"
#include <stack> 

using namespace std;

	std::vector<HCNode*> orderedNodes(256, (HCNode*) 0); 
    /*PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     *  Parameters: vector to hold the values of the chars into the method. 
     */
	HCNode* root; 
    void HCTree::build(const vector<int>& freqs) {
	std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq; 
	HCNode* currNode; 
	for(int i=0; i<freqs.size(); i++) 
		{
		if(!(freqs[i])) { continue; } 
		int currFreq = freqs[i];
		currNode = new HCNode(currFreq, i, 0,0,0);
		orderedNodes[i] = currNode;
		pq.push(currNode);  	
		}

	HCNode* childL; 
	HCNode* childR;
	HCNode* parent;  
	while(pq.size()>1) 
		{
			childL = pq.top();
			pq.pop(); 
			childR = pq.top();
			pq.pop(); 
			int totalFreq = (childL->count) + (childR->count);
			char parentSymbol;  
			if((childL->symbol)>(childR->symbol)) { 
				parentSymbol = childL->symbol; }
			else {
				parentSymbol = childR->symbol; 
			} 
			parent = new HCNode(totalFreq, parentSymbol, childL, childR, 0); 
			childL->p = parent; 
			childR->p = parent; 
			pq.push(parent); 
		}
	root = pq.top();
	pq.pop();	
}

 /** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 * PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
 *  BE USED IN THE FINAL SUBMISSION.
 *  Parameters: symbol is the symbol to encode , and out is 
 *  the BitOutStream that is needed to write the bits into
 *  the buffer.
 */

   void HCTree::encode(byte symbol, BitOutputStream& out) const{
	HCNode* nodeToEncode; 
	nodeToEncode = orderedNodes[symbol];
	stack<int> code; 	
	while(nodeToEncode!=root) {
		if((nodeToEncode->p->c1)==nodeToEncode)		
		{
			code.push(1); 
		}
		else
		{
			code.push(0); 
		}
	nodeToEncode = nodeToEncode->p;
	}
	while(code.size()!=0) {
		out.writeBit(code.top()); 
		code.pop(); 
	}
}



     /*ASCII text) from the ifstream.
     * PRECONDITION: build() has been called, to create the coding
     *tree, and initialize root pointer and leaves vector.
     *THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *IN THE FINAL SUBMISSION.
     *Parameters: in which is the BitInputStream used to read the char
     *to decode.
     */
    int HCTree::decode(BitInputStream& in) const {
	HCNode* current = root;
	int currPath;  
	while(((current->c0!=0) || (current->c1!=0)))
	{
		currPath = in.readBit();
		if(currPath == 0) 	
		{
			current = current->c0; 
		}
		else if(currPath == 1) 
		{
			current = current->c1; 
		}
	}
	return current->symbol; 
   }