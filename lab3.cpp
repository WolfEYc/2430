#include "ArgumentManager.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

int mergeit = 0, selectit=0,insertit=0,quickit=0,bubbleit=0;


int partition(vector<int>& values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = values[pivotIndex];
    int i = left, j = right;
    int temp;
    while (i <= j) {
        while (values[i] < pivotValue) {
            i++;
        }
        while (values[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
        quickit++;
    }
    return i;
}
void quicksort(vector<int>& values, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

vector<int> insertionSort(vector<int> arr)
{
    int n = arr.size();
    vector<int> temp=arr;
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = temp[i];
        j = i - 1;
        insertit++;
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && temp[j] > key)
        {
            temp[j + 1] = temp[j];
            j = j - 1;
            insertit++;
        }
        temp[j + 1] = key;
    }
    return temp;
}

vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    while ((int)left.size() > 0 || (int)right.size() > 0) {
        if ((int)left.size() > 0 && (int)right.size() > 0) {
            if ((int)left.front() <= (int)right.front()) {
                result.push_back((int)left.front());
                left.erase(left.begin());
            }
            else {
                result.push_back((int)right.front());
                right.erase(right.begin());
            }
        }
        else if ((int)left.size() > 0) {
            for (int i = 0; i < (int)left.size(); i++)
                result.push_back(left[i]);
            break;
        }
        else if ((int)right.size() > 0) {
            for (int i = 0; i < (int)right.size(); i++)
                result.push_back(right[i]);
            break;
        }
        mergeit++;
    }
    return result;
}

vector<int> mergeSort(vector<int> m)
{
    if (m.size() <= 1)
        return m;

    vector<int> left, right, result;
    int middle = ((int)m.size() + 1) / 2;

    for (int i = 0; i < middle; i++) {
        left.push_back(m[i]);
    }

    for (int i = middle; i < (int)m.size(); i++) {
        right.push_back(m[i]);
    }

    left = mergeSort(left);
    right = mergeSort(right);
    result = merge(left, right);

    return result;
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

vector<int> selectionSort(vector<int> arr, int n)
{
    vector<int> temp = arr;
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n - 1; i++)
    {
        
        // Find the minimum element in unsorted array  
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            selectit++;
            if (temp[j] < temp[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element with the first element  
        swap(temp[min_idx],temp[i]);
    }
    return temp;
}

vector<int> bubblesort(vector<int> arr) {
    vector<int> joe = arr;
    for (int i = 0; i < joe.size() - 1; i++) {
        bubbleit++;
        for (int j = 0; j < joe.size() - i - 1; j++) {
            if (joe[j] > joe[j+1]) {
                int temp = joe[j];
                joe[j] = joe[j+1];
                joe[j+1] = temp;
            }
            bubbleit++;
        }
    }
    return joe;
}

void print(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << endl;
	}
	ArgumentManager am(argc, argv);
	ifstream input(am.get("input"));
	ofstream output(am.get("output"));

    time_t start, end;
    vector<int> arr;
    vector<int> sortedarr;
    string temp;
    int size;

    input >> temp;
    try {
        size = stoi(temp);
    }
    catch (...) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        input >> temp;
        arr.push_back(stoi(temp));
    }





   
    cout << endl;    
    sortedarr = bubblesort(arr);
    cout << "bubble";
    print(sortedarr);

    sortedarr = mergeSort(arr);
    cout << "merge";
    print(sortedarr);

    sortedarr = selectionSort(arr, arr.size());
    cout << "selection";
    print(sortedarr);

    sortedarr = insertionSort(arr);
    cout << "insertion";
    print(sortedarr);

    quicksort(arr,0,arr.size()-1);
    cout << "quick";
    print(arr);

    cout << endl;
    cout << mergeit << " "<< selectit << " " << insertit << " " <<quickit<< " " <<bubbleit;

    

    if (quickit < mergeit && mergeit < insertit && insertit < selectit && selectit<bubbleit ) {
        output << "Quick Sort, Merge Sort, Insertion Sort, Selection Sort, Bubble Sort";
    }
    else {
        output << "something went womng";
    }


    return 0;
}
