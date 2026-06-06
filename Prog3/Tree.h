#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void destroyTree(Node* node); //tree dealloc helper
  void insert(const string &);
  void insert(const string &, Node* node);
  void preOrder( ) const;
  void preOrder(Node* node) const;
  void inOrder( ) const;
  void inOrder(Node* node ) const;
  void postOrder( ) const;
  void postOrder(Node* node ) const;
  void remove(const string &);
  void remove(const string&, Node* );
  bool search (const string &) const;
  bool search (const string &, Node* node) const;
  void split(Node* node, const string& value);

private:
  // Add additional functions/variables here
  const string smallest(Node* node, const string& string);
  const string middle(Node* node, const string& string);
  const string largest(Node* node, const string& string);
    
};

#endif