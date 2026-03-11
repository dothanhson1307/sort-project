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