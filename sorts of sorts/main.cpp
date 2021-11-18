#include <iostream>
#include <forward_list>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>
#include <algorithm>

using namespace std;

int* generateRandomArray(const int& size) // generate an (unsorted) array consisting of size distinct integers in [0, size)
{
    srand(time(NULL));
    int* arr = new int[size];
    int i = 0;
    for_each(arr, arr + size, [&](int& x){x = i++;});
    random_shuffle(arr, arr + size);
    return arr;
}

void printArray(int* arr, int size) // iterately print elements of the given array
{
    for_each(arr, arr + size, [](int x){cout << x << ' ';});
    cout << endl;
}

void insertionSort(int* arr, int size) // O(n^2), adaptive(benefitial to running time of almost sorted array)
{
    forward_list<int> l (1, arr[0]);
    for(int i = 1; i < size; i++)
    {
        l.emplace_front(arr[i]);
        auto it1 = l.begin(), it2 = l.begin();
        ++it2;

        while(it2 != l.end() && *it1 > *it2)
        {
            int temp = *it1;
            *it1 = *it2;
            *it2 = temp;
            ++it1;
            ++it2;
        }
    }

    auto it3 = l.begin();
    for_each(arr, arr + size, [&](int& x){x = *it3++;});
}

void mergeSort(int* arr, int from, int to) // O(nlogn), from the first index of the array to the last 
{ 
    if(from != to)
    {
        int middle = (from + to) / 2; 
        mergeSort(arr, from, middle);
        mergeSort(arr, middle + 1, to);
        queue<int> sortedQueue;
        int i = from, j = middle + 1;
        for(int k = 0; k < to - from + 1; k++)
        {
            if(i <= middle && j <= to)
            {
                arr[i] <= arr[j] ? sortedQueue.push(arr[i++]): sortedQueue.push(arr[j++]);
            }
            else
            {
                i > middle ? sortedQueue.push(arr[j++]): sortedQueue.push(arr[i++]);
            }
        }
        for(int k = 0; k < to - from + 1; k++)
        {
            arr[k + from] = sortedQueue.front();
            sortedQueue.pop();
        }
    }
}

int main()
{
    int size = 20;

    // insertion sort
    int* arr = generateRandomArray(size);
    printArray(arr, size);
    insertionSort(arr, size);
    printArray(arr, size);
    cout << endl;

    // merge sort
    arr = generateRandomArray(size);
    printArray(arr, size);
    mergeSort(arr, 0, size - 1);
    printArray(arr, size);
    cout << endl;

    cin.get();
}
