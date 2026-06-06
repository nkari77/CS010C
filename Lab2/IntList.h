#pragma once
#include <iostream>
using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList {
    public:
        IntList();
        ~IntList();
        void push_front(const int value);
        void pop_front();
        void push_back(int value);
        void pop_back();
        bool empty() const;
        friend ostream & operator<<(ostream &out, const IntList &rhs);
        void printReverse() const;

    private:
        //rule of 3 copy consttructor, ensure that it is not used 
        IntList(const IntList&);
        IntNode* dummyHead;
        IntNode* dummyTail;
};