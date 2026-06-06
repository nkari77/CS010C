#pragma once
#include <string>

using namespace std;
class Node{
    public:
        //node constructor
        Node(string k);
        //node destructor
        ~Node();

        //value getter
        const string getKey();
        //node height getter
        const int getHeight();
        //node height setter
        void setHeight(int h);

        //left child setter
        void setLeft(Node* newLeft);
        //left child getter
        Node* getLeft();

        //right child setter
        void setRight(Node* newRight);
        //right child getter
        Node* getRight();
        

    protected:
        string key;
        Node *left;
        Node *right;
        int height;
};
