#pragma once

void selectionSort(int a[], int n, unsigned long long& comp);
void insertionSort(int a[], int n, unsigned long long& comp);
void binaryinsertionSort(int a[], int n, unsigned long long& comp);
void bubbleSort(int a[], int n, unsigned long long& comp);
void shakerSort(int a[], int n, unsigned long long& comp);
void heapify(int a[], int n, int i, unsigned long long& comp);
void heapSort(int a[], int n, unsigned long long& comp);
void merge(int a[], int left, int mid, int right, unsigned long long& comp);
void mergeSortRec(int a[], int left, int right, unsigned long long& comp);
void mergeSort(int a[], int n, unsigned long long& comp);
void quickSortRec(int a[], int left, int right, unsigned long long& comp);
void quickSort(int a[], int n, unsigned long long& comp);
void countingSortForRadix(int a[], int n, int exp,unsigned long long& comp);
void radixSort(int a[], int n, unsigned long long& comp);
void countingSort(int a[], int n, unsigned long long& comp);
void shellSort(int a[], int n, unsigned long long& comp);
void flashSort(int a[], int n, unsigned long long& comp);

void no_comp_selectionSort(int a[], int n);
void no_comp_insertionSort(int a[], int n);
void no_comp_binaryinsertionSort(int a[], int n);
void no_comp_bubbleSort(int a[], int n);
void no_comp_shakerSort(int a[], int n);
void no_comp_heapify(int a[], int n, int i);
void no_comp_heapSort(int a[], int n);
void no_comp_merge(int a[], int left, int mid, int right);
void no_comp_mergeSortRec(int a[], int left, int right);
void no_comp_mergeSort(int a[], int n);
void no_comp_quickSortRec(int a[], int left, int right);
void no_comp_quickSort(int a[], int n);
void no_comp_countingSortForRadix(int a[], int n, int ex);
void no_comp_radixSort(int a[], int n);
void no_comp_countingSort(int a[], int n);
void no_comp_shellSort(int a[], int n);
void no_comp_flashSort(int a[], int n);
