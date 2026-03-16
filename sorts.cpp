#include "sorts.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <class T>
void Swap(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}

void GenerateRandomData(int a[], int n) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        a[i] = rand()%n;
    }
}

void GenerateSortedData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

void GenerateReverseData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    srand((unsigned int) time(NULL));
    for (int i = 0; i < 10; i ++) {
        int r1 = rand()%n;
        int r2 = rand()%n;
        Swap(a[r1], a[r2]);
    }
}

void GenerateData(int a[], int n, int dataType) {
    switch (dataType) {
    case 0: GenerateRandomData(a, n); break;
    case 1: GenerateSortedData(a, n); break;
    case 2: GenerateReverseData(a, n); break;
    case 3: GenerateNearlySortedData(a, n); break;
    default: printf("Error: unknown data type!\n");
    }
}

bool isNumber(const string& str) {
    for (char const &c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

int getOrderType(string order) {
    if (order == "-rand") return 0;
    if (order == "-sorted") return 1;
    if (order == "-rev") return 2;
    if (order == "-nsorted") return 3;
    return -1;
}

void readFromFile(string filename, int*& a, int& n) {
    ifstream f(filename);
    if (f.is_open()) {
        f >> n;
        a = new int[n];
        for (int i = 0; i < n; ++i) f >> a[i];
        f.close();
    }
}

void writeToFile(string filename, int a[], int n) {
    ofstream f(filename);
    if (f.is_open()) {
        f << n << "\n";
        for (int i = 0; i < n; ++i) f << a[i] << " ";
        f.close();
    }
}

void selectionSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    for (int i = 0;++comp && i < n - 1; i++) {

        int min_idx = i;
        for (int j = i + 1; ++comp && j < n; j++) {
            if (++comp && a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        swap(a[min_idx], a[i]);
    }
}

void insertionSort(int a[], int n, unsigned long long& comp){
    comp = 0;
    for (int i = 1; ++comp && i < n; i++){
        int num = a[i];
        int j = i-1;
        while (++comp && ++comp &&j >= 0 && a[j] > num){
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = num;
    }
}

void binaryinsertionSort(int a[], int n, unsigned long long& comp){
    comp = 0;
    for (int i = 1; ++comp && i < n; ++i){
        int key = a[i];
        int first = 0, last = i - 1;
        while (++comp,first <= last) {
            int m = (first + last) / 2;
            if (++comp,key < a[m]) last = m - 1;
            else first = m + 1;
        }
        for (int j = i - 1; ++comp && j >= first; --j)
            a[j + 1] = a[j];
        a[first] = key;
    }
}

void bubbleSort(int a[], int n, unsigned long long& comp){
    comp = 0;
    for (int pass = 1;++comp && pass < n; ++pass){
        bool checked = true;
        for (int j = 0;++comp && j < n - pass; ++j){
            if (++comp,a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                checked = false;
            }
        }
        if(checked){
            return;
        }
    }
}

void shakerSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    int left = 1,right = n - 1,k = 0;
    do {
        k = 0;
        for (int j = left;++comp, j <= right; ++j) {
            if (++comp, a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
                k = j;
            }
        }
        right = k - 1; 
        for (int j = right;++comp, j >= left; --j) {
            if (++comp, a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
                k = j;
            }
        }
        left = k + 1; 
    } while (++comp,left <= right && ++comp,k > 0); 
}

void heapify(int a[], int n, int i, unsigned long long& comp) {
    int largest = i;       
    int left = 2 * i + 1;  
    int right = 2 * i + 2; 
    if (++comp,left < n && (++comp, a[left] > a[largest])) {
        largest = left;
    }
    if (++comp,right < n && (++comp, a[right] > a[largest])) {
        largest = right;
    }
    if (++comp,largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest, comp);
    }
}

void heapSort(int a[], int n, unsigned long long& comp) {
    comp = 0; 
    for (int i = n / 2 - 1;++comp, i >= 0; --i) {
        heapify(a, n, i, comp);
    }
    for (int i = n - 1;++comp, i > 0; --i) {
        swap(a[0], a[i]);
        heapify(a, i, 0, comp);
    }
}

void merge(int a[], int left, int mid, int right, unsigned long long& comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0;++comp, i < n1; i++) L[i] = a[left + i];
    for (int j = 0;++comp, j < n2; j++) R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (++comp,++comp,i < n1 && j < n2) {
        if (++comp, L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }
    while (++comp,i < n1) a[k++] = L[i++];
    while (++comp,j < n2) a[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSortRec(int a[], int left, int right, unsigned long long& comp) {
    if (++comp,left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRec(a, left, mid, comp);
        mergeSortRec(a, mid + 1, right, comp);
        merge(a, left, mid, right, comp);
    }
}

void mergeSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    mergeSortRec(a, 0, n - 1, comp);
}

void quickSortRec(int a[], int left, int right, unsigned long long& comp) {
    int i = left,j = right;
    int pivot = a[left + (right - left) / 2];
    while (++comp,i <= j) {
        while (++comp, a[i] < pivot) {
            i++;
        }
        while (++comp, a[j] > pivot) {
            j--;
        }
        if (++comp, i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (++comp,left < j) {
        quickSortRec(a, left, j, comp);
    }
    if (++comp,i < right) {
        quickSortRec(a, i, right, comp);
    }
}

void quickSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    if (++comp,n > 1) {
        quickSortRec(a, 0, n - 1, comp);
    }
}

void countingSortForRadix(int a[], int n, int exp,unsigned long long& comp) {
    int* output = new int[n];
    int count[10] = {0};
    for (int i = 0;++comp, i < n; i++) {
        count[(a[i] / exp) % 10]++;
    }
    for (int i = 1;++comp,i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1;++comp, i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    for (int i = 0;++comp, i < n; i++) {
        a[i] = output[i];
    }
    delete[] output;
}

void radixSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    if (++comp,n <= 1) return;
    int max_val = a[0];
    for (int i = 1;++comp, i < n; i++) {
        if (++comp, a[i] > max_val) {
            max_val = a[i];
        }
    }
    for (int exp = 1;++comp, max_val / exp > 0; exp *= 10) {
        countingSortForRadix(a, n, exp,comp);
    }
}

void countingSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    if (++comp,n <= 1) return;
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (++comp, a[i] > max_val) {
            max_val = a[i];
        }
    }

    int* count = new int[max_val + 1]{0};
    int* output = new int[n];

    for (int i = 0;++comp, i < n; i++) {
        count[a[i]]++;
    }
    for (int i = 1;++comp, i <= max_val; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1;++comp, i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }
    for (int i = 0;++comp, i < n; i++) {
        a[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

void shellSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap;++comp, i < n; i += 1) {
            int temp = a[i];
            int j;
            for (j = i;++comp, j >= gap && (++comp, a[j - gap] > temp); j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

void flashSort(int a[], int n, unsigned long long& comp) {
    comp = 0;
    if (++comp,n <= 1) return;
    int minVal = a[0];
    int maxVal = a[0];
    int maxIdx = 0;

    for (int i = 1;++comp, i < n; ++i) {
        if (++comp,a[i] < minVal) {
            minVal = a[i];
        }
        if (++comp,a[i] > maxVal) {
            maxVal = a[i];
            maxIdx = i; 
        }
    }
    if (++comp,minVal == maxVal) return;
    int m = (int)(0.45 * n);
    if (++comp,m < 2) m = 2;
    int* L = new int[m]();
    double c = (double)(m - 1) / (maxVal - minVal);
    for (int i = 0;++comp, i < n; ++i) {
        int k = (int)(c * (a[i] - minVal));
        L[k]++;
    }
    for (int k = 1;++comp, k < m; ++k) {
        L[k] += L[k - 1];
    }
    swap(a[0], a[maxIdx]);

    int count = 1; 
    int i = 0;  
    int k = m - 1; 

    while (++comp,count < n) {
        while (++comp,i >= L[k]) {
            i++;
            k = (int)(c * (a[i] - minVal));
        }

        int flash = a[i];
        while (++comp,i < L[k]) {
            k = (int)(c * (flash - minVal));
            int targetIdx = --L[k];
    
            swap(flash, a[targetIdx]);
            count++;
        }
    }
    delete[] L;
    for (int idx = 1;++comp, idx < n; ++idx) {
        int key = a[idx];
        int j = idx - 1;
        while (++comp,j >= 0 && ++comp, a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}






// no comp from here

void no_comp_selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {

        int min_idx = i;
        for (int j = i + 1;j < n; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        swap(a[min_idx], a[i]);
    }
}

void no_comp_insertionSort(int a[], int n){
    for (int i = 1; i < n; i++){
        int num = a[i];
        int j = i-1;
        while (j >= 0 && a[j] > num){
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = num;
    }
}

void no_comp_binaryinsertionSort(int a[], int n){
    for (int i = 1;  i < n; ++i){
        int key = a[i];
        int first = 0, last = i - 1;
        while (first <= last) {
            int m = (first + last) / 2;
            if (key < a[m]) last = m - 1;
            else first = m + 1;
        }
        for (int j = i - 1; j >= first; --j)
            a[j + 1] = a[j];
        a[first] = key;
    }
}

void no_comp_bubbleSort(int a[], int n){
    for (int pass = 1; pass < n; ++pass){
        bool checked = true;
        for (int j = 0; j < n - pass; ++j){
            if (a[j] > a[j + 1]){
                swap(a[j], a[j + 1]);
                checked = false;
            }
        }
        if(checked){
            return;
        }
    }
}

void no_comp_shakerSort(int a[], int n) {
    int left = 1,right = n - 1,k = 0;
    do {
        k = 0;
        for (int j = left; j <= right; ++j) {
            if ( a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
                k = j;
            }
        }
        right = k - 1; 
        for (int j = right; j >= left; --j) {
            if ( a[j - 1] > a[j]) {
                swap(a[j - 1], a[j]);
                k = j;
            }
        }
        left = k + 1; 
    } while (left <= right && k > 0); 
}

void no_comp_heapify(int a[], int n, int i) {
    int largest = i;       
    int left = 2 * i + 1;  
    int right = 2 * i + 2; 
    if (left < n && ( a[left] > a[largest])) {
        largest = left;
    }
    if (right < n && ( a[right] > a[largest])) {
        largest = right;
    }
    if (largest != i) {
        swap(a[i], a[largest]);
        no_comp_heapify(a, n, largest);
    }
}

void no_comp_heapSort(int a[], int n) { 
    for (int i = n / 2 - 1; i >= 0; --i) {
        no_comp_heapify(a, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(a[0], a[i]);
        no_comp_heapify(a, i, 0);
    }
}

void no_comp_merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if ( L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void no_comp_mergeSortRec(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        no_comp_mergeSortRec(a, left, mid);
        no_comp_mergeSortRec(a, mid + 1, right);
        no_comp_merge(a, left, mid, right);
    }
}

void no_comp_mergeSort(int a[], int n) {
    no_comp_mergeSortRec(a, 0, n - 1);
}

void no_comp_quickSortRec(int a[], int left, int right) {
    int i = left,j = right;
    int pivot = a[left + (right - left) / 2];
    while (i <= j) {
        while ( a[i] < pivot) {
            i++;
        }
        while ( a[j] > pivot) {
            j--;
        }
        if ( i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        no_comp_quickSortRec(a, left, j);
    }
    if (i < right) {
        no_comp_quickSortRec(a, i, right);
    }
}

void no_comp_quickSort(int a[], int n) {
    if (n > 1) {
        no_comp_quickSortRec(a, 0, n - 1);
    }
}

void no_comp_countingSortForRadix(int a[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        count[(a[i] / exp) % 10]++;
    }
    for (int i = 1;i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }
    delete[] output;
}

void no_comp_radixSort(int a[], int n) {
    if (n <= 1) return;
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if ( a[i] > max_val) {
            max_val = a[i];
        }
    }
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        no_comp_countingSortForRadix(a, n, exp);
    }
}

void no_comp_countingSort(int a[], int n) {
    if (n <= 1) return;
    int max_val = a[0];
    for (int i = 1; i < n; i++) {
        if ( a[i] > max_val) {
            max_val = a[i];
        }
    }

    int* count = new int[max_val + 1]{0};
    int* output = new int[n];

    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }
    for (int i = 1; i <= max_val; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

void no_comp_shellSort(int a[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = a[i];
            int j;
            for (j = i; j >= gap && ( a[j - gap] > temp); j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}

void no_comp_flashSort(int a[], int n) {
    if (n <= 1) return;
    int minVal = a[0];
    int maxVal = a[0];
    int maxIdx = 0;

    for (int i = 1; i < n; ++i) {
        if (a[i] < minVal) {
            minVal = a[i];
        }
        if (a[i] > maxVal) {
            maxVal = a[i];
            maxIdx = i; 
        }
    }
    if (minVal == maxVal) return;
    int m = (int)(0.45 * n);
    if (m < 2) m = 2;
    int* L = new int[m]();
    double c = (double)(m - 1) / (maxVal - minVal);
    for (int i = 0; i < n; ++i) {
        int k = (int)(c * (a[i] - minVal));
        L[k]++;
    }
    for (int k = 1; k < m; ++k) {
        L[k] += L[k - 1];
    }
    swap(a[0], a[maxIdx]);

    int count = 1; 
    int i = 0;  
    int k = m - 1; 

    while (count < n) {
        while (i >= L[k]) {
            i++;
            k = (int)(c * (a[i] - minVal));
        }

        int flash = a[i];
        while (i < L[k]) {
            k = (int)(c * (flash - minVal));
            int targetIdx = --L[k];
            
            swap(flash, a[targetIdx]);
            count++;
        }
    }
    delete[] L;
    for (int idx = 1; idx < n; ++idx) {
        int key = a[idx];
        int j = idx - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}


SortFunction getSortFunction(string name) {
    if (name == "selection-sort") return selectionSort;
    if (name == "insertion-sort") return insertionSort;
    if (name == "binary-insertion-sort") return binaryinsertionSort;
    if (name == "bubble-sort") return bubbleSort;
    if (name == "shaker-sort") return shakerSort;
    if (name == "heap-sort") return heapSort;
    if (name == "merge-sort") return mergeSort;
    if (name == "quick-sort") return quickSort;
    if (name == "radix-sort") return radixSort;
    if (name == "counting-sort") return countingSort;
    if (name == "shell-sort") return shellSort;
    if (name == "flash-sort") return flashSort;
    return nullptr;
}

NoCompSortFunction getNoCompSortFunction(string name) {
    if (name == "selection-sort") return no_comp_selectionSort;
    if (name == "insertion-sort") return no_comp_insertionSort;
    if (name == "binary-insertion-sort") return no_comp_binaryinsertionSort;
    if (name == "bubble-sort") return no_comp_bubbleSort;
    if (name == "shaker-sort") return no_comp_shakerSort;
    if (name == "heap-sort") return no_comp_heapSort;
    if (name == "merge-sort") return no_comp_mergeSort;
    if (name == "quick-sort") return no_comp_quickSort;
    if (name == "radix-sort") return no_comp_radixSort;
    if (name == "counting-sort") return no_comp_countingSort;
    if (name == "shell-sort") return no_comp_shellSort;
    if (name == "flash-sort") return no_comp_flashSort;
    return nullptr;
}

double measureSortTime(NoCompSortFunction sortFunc, int a[], int n) {
    auto start = high_resolution_clock::now();
    sortFunc(a, n);
    auto end = high_resolution_clock::now();
    duration<double, milli> time = end - start;
    return time.count();
}
