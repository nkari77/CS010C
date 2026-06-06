#include <iostream>
#include <ctime>

const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
const int NUMBERS_SIZE = 50000;

using namespace std;

//generate random integers
int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}

//populate the arrays passed in with 50000 random ints
void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for (int i = 0; i < NUMBERS_SIZE; ++i) {
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

//midpoint pivot quicksort partition
int partition_midpoint(int numbers[], int i, int k) {
    int pivot = numbers[(i + k) / 2]; // pivot is the midpoint
    int left = i;
    int right = k;

    while (left <= right) {
        //find the left and right edge points inwards towards the pivot
        while (numbers[left] < pivot){
            left++;
        }
            
        while (numbers[right] > pivot){
            right--;
        }
        //if left is greater than right, swap their values
        if (left <= right) {
            int temp = numbers[left];
            numbers[left] = numbers[right];
            numbers[right] = temp;
            left++;
            right--;
        }
    }

    return left;
}

//quicksorter using midpoint
void Quicksort_midpoint(int numbers[], int i, int k) {
    //left edge cannot be greater than right
    if (i >= k){
        return;
    }

    //determine partition point
    int index = partition_midpoint(numbers, i, k);

    //recurisvely call on the 2 generated subarrays with partition point
    Quicksort_midpoint(numbers, i, index - 1);
    Quicksort_midpoint(numbers, index, k);
}

//median of three quicksort pivot partition
int partition_medianOfThree(int numbers[], int i, int k) {
    int pivot;
    int mid = (i + k) / 2;

    //if left edge is greater than the mid
    if (numbers[i] < numbers[mid]) {
        //if the mid is less than the right edge
        if (numbers[mid] < numbers[k]){
            pivot = mid;
        }
        //else if the left edge is less than right, the pivot becomes the right edge
        else if (numbers[i] < numbers[k]){
            pivot = k;
        }
        //last case, pivot becomes i
        else{
            pivot = i;
        }
    } else {
        //left edge median, set as pivot
        if (numbers[i] < numbers[k]){
            pivot = i;
        }
        //right edge median, set as pivot
        else if (numbers[mid] < numbers[k]){
            pivot = k;
        }
        //else mid is median
        else{
            pivot = mid;
        }
    }

    //swap pivot with last element
    int temp = numbers[pivot];
    numbers[pivot] = numbers[k];
    numbers[k] = temp;

    pivot = numbers[k];
    int left = i;
    int right = k - 1;

    while (left <= right) {
        //iterate left to right until element greater than pivot is found
        while (left <= right && numbers[left] <= pivot){
            left++;
        }
        //iterate right to left until element greater than pivot is found       
        while (right >= left && numbers[right] >= pivot){
            right--;
        }
        if (left < right) {
            //swap left and right position elements
            int temp = numbers[left];
            numbers[left] = numbers[right];
            numbers[right] = temp;
        }
    }

    //swap pivot back
    temp = numbers[left];
    numbers[left] = numbers[k];
    numbers[k] = temp;

    return left;
}

//quicksorter using median of three
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i >= k){
        return;
    }

    //determine partition point
    int index = partition_medianOfThree(numbers, i, k);

    //recursively call quicksort on generated subarrays from parition point
    Quicksort_medianOfThree(numbers, i, index - 1);
    Quicksort_medianOfThree(numbers, index + 1, k);
}

//insertion sort
void InsertionSort(int numbers[], int numbersSize) {
    for (int i = 1 ; i < numbersSize ; i++) {
        //find key to be inserted
        int key = numbers[i];
        //determine position
        int j = i - 1;

        while (j >= 0 && numbers[j] > key) {
            //shift larger elements right for insert
            numbers[j + 1] = numbers[j];
            j--;
        }
        //insert key into correctly sorted position
        numbers[j + 1] = key;
    }
}

//time elapsed display
int main() {
    //alloc arrays
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    //popullate arrays
    fillArrays(arr1, arr2, arr3);

    //timer vars
    clock_t start, end;
    int elapsedTime;

    //midpoint pivot quicksort timer
    start = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE - 1);
    end = clock();
    elapsedTime = (end - start) / CLOCKS_PER_MS;
    cout << "Quicksort_midpoint elapsed time: " << elapsedTime << " milliseconds" << endl;

    //median of three quicksort timer
    start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE - 1);
    end = clock();
    elapsedTime = (end - start) / CLOCKS_PER_MS;
    cout << "Quicksort_medianOfThree elapsed time: " << elapsedTime << " milliseconds" << endl;

    //insertion sort timer
    start = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    end = clock();
    elapsedTime = (end - start) / CLOCKS_PER_MS;
    cout << "InsertionSort elapsed time: " << elapsedTime << " milliseconds" << endl;

    return 0;
}
