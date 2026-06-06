#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {

  friend class Tree;

  public:
  Node();
  Node(const string&);
  
  const string getSmall();
  const string getLarge();

  Node* getLeft();
  Node* getMiddle();
  Node* getRight();
  Node* getParent();

   void setLeft(Node* node);
   void setMiddle(Node* node);
   void setRight(Node* node);
   void setParent(Node* node);

   void setSmall(const string&);
   void setLarge(const string&);
  

  bool isFull() const;
  bool isLeaf() const;

private:
  string small;
  string large;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;

  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.
  

};

#endif