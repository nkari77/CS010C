#pragma once
#include <string>
using namespace std;
class Node{
    public:
    string data;
    int count;
    Node* left;
    Node* right;

    Node(const string& data);
    ~Node();

};