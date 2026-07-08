#include<chrono>
#include<iostream>
#include<sstream>
#include<random>


double** generateRandomArray(const int& size) {
    // set randomness
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    
    // create random array
    double** pt = new double*[size];
    for(unsigned int i = 0; i < size; i++){
        pt[i] = new double;
        *(pt[i]) = uniform(rng);
    }
    return pt;
}

void printArray(double** pt, const int& size) {
    std::ostringstream oss;
    oss << "[";
    for(int i = 0; i < size - 1; i++)
        oss << *(pt[i]) << ", ";
    oss << *(pt[size - 1]) << "]" << std::endl;
    std::cout << oss.str();
}


void bubbleSort(double** pt, const int& size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size - 1; j++)
            if (*pt[j] > *pt[j + 1])
                std::swap(pt[j], pt[j + 1]);
}


void insertionSortTemp(double** pt, const int& size) {
    for (int i = 0; i < size; i++){
        double* tmp = pt[i];
        int j = i - 1;
        while (j > 0 && *pt[j] > *tmp) {
            pt[j + 1] = pt[j];
            j--;
        }
        pt[j + 1] = tmp; 
    }
}
void insertionSort(double** pt, const int& size) {
    for (int i = 0; i < size; i++){
        int j = i;
        while (j > 0 && *pt[j - 1] > *pt[j]) {
            std::swap(pt[j - 1], pt[j]);
            j--;
        }
    }
}


void selectionSort(double** pt, const int& size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
            if (*pt[j] < *pt[min_index])
                min_index = j;
        std::swap(pt[i], pt[min_index]);
    }
}


int partition(double** pt, int low, int high) {
    double pivot = *pt[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
        if (*pt[j] < pivot) {
            i++;
            std::swap(pt[i], pt[j]);
        }
    std::swap(pt[i + 1], pt[high]);
    return i + 1;
}
void quickSort(double** pt, const int& low, const int& high) {
    if (low < high) {
        int pivot_index = partition(pt, low, high);
        quickSort(pt, low, pivot_index - 1);
        quickSort(pt, pivot_index + 1, high);
    }
}
void quickSort(double** pt, const int& size) {
    quickSort(pt, 0, size - 1);
}


void free(double** pt, const int& size) {
    for (int i = 0; i < size; i++)
        delete pt[i];
    delete[] pt;
}


// https://stackoverflow.com/a/22387757/29272030
void timing(const int& array_size, void (*sort)(double**, const int&)) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    
    double** array = new double*[array_size];
    array = generateRandomArray(array_size);
    printArray(array, array_size);
    auto t1 = high_resolution_clock::now();
    sort(array, array_size);
    auto t2 = high_resolution_clock::now();
    
    printArray(array, array_size);
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Array sorted in " << ms_double.count() << "ms." << std::endl;
    free(array, array_size);
}


int main(int argc, char* argv[]) {

    int array_size;
    if (argc > 0) {
        std::cout << "Setting array_size to " << argv[1] << "."  << std::endl;
        array_size = std::strtol(argv[1], NULL, 10);
    } else {
        array_size = 10;
    }

    timing(array_size, static_cast<void(*)(double**, const int&)>(&quickSort));
    return 0;
}