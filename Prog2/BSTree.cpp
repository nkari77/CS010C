#include "BSTree.h"
#include <stdexcept>
#include <iostream>

using namespace std;
//creates empty tree with null root
BSTree::BSTree()
: root(nullptr){}

BSTree::~BSTree(){
    //call helper
    destroyTree(root); 

}

void BSTree::destroyTree(Node* node){
    if (node == nullptr){
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}

//insert value
void BSTree::insert(const string& insertValue){
    if (root == nullptr){
        root = new Node(insertValue);
        return;
    }

    Node* curr = root;
    //do not end until node is added
    while (1){
        //check case for duplicate data node
        if (insertValue == curr->data){
            curr->count++;
            return;
        }
        else if(insertValue < curr->data){
            //if left node is empty, put new node there
            if (curr->left == nullptr){
                curr->left = new Node(insertValue);
                return;
            }
            //else, continue traversal
            curr = curr->left;
        }
        else{
            //check case if node must be inserted as rightmost
            if (curr->right == nullptr){
                curr->right = new Node(insertValue);
                return;
            }
            curr = curr->right;
        }
    }
}

//search recursion
bool BSTree::search(const string& searchVal) const{
    return searchHelp(root, searchVal);
}
//search recursion helper
bool BSTree::searchHelp(Node* node, const string& searchVal) const{
    if (node == nullptr){
        //node does not exist
        return false;
    }
    else if (searchVal == node->data){
        //searchval has been found
        return true;
    }
    else if (searchVal < node->data){
        //search left sub
        return searchHelp(node->left, searchVal);
    }
    else {
        //search right sub
        return searchHelp(node->right, searchVal);
    }
}

string BSTree::largest() const{
    //empty tree check case
    if (root == nullptr){
        return "";
    }

    Node* curr = root;

    //keep setting "curr" to its right child (larger) until no larger nodes exist
    while (curr->right != nullptr){
        curr = curr->right;
    }
    return curr->data;
}

string BSTree::smallest() const{
    //empty tree check case
    if (root == nullptr){
        return "";
    }
    Node* curr = root;
    
    //keep setting "curr" to its left child (smaller) until no smaller nodes exist
    while (curr->left != nullptr){
        curr = curr->left;
    }
    return curr->data;
}

//height recursion
int BSTree::height(const string& heightVal, Node* curr) const {
    //not found
    if (curr == nullptr){
        return -1;
    }
    //determine left and right subtree distance, then determine the larger one (most hopes required)
    int lsbtHeight = height(heightVal, curr->left);
    int rsbtHeight = height(heightVal,curr->right);
    return 1 + max(lsbtHeight,rsbtHeight);
}

//height helper
int BSTree::height(const string& key) const{
    //if key does not exist, return -1
    if (!search(key)){
        return -1;
    }
    Node* curr = root;

    while (curr!= nullptr){
        if (curr->data == key){
            break;
        }
        //traverse left
        else if (key < curr->data){
            curr = curr->left;
        }
        //traverse right
        else{
            curr = curr->right;
        }
    }
    //start recursive calc for node found
        return height(key,curr);

}
//remove helper
void BSTree::remove(Node *&curr, const string &key, bool cont)
{
    if (!curr)
        return;
    if (key < curr->data)
    { // Keep on searching for node to remove (to left)
        remove(curr->left, key, cont);
    }
    else if (key > curr->data)
    { // Keep on searching for node to remove (to right)
        remove(curr->right, key, cont);
    }
    else
    {
        if ((curr->count > 1) && (!cont))
        {
            curr->count--;
            return;
        }
        if ((curr->left == nullptr) && (curr->right == nullptr))
        { // If the node to delete is a leaf (no children)
            delete curr;
            curr = nullptr;
        }
        else if (curr->left != nullptr)
        { // has a left child or has two children
            Node *next = curr->left;
            // Find the largest node that is still smaller than the current node.
            // Go left once and then as much right as possible.
            while (next->right != nullptr)
                next = next->right;
            curr->data = next->data;
            curr->count = next->count;
            remove(curr->left, next->data, true);
        }
        else
        { // only has a right child
            Node *next = curr->right;
            // Find the smallest node that is larger than the current node
            // Go right once then as far left as possible
            while (next->left != nullptr)
                next = next->left;
            curr->data = next->data;
            curr->count = next->count;
            remove(curr->right, next->data, true);
        }
    }
}
//remove recursion
void BSTree::remove(const string &key)
{
    remove(root, key, false);
}


void BSTree::inOrder() const {
    inOrder(root);
}

void BSTree::preOrder() const {
    preOrder(root);
    
}

void BSTree::postOrder() const {
    postOrder(root);
    
}

void BSTree::preOrder(Node* node) const {
    if (node != nullptr) {
        //print helper
        cout << node->data << "(" << node->count << "), ";
        //left subtree
        preOrder(node->left);
        //right subtree
        preOrder(node->right);
        
    }
}

void BSTree::postOrder(Node* node) const {
    if (node != nullptr) {
        //traverse left sub
        postOrder(node->left);
        //traverse right sub
        postOrder(node->right);
        //print stack
        cout << node->data << "(" << node->count << "), ";
    }
}

void BSTree::inOrder(Node* node) const {
    if (node != nullptr) {
        //recursion to start from smallest node possible
        inOrder(node->left);
        //print helper
        cout << node->data << "(" << node->count << "), ";
        //recursion to then print larger values last
        inOrder(node->right);
    }
}