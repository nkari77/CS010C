#include "PrintJob.h"

PrintJob::PrintJob ( int setP, int setJ, int numP ):priority(setP), jobNumber(setJ), numPages(numP){}
//getters for printjobs
int PrintJob::getPriority ( ){
    return priority;
}

int PrintJob::getJobNumber ( ){
    return jobNumber;
}

int PrintJob::getPages ( ){
    return numPages;
}

//setters for printjobs
void PrintJob::setPriority(int val){
    priority = val;
}

void PrintJob::setJobNumber(int val){
    jobNumber = val;
}

void PrintJob::setPages(int val){
    numPages = val;
}