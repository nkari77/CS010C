#include "IntList.h"
#include <iostream>
#include <string>

//constructor (empty list with linked dummynodes)
IntList::IntList()
{
    //create dummy nodes
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);

    //establish empty list link
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;

    //create list end and list beginning
    dummyHead->prev = nullptr;
    dummyTail->next = nullptr;
}

//add value to front, key links are dummyhead->next to new and new->prev to dummyhead
void IntList::push_front(int value){
    //create new node to be added with value from param
    IntNode* pushnode = new IntNode(value);
    //if list is emtpy, link not only dummyhead but dummytail as well
    if (empty()){
        dummyHead->next = pushnode;
        dummyTail->prev = pushnode;

        pushnode->prev = dummyHead;
        pushnode->next = dummyTail;
    }
    else{
        //store old head to be linked with new head. old prev is new and new next is old
        IntNode* temp = dummyHead->next;
        dummyHead->next = pushnode;
        pushnode->next = temp;
        temp->prev = pushnode;
        pushnode->prev = dummyHead;
        //ensure no leak
        temp = nullptr;
    }
}

//remove head, if empty exception is thrown
void IntList::pop_front(){
    if (empty()){
        throw runtime_error("empty");
    }
    else{
        //store both head and new head, dummyhead will be linked to newhead while old is deleted
        IntNode* toRemove = dummyHead->next;
        IntNode* newHead = toRemove->next;

        //link dummy next to newhead and newhead prev to dummy
        dummyHead->next = newHead;
        newHead->prev = dummyHead;

        //deallocate old head
        delete toRemove;
    }
}

//push value to end of list, if empty link similarly to push_front
void IntList::push_back(int value){
    //create new node to be added with value from param
    IntNode* pushnode = new IntNode(value);
    if (empty()){
        dummyHead->next = pushnode;
        dummyTail->prev = pushnode;

        pushnode->prev = dummyHead;
        pushnode->next = dummyTail;
    }
    else{
        //store prior tail to be linked
        IntNode* temp = dummyTail->prev;
        dummyTail->prev = pushnode;
        pushnode->prev = temp;
        temp->next = pushnode;
        pushnode->next = dummyTail;
        temp = nullptr;
    }
}

//remove tail, if empty exception is thrown
void IntList::pop_back(){
    if (empty()){
        throw runtime_error("empty");
    }
    else{
        //store tail and tail prev. tail prev will be the new tail (linked to dummytail) while old tail is deallocated
        IntNode* toRemove = dummyTail->prev;
        IntNode* newTail = toRemove->prev;

        dummyTail->prev = newTail;
        newTail->next = dummyTail;

        //deallocate old tail
        delete toRemove;
    }
}

//iterate through links from tail to head, using PREV as iterator
void IntList::printReverse() const{
    IntNode* outputNode = dummyTail->prev;
    //while the prev of the current node isnt null (aka the current output node isnt the dummyHead)
    while (outputNode->prev != nullptr){
        //if not last item, print space
        if (outputNode != dummyHead->next){
            cout << outputNode->data << " ";
        }
        //if last value in list no space
        if (outputNode == dummyHead->next){
            cout << outputNode->data;
        }
        outputNode = outputNode->prev;
    }
}

//if the head next is the dummytail, this means there are no nodes in the list (return false), else return true
bool IntList::empty() const{
    //check if dummyhead next points to dummytail aka list is linked to nothing
    return  dummyHead->next == dummyTail;
}

//overloaded operator, same logic as print reverse except goes from head to tail, and utilizes friend functionality to access private vars
ostream & operator<<(ostream &out, const IntList &rhs){
    cout << "reached ostream" << endl;
    IntNode* outputNode = rhs.dummyHead->next;
    while (outputNode->next != nullptr){
        //if not last item, print space
        if (outputNode != rhs.dummyTail->prev){
            out << outputNode->data << " ";
        }
        //if last value in list no space
        if (outputNode == rhs.dummyTail->prev){
            out << outputNode->data;
        }
        outputNode = outputNode->next;
    }
    return out;
}

//while list is not empty, continue to pop from back of list until fully deallocated
IntList::~IntList(){
    while(!empty()){
        pop_back();
    }
}
