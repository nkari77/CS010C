#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"

using namespace std;

class AVLTree{
    public:
    //default tree constructor
        AVLTree(){
            root = nullptr;
        };
        void insert(const string &);
        int balanceFactor(Node*);
        void printBalanceFactors();
        void visualizeTree(const string &);
    private:
        Node* root;
        int height(Node* node);
        Node* insert(Node* insertNode, string key);
        Node* rotate(Node* rotateNode, string key, int balance);
        void printBalanceFactors(Node* node);
        //dotty file producer
        void visualizeTree(ofstream &, Node*);
        Node* rightRotate(Node* rPoint);
        Node* leftRotate(Node* lPoint);
        int maxFinder(int a, int b);

};