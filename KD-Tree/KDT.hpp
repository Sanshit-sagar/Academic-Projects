#ifndef KDT_HPP
#define KDT_HPP

#include "BSTNode.hpp"
#include <algorithm> 
#include <iostream>  
#include <math.h>   
#include <vector>   
#include <limits>    
#include "BST.hpp"

using namespace std;

class Point {

  private:
    double delta = 0.00005;
  public:

    double x, y;

    Point(): x(0.0), y(0.0) { }

    Point(double x, double y) {
		this->x = x;
		this->y = y;
	}

    bool operator == (const Point& other) const {
      return abs(x - other.x) < delta && abs(y - other.y) < delta;
    }

    bool operator != (const Point& other) const {
      return abs(x - other.x) > delta || abs(y - other.y) > delta;
    }


    bool operator < (const Point& other) const {
      cerr << "This operator should not be called, you will need " <<
        "check the x and y components each time" << endl;
      return false;
    }


    static double squareDistance(const Point& p1, const Point& p2) {


		int dx = p2.x - p1.x;
		int dy = p2.y - p1.y;

		//cout << p1.x << endl;
		return (dx * dx + dy * dy);
    }
};

std::ostream& operator << (std::ostream& out, const Point& data) {
  out << "(" << data.x << ", " << data.y << ")";
  return out;
}


bool xLessThan(const Point & p1, const Point & p2) {
  return p1.x < p2.x;
}

bool yLessThan(const Point & p1, const Point & p2) {
  return p1.y < p2.y;
}

class KDT : public BST<Point> {
  public:

	  virtual unsigned int build(vector<Point>& items) {
      if(items.size()==0) {
        return 0;
      }

      BSTNode<Point>* curr_root = buildSubset(items, 0, items.size(), 0, 0);
      if(this->root==NULL) {
        this->root = curr_root;
        this->isize = items.size();
        this->iheight = this->height();
        return this->isize;
      }

      BSTNode<Point>* root_to_ret = recurseInsertKDT(curr_root, this->root);
      if(root_to_ret==NULL) {
        return 0;
      }
      this->isize += items.size();
      this->iheight = this->height();

      return this->isize;
    }

	  BSTNode<Point>* buildSubset(vector<Point> & items, unsigned int start,
		  unsigned int end, unsigned int dimension,
		  unsigned int height) {

		  if (start >= end) {
			  return NULL;
		  }

		  if (dimension == 0) {
			  std::sort(items.begin() + start, items.begin() + end - 1, xLessThan);
      }
      else {
        std::sort(items.begin() + start, items.begin() + end -1, yLessThan);
      }

		  int medianIndex = (start + end)/2;
      int new_height = height + 1;
      int new_dimension = (dimension==0) ? 1 : 0;

		  BSTNode<Point>* medianNode = new BSTNode<Point>(items[medianIndex]);
      medianNode->left = buildSubset(items, start, medianIndex, new_dimension, new_height);
		  medianNode->right = buildSubset(items, medianIndex + 1, end, new_dimension, new_height);

		  return medianNode;
	  }

    BSTNode<Point>* recurseInsertKDT(BSTNode<Point>* to_add, BSTNode<Point>* node) {
      if(node == NULL) {
          return to_add;
      }
      else if(node->data == to_add->data) {
          return NULL;
      }

      if (node->data < to_add->data) {
          BSTNode<Point> *newRightChild = recurseInsertKDT(to_add, node->right);
          node->right = newRightChild;
          newRightChild->parent = node;
      }
      else {
          BSTNode<Point> *newLeftChild = recurseInsertKDT(to_add, node->left);
          node->left = newLeftChild;
          newLeftChild->parent = node;
       }
      return node;
    }

    int getHeight(BSTNode<Point>* root) {
        if(root==NULL) {
          return 0;
        }
        else {
          int left_subtree_height = getHeight(root->left);
          int right_subtree_height = getHeight(root->right);

          if(left_subtree_height>right_subtree_height) {
            return left_subtree_height + 1;
          }
          else {
            return right_subtree_height + 1;
          }
        }
    }


    virtual iterator findNearestNeighbor(const Point& item) const {
      return 0;
    }

    virtual iterator find(const Point& item) const override {
      cerr << "The KD Tree find method should not be called" << endl;
      cerr << "Use findNearestNeighbor instead" << endl;
      return 0;
    }


    virtual bool insert(const Point& item) override {
      cerr << "The KD Tree insert method should not be called" << endl;
      return false;
    }

  private:

   
    void  findNNHelper(BSTNode<Point> * node, const Point& queryPoint,
                                 double * smallestSquareDistance,
                                 BSTNode<Point> ** closestPoint,
                                 unsigned int dimension) const {

          if(node.left==NULL && node.right==NULL) {
              int x_dist = queryPoint.x - node->data.x;
              int y_dist = queryPoint.y - node->data.y;
              int updated_distance = x_dist * x_dist + y_dist * y_dist;
              if(updated_distance<smallestSquareDistance) {
                smallestSquareDistance = updated_distance;
                closestPoint = node->data;
              }
          }
          else {
              bool search_direction = false; 
              if(dimension==0) {
                if(queryPoint.x>node->data.x) {
                  search_direction = true;
                }
              }
              else {
                if(queryPoint.y>node->data.y) {
                  search_direction = true;
                }
              }


              int x1, x2;
              if(dimension==0) {
                x1 = node.x - smallestSquareDistance;
                x2 = node.x + smallestSquareDistance;
              }
              else {
                x1 = node.y - smallestSquareDistance;
                x2 = node.y + smallestSquareDistance;
              }

              int new_dimension = (dimension==0) ? 1 : 0;
              int curr_distance = squareDistance(node->data, queryPoint);
              if(search_direction==false) {
                if(x1<=curr_distance) {
                  findNNHelper(node.left, queryPoint, smallestSquareDistance, closestPoint, new_dimension);
                }
                if(x2>curr_distance) {
                  findNNHelper(node.right, queryPoint, smallestSquareDistance, closestPoint, new_dimension);
                }
              }
              else { 
                if(x2>curr_distance) {
                  findNNHelper(node.right, queryPoint, smallestSquareDistance, closestPoint, new_dimension);
                }
                if(x1<=curr_distance) {
                  findNNHelper(node.left, queryPoint, smallestSquareDistance, closestPoint, new_dimension);
                }
              }
          }
          return node;
    }
};


#endif // KDT_HPP