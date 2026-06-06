#include "Node.h"

using namespace std;

//default constructor
Node::Node(string k){
    key = k;
    left = NULL;
    right = NULL;
    height = 1;
}

//return key
const string Node::getKey(){
    return key;
}

//return height
const int Node::getHeight(){
    return height;
}

//return height
void Node::setHeight(int h){
    height = h;
}

//set left
void Node::setLeft(Node* newLeft){
    left = newLeft;
}

//get left
Node* Node::getLeft(){
    return left;
}

//set right
void Node::setRight(Node* newRight){
    right = newRight;
}

//get right
Node* Node::getRight(){
    return right;
}