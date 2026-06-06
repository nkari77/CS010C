#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 20;
//templating for class, ensures integer and string stacks are supported
template <typename T>
class stack{

    private:
        //initial empty arry with unsigned size
        T data[MAX_SIZE];
        unsigned int size;
    
    public:
        //default construction of empty, size 0 array (max posssible size 20)
        stack()
        : size(0){}

        //add an element to the stack, will be placed on rightmost side of the array, aka the "Top" of the stack
        void push(T val){
            try{
                //check if after pushing the full size is achieved
                if(size+1 > MAX_SIZE){
                    throw overflow_error("Push called on full stack");
                }
                //otherwise push as normal but adding a new value and incrementing size
                else{
                    data[size] = val;
                    size += 1;
                }
            }
            //display exception is overflow occurs (pushing to full)
            catch(const std::overflow_error& excpt){
            cout << excpt.what() << endl;
            }
        }

        //pop the top element of the stack
        void pop(){
            try{
                //check if stack is empty
                if(size == 0){
                    throw out_of_range("Called pop on empty stack");
                }
                //otherwise remove the top element and decrement size
                else{
                    data[size-1] = 0;
                    size -= 1;
                }
            }
        }

        //pop the top two elements of the stack
        void pop_two(){
            try{
                //if empty stack, throw empty exception
                if(size == 0){
                    throw out_of_range("Called pop_two on empty stack");
                }
                //if size 1 stack, throw size 1 exception
                else if(size == 1){
                    throw out_of_range("Called pop_two on stack of size 1");
                }
                //otherwise, clear top two vals and decrement size accordingly
                else{
                    data[size-1] = 0;
                    data[size-2] = 0;
                    size -= 2;
                }
            }
            //throw exceptions if stack contains less that 2 poppable elements
            catch(const std::out_of_range& excpt){
            cout << excpt.what() << endl;
            }
        }

        //return top value of stack
        T top(){
            return data[size-1];

        }

        //check if stack is empty through size var
        bool empty(){
            if(size == 0){
                return true;
            }
            else{
                return false;
            }
        }
};
