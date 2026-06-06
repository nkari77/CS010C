#include "Tree.h"
#include <iostream>

Tree::Tree() {
  root = nullptr;
}

Tree::~Tree() {
    destroyTree(root);
}

void Tree::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    //traverse left,right,mid subtrees, deleting each node 
    destroyTree(node->getLeft());
    destroyTree(node->getMiddle());
    destroyTree(node->getRight());

    //delete node
    delete node;
}

//recursive helper
void Tree::insert(const string &string){
    if (root == nullptr){
        root = new Node(string);
        return;
    }
    insert(string,root);   
}

void Tree::insert(const string &s, Node* node){
    
    if(!node->isLeaf()) { // if internal node
        if(s < node->getSmall()) return insert(s, node->getLeft());
        if(s > node->getLarge() && node->getRight() != nullptr) return insert(s, node->getRight());
        else return insert(s, node->getMiddle());
    }

    if(node->getLarge() == "" && node->isLeaf()) {//if node contains 1 key
        if(s < node->getSmall()) { 
            //swap old small with new small, and replace large with old small
            node->setLarge(node->getSmall());
            node->setSmall(s);
            return;
        } 
        //othewise, simply insert to large
        node->setLarge(s);
        return;
    } else if(node->isFull() && node->isLeaf()){
      //split node if it is full and is a leaf (no child can be made)
        split(node, s);
    }
}

const string Tree::smallest(Node* node, const string& value) {
    string prevsmall = node->getSmall(); //store prevsmall
    string prevlarge = node->getLarge(); //store prevlarge
    //if prevsmall is the smallest of the 3
    if(prevsmall < prevlarge && prevsmall < value)
    {
      return prevsmall;
    } 
    //if prevlarge is smallest of the three
    if(prevlarge < prevsmall && prevlarge < value){
      return prevlarge;
    } 
    //otherwise, value is the smallest of the three
    return value;
}

const string Tree::middle(Node* node, const string& value) {
    string prevsmall = node->getSmall();
    string prevlarge = node->getLarge();
    //if prevsmall is between prevlarge and value
    if((prevsmall < prevlarge && prevsmall > value) || (prevsmall > prevlarge && prevsmall < value)){
      return prevsmall;
    }   
    //if prevlarge is between prevsmall and value
    if((prevlarge < prevsmall && prevlarge > value) || (prevlarge > prevsmall && prevlarge < value)){
      return prevlarge;
    } 
    //otherwise value is the mid
    return value;
}

const string Tree::largest(Node* node, const string& value) {
    string prevsmall = node->getSmall();
    string prevlarge = node->getLarge();
    //if prevsmall is the biggest
    if(prevsmall > prevlarge && prevsmall > value){
      return prevsmall;
    } 
    //if prevlarge is the biggest
    if(prevlarge > prevsmall && prevlarge > value){
      return prevlarge;
    } 
    //otherwise value is the biggest
    return value;
}

void Tree::split(Node* node, const string& s) {
    //find what the left, mid and right will be post split
    string left = smallest(node, s);
    string mid = middle(node, s);
    string right = largest(node, s);
    //root node split case
    if(node == root && root->getLeft() == nullptr) {
        //set small to left
        node->setSmall(left);
        //default large
        node->setLarge("");
        //new mid
        root = new Node(mid);
        root->setLeft(node);
        node->setParent(root);
        root->setMiddle(new Node(right));
        root->getMiddle()->setParent(root);
        //leaf node split case
    } else if(node->getLeft() == nullptr) {
        Node* parent = node->getParent();
        //parent left child with 2 children check case
        if(node->getParent()->getLarge() == "" && node == parent->getLeft()) {
            parent->setSmall(mid);
            parent->setRight(new Node(parent->getMiddle()->getSmall()));
            parent->getRight()->setParent(parent);
            parent->getMiddle()->setSmall(right);
            node->setSmall(left);
            node->setLarge("");
        }
        //parent mid child with 2 children check case 
        else if(node->getParent()->getLarge() == "" && node == parent->getMiddle()) {
            node->getParent()->setRight(new Node(right));
            node->getParent()->getRight()->setParent(node->getParent());
            node->setSmall(left);
            node->setLarge("");
        } 
        //parent right child 2 children check case
        else {
            node->setSmall(left);
            node->setLarge(right);
            split(node->getParent(), mid);
        }
    }   
    return;
}

void Tree::preOrder() const {
  preOrder(root);
  cout << endl;
}

void Tree::preOrder(Node* node) const {
    if(node == nullptr){
      return;
    }
    //small print
    cout << node->getSmall() << ", ";
    //traverse left
    preOrder(node->getLeft());
    //if large exist, print, otherwise traverse
    if(node->getLarge() != "") {
        cout << node->getLarge() << ", ";
    }
    //mid traverse
    preOrder(node->getMiddle());
    //right traverse
    preOrder(node->getRight());
}


void Tree::inOrder() const {
  inOrder(root);
  cout << endl;
}

void Tree::inOrder(Node* node) const {
    if(node == nullptr){
      return;
    } 
    //left traverse
    inOrder(node->getLeft());
    //smallest val
    cout << node->getSmall() << ", ";
    //traverse mid
    inOrder(node->getMiddle());
    //if large exists, print, otherwise continue traversal
    if(node->getLarge() != "") {
        cout << node->getLarge() << ", ";
    }
    inOrder(node->getRight());
    

}

void Tree::postOrder() const {
  postOrder(root);
  cout << endl;
}

void Tree::postOrder(Node* node) const {
    if(node == nullptr){
      return;
    } 
    //left mid traverse
    postOrder(node->getLeft());
    postOrder(node->getMiddle());
    //small print
    cout << node->getSmall() << ", ";
    //right traverse
    postOrder(node->getRight());
    //if large exists print
    if(node->getLarge() != "") {
        cout << node->getLarge() << ", ";
    }

}

void Tree::remove(const string& key){
  if (!search(key)){
    return;
  }
  remove(key,root);

}
void Tree::remove(const string& key, Node* node){
    if(key < node->getSmall() && node->getLeft() != nullptr){
      //left traverse based on key comparison to small
      remove(key, node->getLeft());
    } 
    else if(key > node->getLarge() && node->getRight() != nullptr){
      //right traverse based on key comparison to large
      remove(key, node->getRight());
    } 
    else if(key > node->getSmall() && node->getMiddle() != nullptr)
    {
      //between case, traverse mid
      remove(key, node->getMiddle());
    } 
    //if node equals small of currnode
    if(key == node->getSmall()){ 
        //if note is a nonroot leaf
        if(node->isLeaf() and node != root){
          //if the node is full, move large to the left (small) and erase the large
            if(node->isFull()){ 
              node->setSmall(node->getLarge());
              node->setLarge("");
            }
            //check if left mid or right (not full case)
            else{
                Node* parent = node->getParent();
                //left child check case
                if(parent->getLeft() == node){
                    string middleCopy = parent->getMiddle()->getSmall();
                    delete parent->getMiddle();
                    parent->setMiddle(nullptr);
                    delete node;
                    parent->setLeft(nullptr);

                    node->getParent()->setLarge(middleCopy);
                    return;
                }
                //mid child check case
                else if(parent->getMiddle() == node){
                    string leftCopy = parent->getLeft()->getSmall();
                    delete parent->getLeft();
                    parent->setLeft(nullptr);
                    parent->setMiddle(nullptr);
                    delete node;

                    parent->setLarge(parent->getSmall());
                    parent->setSmall(leftCopy);
    
                    return;
                }
                //right child check case
                else if(parent->getRight() == node){ 
                    string copyLeft = parent->getLeft()->getSmall();
                    delete parent->getLeft();
                    parent->setLeft(nullptr);
                    parent->setRight(nullptr);
                    delete node;

                    parent->setLarge(parent->getSmall());
                    parent->setSmall(copyLeft);
                    

                    return;
                }
            }
        }
        //if node is the root
        else{
            if(node->isLeaf()) {
                if(node->isFull()){ 
                  //if large is being removed
                    if(key == node->getLarge()){
                      node->setLarge("");
                    } 
                    //small node remove case
                    else if(key == node->getSmall()){
                        node->setSmall(node->getLarge());
                        node->setLarge("");
                    }
                } 
                //last case, node itself
                else{
                    delete node;
                    root = nullptr;
                }
            } 
            //root node with children removal
            else {
                node->setSmall(node->getLeft()->getSmall());
                node->setLarge(node->getMiddle()->getSmall());
                delete node->getLeft();
                delete node->getMiddle();
                node->setLeft(nullptr);
                node->setMiddle(nullptr);
            }
        }
    }
    //last case, removing large of node
    else if(key == node->getLarge()){
        node->setLarge("");
    } 
}


bool Tree::search(const string &s) const {
    if(root == nullptr){
      return false;
    } 
    return search(s, root);
}

bool Tree::search(const string &s, Node* node) const{
  //if node is the small or large
    if(s == node->getSmall() || s == node->getLarge()) {
      return true;
    }
    //if node is less, traverse left
    if(s < node->getSmall() && node->getLeft() != nullptr){
      return search(s, node->getLeft());
    } 
    //if node between, traverse middle
    if((s > node->getSmall() && s < node->getLarge()) || (node->getRight() == nullptr)){
      return search(s, node->getMiddle());
    } 
    //else traverse right
    else{
      search(s, node->getRight());
    } 

    //last case, not found return false
    return false;
}