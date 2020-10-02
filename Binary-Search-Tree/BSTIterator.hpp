#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>
using namespace std;

template<typename Data>
class BSTIterator : public iterator<input_iterator_tag,Data> {

private:
    BSTNode<Data>* curr;

public:
    BSTIterator(BSTNode<Data>* curr) : curr(curr) { }

    Data operator*() const {	 
            return curr->data;
    }

    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    
    bool operator==(BSTIterator<Data> const & rhs) const {
        if (this->curr == rhs.curr)    {   
            return true;
        }
        else {
            return false;
        }
    }

    bool operator!=(BSTIterator<Data> const & rhs) const {
        if (this->curr != rhs.curr) {
            return true;
        }
        else {
            return false;
        }
    }
};

#endif 