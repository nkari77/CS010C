#include <cstdlib>
#include <iostream>
#include "IntList.h"
//testing new pc git push
//test 2
using namespace std;

int main(){
    IntList newlist;
    cout << "list initialized" << endl;
    //push front check
    newlist.push_front(5);
    newlist.push_front(3);
    newlist.push_front(8);
    cout << "push front complete" << endl;
    cout << newlist << endl;

    //pop front check
    newlist.pop_front();
    cout << "front pop complete" << endl;
    cout << newlist << endl;

    //push back check
    newlist.push_back(192);
    newlist.push_back(1927);
    cout << "push back complete" << endl;
    cout << newlist << endl;

    //pop back check
    newlist.pop_back();
    newlist.pop_back();
    cout << "pop back complete" << endl;
    cout << newlist << endl;

    //print reverse check

    newlist.printReverse();
    
}