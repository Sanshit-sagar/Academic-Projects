#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

template<typename Data>
class BSTNode {

public:

	BSTNode(const Data & d) : data(d) {
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	BSTNode<Data>* left;
	BSTNode<Data>* right;
	BSTNode<Data>* parent;
	Data const data;   


	BSTNode<Data>* successor() {

		BSTNode<Data>* position = this;

		if (position->right != NULL) {
			return FindSmallest(position->right);
		}

		BSTNode<Data> *newnode = position->parent; 
			while (newnode != NULL && position == newnode->right) { 

				position = newnode;
				newnode = newnode->parent;
			}
		return newnode;
	}


	BSTNode<Data>* FindSmallest(BSTNode<Data>* node) {

		while (node->left != NULL) {
	
			node = node->left;
		}
		return node;
	}

}; 


template <typename Data>
ostream & operator<<(ostream& stm, const BSTNode<Data> & n) {
	stm << '[';
	stm << setw(10) << &n;                
	stm << "; p:" << setw(10) << n.parent;
	stm << "; l:" << setw(10) << n.left;   
	stm << "; r:" << setw(10) << n.right;  
	stm << "; d:" << n.data;              
	stm << ']';
	return stm;
}

#endif 