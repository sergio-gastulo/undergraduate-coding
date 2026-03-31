#include<iostream>
#include<sstream>


// array printer
void printArray(const int* pt, const int& size) {
    std::ostringstream oss;
    oss << "[";
    for(int i = 0; i < size - 1; i++)
        oss << pt[i] << ", ";
    oss << pt[size - 1] << "]" << std::endl;
    std::cout << oss.str();
}


// by default quickSort is implemented
int partition(int* pt, int low, int high) {
    int pivot = pt[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (pt[j] < pivot) {
            i++;
            std::swap(pt[i], pt[j]);
        }
    std::swap(pt[i + 1], pt[high]);
    return i + 1;
}
void quickSort(int* pt, int low, int high) {
    if (low < high) {
        int partition_index = partition(pt, low, high);
        quickSort(pt, low, partition_index - 1);
        quickSort(pt, partition_index + 1, high);
    }
}
void quickSort(int* pt, int dim) {
    quickSort(pt, 0, dim - 1);
}


// binary search in question
int binarySearch(int* pt, int dim, int search) {
    
    // sort the array first
    quickSort(pt, dim);
    int low = 0;
    int high = dim - 1;

    while (low <= high)
    {
        int middle = low + (high - low) / 2;

        if (pt[middle] == search)
            return middle;
        if (pt[middle] < search)
            low = middle + 1;
        else
            high = middle - 1;
    }
    return -1;
}

void search(int* pt, int dim, int search) {
    printArray(pt, dim);
    int res = binarySearch(pt, dim, search);
    printArray(pt, dim);
    if (res == -1) 
        std::cout   << "Couldn't find " << search 
                    << " on array argument." << std::endl;
    else 
        std::cout   << search << " was found at index " 
                    << res << "." << std::endl;
}


int main(int argc, char* argv[]) {
    int size = 10;
    int* arr = new int[size]{99, 10, 12, 15, 66, 88, 100, 30, -50, -20};
    search(arr, size, 10);
    delete[] arr;
    return 0; 
}