#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index){
    //store starting index as temp min
    unsigned int min = index;
    for(unsigned int i = index ; i < vals.size() ; ++i){
        //if curr value is smaller than min, set min to curr
        if (vals.at(i) < vals.at(min)){
            min = i;
        }
    }
    return min;
}

template<typename T>
void selection_sort(vector<T> &vals){
    //start at index 0 and swap min value to its location
    //keep iterating +1 until last value is reached, at which point all minimums should precede it
    for (unsigned int i = 0 ; i < vals.size() ; ++i){
        //store starting point and find min to swap
        int currMin = min_index(vals,i);

        //swap starting val with minimum
        auto temp = vals.at(i);
        vals.at(i) = vals.at(currMin);
        vals.at(currMin) = temp;
    }
}

template<typename T>
T getElement(vector<T> vals, int index){
    return vals.at(index);
}


vector<char> createVector(){
    //randomly decide vector size, max can be 26 (corresponds to num of letters)
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        //push back alphabetized values until rand size is reached
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){

    //create int vector for selection sort test
    vector<int> intVector;
    intVector.push_back(5);
    intVector.push_back(6);
    intVector.push_back(7);
    intVector.push_back(2);

    //create string vector for selection sort test
    vector<string> stringVector;
    stringVector.push_back("pear");
    stringVector.push_back("orange");
    stringVector.push_back("lettuce");
    stringVector.push_back("chicken");
    stringVector.push_back("tomato");
    stringVector.push_back("apple");

    //selection sort check on integer vector
    selection_sort(intVector);
    cout << "Sorted intVector is: ";
    for (unsigned int i = 0 ; i < intVector.size() ; ++i){
        cout << intVector.at(i) << " ";
    }
    cout << endl;

    //selection sort check on string vector
    selection_sort(stringVector);
    cout << "Sorted stringVector is: ";
    for (unsigned int i = 0 ; i < stringVector.size() ; ++i){
        cout << stringVector.at(i) << " ";
    }
    cout << endl;

    //Part B
    //random seeding
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    int size = vals.size();
    //continue prompting 10 times
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;
        try{
            //if index exceeds vector size, or is less that 0 throw exception
            if (index > size || index < 0){
                throw std::out_of_range("out of range exception occured");
            }
            else{
                //if index is valid, print element requested
                curChar = getElement(vals,index);
                cout << "Element located at " << index << ": is " << curChar << endl;
            }
        }
        //catch case for out of range exceptions
        catch(const std::out_of_range& excpt){
            cout << excpt.what() << endl;
        }
    }
    return 0;
}