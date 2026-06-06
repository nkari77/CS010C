#include "Node.h"

Node::Node(const string& string)
: small(string),large(""),left(nullptr),middle(nullptr),right(nullptr),parent(nullptr)
{}

const string Node::getSmall() {
    return small;
}

const string Node::getLarge() {
    return large;
}

  void Node::setSmall(const string& setSmall) {
    small = setSmall;
}

  void Node::setLarge(const string& newLarge) {
    large = newLarge;
}

Node* Node::getLeft(){
    return left;
}
Node* Node::getMiddle(){
    return middle;
}
Node* Node::getRight(){
    return right;
}

bool Node::isFull() const{
    if (small != ""  && large != ""){
        return true;
    }
    return false;
}
bool Node::isLeaf() const{
    if (left == nullptr && middle == nullptr && right == nullptr){
        return true;
    }
    return false;
}

Node* Node::getParent(){
    return parent;
}

 void Node::setParent(Node* node){
    parent = node;
}
 void Node::setLeft(Node* node){
    left = node;
}
 void Node::setMiddle(Node* node){
    middle = node;
}
 void Node::setRight(Node* node){
    right = node;
}

