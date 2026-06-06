#include "Heap.h"
#include <iostream>
#include <stdexcept>
using namespace std;
//default constructor
Heap::Heap()
: numItems(0){}

void Heap::enqueue(PrintJob* job){
    if (numItems < MAX_HEAP_SIZE){
        //if empty just add new job
        if(!numItems){
            arr[numItems] = job;
            ++numItems;
        }
        else{
            int currItem = numItems; //initialize location to last job
            //while not at first item, keep halving until priority is in order (find location for new printjob insert)
            while (currItem > 0 && arr[(currItem - 1) / 2]->getPriority() < job->getPriority() ){
                //last item becomes val of mid
                arr[currItem] = arr[(currItem-1)/ 2];
                currItem = (currItem-1) / 2;
            }
            arr[currItem] = job; //place job into location with proper priority
            ++numItems;
        }
    }
    else{
        return;
        //throw exception for full queue
        //throw overflow_error("Overflow Error: Enqeue attempted on full queue");
    }
}

void Heap::dequeue(){
    if(!numItems){
        //throw underflow_error("Underflow Error: Deqeue attempted on empty queue");
        return;
    }

    if (numItems > 2 && arr[1]->getPriority() < arr[numItems-1]->getPriority() && arr[2]->getPriority() < arr[numItems-1]->getPriority()){
        //first item swaps for dequeue item
        arr[0] = arr[numItems-1];
        --numItems;
    }
    else{
        //downsort, decrement
        trickleDown(0);
        --numItems;
    }
}

PrintJob* Heap::highest(){
    if (!numItems){
        //throw runtime_error("Heap is empty");
        return nullptr;
    }
    return arr[0];
}

void Heap::print(){
    cout << "Priority: " << arr[0]->getPriority();
    cout << ", Job Number: " << arr[0]->getJobNumber();
    cout << ", Number of Pages: " << arr[0]->getPages() << endl;
}

void Heap::trickleDown(int num){ 
    if (((2 * num + 1) < numItems) && (2 * num + 2 < numItems)){
        //check case for 2 children on current node
        if (arr[2*num+1]->getPriority() > arr[2*num+2]->getPriority()){
            arr[num] = arr[2*num + 1];
            trickleDown(2*num +1);
        }
        //if right child has greater prio than left
        else{
            arr[num] = arr[2*num+2];
            trickleDown(2*num +2);
        }
    }
    //only left child exists
    else if (((2*num + 1)) < numItems){
        arr[num] = arr[2*num+1];
    }
    return;
}