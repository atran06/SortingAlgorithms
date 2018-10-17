/*************************************************************************
 * Project 5
 *
 * Filename: main.cpp
 * Description: Implements and tests selection sort, insertion sort,
 *              merge sort, and quick sort.
 * Name: Arthur Tran
 * Date: 10-12-18
 *************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "53Stopwatch.h"

using namespace std;

/*
 * Function: swapElements()
 * Desc: Swaps two elements in an array.
 * Params:
 *   arr - Pointer to an array
 *   size - Size of array
 *   index1 - The first index to swap
 *   index2 - The second index to swap
 * Returns: void
 */
void swapElements(int* arr, int index1, int index2) {
     int temp = arr[index1];
     arr[index1] = arr[index2];
     arr[index2] = temp;
}

/*
 * Function: createArray()
 * Desc: Dynamically allocates an array of integers
 *       and fills each slot with a random integer between
 *       1 and 1000.
 * Params:
 *   size - Size of array
 * Returns: The pointer to the array
 */
int* createArray(int size) {
     int* arr = new int[size];

     for(int i = 0; i < size; i++) {
          arr[i] = (rand() % 1000) + 1;
     }

     return arr;
}

/*
 * Function: insertionSort()
 * Desc: Runs the insertion sort algorithm.
 * Params:
 *   arr - Pointer to an array
 *   size - Size of the array
 * Returns: void
 */
void insertionSort(int* arr, int size) {
     for(int i = 1; i < size; i++) {
          int j = i;

          while(j > 0 && arr[j] < arr[j - 1]) {
               swapElements(arr, j, j - 1);
               j--;
          }
     }
}

/*
 * Function: selectionSort()
 * Desc: Runs the selection sort algorithm.
 * Params:
 *   arr - Pointer to an array
 *   size - Size of the array
 * Returns: void
 */
void selectionSort(int * arr, int size) {
     for(int i = 0; i < size; i++) {
          int smallestIndex = i;

          for(int x = i + 1; x < size; x++) {
               if(arr[x] < arr[smallestIndex]) smallestIndex = x;
          }

          swapElements(arr, i, smallestIndex);
     }
}

/*
 * Function: merge()
 * Desc: Utility function for mergeSort() that splits given array
 *       into two halves and merges them back in sorted order.
 * Params:
 *   arr - Pointer to an array.
 *   left - Left bound of the array.
 *   middle - Middle of the array.
 *   right - Right bound of the array.
 * Returns: void
 */
void merge(int* arr, int left, int middle, int right) {
     int i, x, k; //indexes for loops
     int tempArray1Size = middle - left + 1;
     int tempArray2Size = right - middle;

     int tempArray1[tempArray1Size];
     int tempArray2[tempArray2Size];

     //copies the halves of the array into the temp arrays
     for(i = 0; i < tempArray1Size; i++) {
          tempArray1[i] = arr[i + left];
     }
     for(int x = 0; x < tempArray2Size; x++) {
          tempArray2[x] = arr[middle + 1 + x];
     }

     i = 0;
     x = 0;
     k = left;

     while(i < tempArray1Size && x < tempArray2Size) {
          if (tempArray1[i] <= tempArray2[x]) {
               arr[k] = tempArray1[i];
               i++;
          } else {
               arr[k] = tempArray2[x];
               x++;
          }
          k++;
     }
     while(i < tempArray1Size) {
          arr[k] = tempArray1[i];
          i++;
          k++;
     }
     while(x < tempArray2Size) {
          arr[k] = tempArray2[x];
          x++;
          k++;
     }
}

/*
 * Function: mergeSort()
 * Desc: Recursively splits an array into halves and calls on
 *       merge() to merge them into sorted order.
 * Params:
 *   arr - Pointer to an array.
 *   left - Left bound of the array.
 *   right - Right bound of the array.
 * Returns: void
 */
void mergeSort(int* arr, int left, int right) {
     if(left < right) {
          int middle = (left + right) / 2;

          mergeSort(arr, left, middle);
          mergeSort(arr, middle + 1, right);

          merge(arr, left, middle, right);
     }
}

/*
 * Function: partition()
 * Desc: Utility function for quickSort() that partitions a given array according
 *       to a specific pivot point. (in this case is the last element in the array)
 * Params:
 *   arr - Pointer to an array.
 *   low - Left bound of the array.
 *   high - Right bound of the array.
 * Returns: Returns the index of where the array is partitioned.
 */
int partition(int* arr, int low, int high){
     int pivotIndex = high; //uses the last element in the array as a pivot

     int leftIndex = low;
     int rightIndex = pivotIndex;

     while(leftIndex < rightIndex) {
          while(arr[leftIndex] <= arr[pivotIndex] && leftIndex < rightIndex) {
               leftIndex++;
          }
          while(arr[rightIndex] >= arr[pivotIndex] && leftIndex < rightIndex) {
               rightIndex--;
          }
          if(leftIndex < rightIndex) swapElements(arr, leftIndex, rightIndex);
     }
     swapElements(arr, leftIndex, pivotIndex);

     return rightIndex;
}

/*
 * Function: quickSort()
 * Desc: Recursively arranges an array into halves that are larger or smaller
 *       than a certain pivot point.
 * Params:
 *   arr - Pointer to an array.
 *   low - Left bound of the array.
 *   high - Right bound of the array.
 * Returns: void
 */
void quickSort(int* arr, int low, int high) {
     if(low < high) {
          int split = partition(arr, low, high);

          quickSort(arr, low, split - 1);
          quickSort(arr, split + 1, high);
     }
}

/*
 * Function: writeToFile()
 * Desc: Appends a specifed string to the end of a specified file.
 * Params:
 *   filename- Filename to open and write to
 *   toWrite - The string to write
 * Returns: void
 */
void writeToFile(string filename, string toWrite) {
     ofstream outputFileStream;

     outputFileStream.open(filename, fstream::app); //appends to the end of the file
     if(!outputFileStream.is_open()) {
          cout << "Can't open " << filename << endl;
          return;
     }
     outputFileStream << toWrite << endl;
     outputFileStream.close();
}

/*
 * Function: clearFile()
 * Desc: Deletes contents of specified file.
 * Params:
 *   filename- Filename to open and write to
 * Returns: void
 */
void clearFile(string filename) {
     ofstream outputFileStream;

     outputFileStream.open(filename, fstream::trunc);
     if(!outputFileStream.is_open()) {
          cout << "Can't open " << filename << endl;
          return;
     }

     outputFileStream.close();
}

/*
 * Function: isSorted()
 * Desc: Utility function to check if the given array is sorted.
 * Params:
 *   arr - Pointer to an array
 *   size - Size of array
 * Returns: True if array is sorted false otherwise.
 */
bool isSorted(int* arr, int size) {
     for(int i = 1; i < size; i++) {
          if(arr[i - 1] > arr[i]) return false;
     }
     return true;
}

/*
 * Function: runTest()
 * Desc: Creates a new array of random ints and runs it through
 *       a specified sorting algorithm and records it's time.
 * Params:
 *   algorithm - Algorithm to run.
 *   timesToRun - Number of times to run the test.
 *   arraySize - The size of the array to test.
 * Returns: void
 */
void runTest(string algorithm, int timesToRun, int arraySize) {
     cout << endl;
     const double MILLIS_IN_SEC = 1000;
     Stopwatch stopwatch;

     if(algorithm == "insertion sort") {
          double insertionSortSum = 0;

          for(int i = 0; i < timesToRun; i++) {
               int* arr = createArray(arraySize);

               cout << "Running insertion sort " << i + 1 << endl;
               stopwatch.reset();
               insertionSort(arr, arraySize);
               insertionSortSum += stopwatch.recordTime();

               delete[] arr;
          }

          int insertionSortAverage = (insertionSortSum * MILLIS_IN_SEC) / timesToRun;

          cout << "Insertion sort took an average of " << insertionSortAverage << " milliseconds to sort " << arraySize << " numbers" << endl;

          writeToFile("results.txt", "Insertion sort: " + to_string(arraySize) + " elements took an average of " + to_string(insertionSortAverage)
               + " milliseconds across " + to_string(timesToRun) + " test(s)");

     } else if(algorithm == "selection sort") {
          double selectionSortSum = 0;

          for(int i = 0; i < timesToRun; i++) {
               int* arr = createArray(arraySize);

               cout << "Running selection sort " << i + 1 << endl;
               stopwatch.reset();
               selectionSort(arr, arraySize);
               selectionSortSum += stopwatch.recordTime();

               delete[] arr;
          }

          int selectionSortAverage = (selectionSortSum * MILLIS_IN_SEC) / timesToRun;

          cout << "Insertion sort took an average of " << selectionSortAverage << " milliseconds to sort " << arraySize << " numbers" << endl;

          writeToFile("results.txt", "Selection sort: " + to_string(arraySize) + " elements took an average of " + to_string(selectionSortAverage)
               + " milliseconds across " + to_string(timesToRun) + " test(s)");

     } else if(algorithm == "merge sort") {
          double mergeSortSum = 0;

          for(int i = 0; i < timesToRun; i++) {
               int* arr = createArray(arraySize);

               cout << "Running merge sort " << i + 1 << endl;
               stopwatch.reset();
               mergeSort(arr, 0, arraySize - 1);
               mergeSortSum += stopwatch.recordTime();

               delete[] arr;
          }

          int mergeSortAverage = (mergeSortSum * MILLIS_IN_SEC) / timesToRun;

          cout << "Merge sort took an average of " << mergeSortAverage << " milliseconds to sort " << arraySize << " numbers" << endl;

          writeToFile("results.txt", "Merge sort: " + to_string(arraySize) + " elements took an average of " + to_string(mergeSortAverage)
               + " milliseconds across " + to_string(timesToRun) + " test(s)");

     } else if(algorithm == "quick sort") {
          double quickSortSum = 0;

          for(int i = 0; i < timesToRun; i++) {
               int* arr = createArray(arraySize);

               cout << "Running quick sort " << i + 1 << endl;
               stopwatch.reset();
               quickSort(arr, 0, arraySize - 1);
               quickSortSum += stopwatch.recordTime();

               delete[] arr;
          }

          int quickSortAverage = (quickSortSum * MILLIS_IN_SEC) / timesToRun;

          cout << "Quick sort took an average of " << quickSortAverage << " milliseconds to sort " << arraySize << " numbers" << endl;

          writeToFile("results.txt", "Quick sort: " + to_string(arraySize) + " elements took an average of " + to_string(quickSortAverage)
               + " milliseconds across " + to_string(timesToRun) + " test(s)");

     } else {
          cout << "Can't run " << algorithm << endl;
     }
}

/*
 * Function: runAllTests()
 * Desc: Runs each algorithm a specified number of times then
 *       records the average.
 * Params:
 *   timesToRun - Number of times to run the test.
 *   arraySize - The size of the array to test.
 * Returns: void
 */
void runAllTests(int timesToRun, int arraySize) {
     runTest("insertion sort", timesToRun, arraySize);
     runTest("selection sort", timesToRun, arraySize);
     runTest("merge sort", timesToRun, arraySize);
     runTest("quick sort", timesToRun, arraySize);
}

void runProjectRequirementTests() {
     for(int i = 20000; i <= 640000; i *= 2) {
          runTest("insertion sort", 1, i);
          runTest("selection sort", 1, i);
          runTest("merge sort", 1, i);
          runTest("quick sort", 1, i);
     }
}


/*
 * Function: print()
 * Desc: Prints each elements in a specified array.
 * Params:
 *   arr - Pointer to an array
 *   size - Size of the array
 * Returns: void
 */
void print(int* arr, int size) {
     for(int i = 0; i < size; i++) {
          cout << arr[i] << " ";
     }
     cout << endl;
}

int main() {
     clearFile("results.txt"); //clears the save file
     // runAllTests(3, 50000); //tests every algorithm
     //
     // const int SIZE = 20;
     // int* arr = createArray(SIZE);
     //
     // runTest("merge sort", 5, 100000); //tests only one algorithm
     //
     // delete[] arr;

     runProjectRequirementTests();
     return 0;
}
