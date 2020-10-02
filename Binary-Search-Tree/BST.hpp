#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>
class BST {

protected:
    BSTNode<Data>* root;
    unsigned int isize;
    unsigned int iheight;

public:
    typedef BSTIterator<Data> iterator;

    BST() : root(0), isize(0), iheight(0) {  }

    virtual ~BST() {
        deleteAll(root);
    }

    BSTNode<Data>* recurseInsert(const Data& item, BSTNode<Data>* node) {
        if(node == NULL) {
            return new BSTNode<Data>(item);
        }
        if (node->data < item) { 
                BSTNode<Data> *newRightChild = recurseInsert(item, node->right);
                node->right = newRightChild
                newRightChild->parent = node;
        }
        else {
                BSTNode<Data> *newLeftChild = recurseInsert(item, node->left);
                node->left = newLeftChild;
                newLeftChild->parent = node;
        }
        return node;
    }


    virtual bool insert(const Data& item) {
        root = recurseInsert(item, root);
        isize = isize +1;
        return true;
    }

    virtual iterator findHelper(const Data& item, BSTNode<Data>* node) const {

        if (item < node->data) {
            return findHelper(item, node->left);
        }

        else if (node->data < item) {
            return findHelper(item, node->right);
        }
        else {
            return node;
        }

    }

    virtual iterator find(const Data& item) const {
        if (this->root != NULL) {
            return findHelper(item, this->root);
        }
        return 0;
    }


    unsigned int size() const {
        return isize;
    }

    unsigned int heightHelper(BSTNode<Data>* node, int currentHeight) {
        if (node == NULL) {
            return currentHeight - 1;
        }

        int left_height = heightHelper(node->left, currentHeight + 1);
        int right_height = heightHelper(node->right, currentHeight + 1);

        return std::max(left_height, right_height);

        return 0;
    }

    unsigned int height() {

        if (this->root != NULL) {
            return heightHelper(this->root, 0) + 1;
        }
        else {
            return -1;
        }
    }

    bool empty() const {
        return isize == 0;
    }

    
    iterator begin() const {
    return BST::iterator(first(root));
    }

    
    iterator end() const {
        return typename BST<Data>::iterator(0);

    }

    void inorder() const {
        inorder(root);
    }


    void inorder(BSTNode<Data>* node) const {  

        if (node == NULL) {
            return;
        }

        if (node->left != NULL) {
            inorder(node->left);
        }

        cout << node->data << endl;

        if (node->right != NULL) {
            inorder(node->right);
        }
    }

private:
    static BSTNode<Data>* first(BSTNode<Data>* root) {

        if (root == NULL) {
            return 0;
        }

        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }

    static void deleteAll(BSTNode<Data>* n) {
        if (n == NULL) {
            return;
        }

        deleteAll(n->left);
        deleteAll(n->right);
        delete(n);
    }
};


#endif 