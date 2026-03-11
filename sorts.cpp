#include "sorts.h"
#include <iostream>

using namespace std;

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

