#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>
#include <chrono>
#include <cstdlib>
#include "sorts.h"

using namespace std;
using namespace std::chrono;

typedef void (*SortFunction)(int[], int, unsigned long long&);

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
    return nullptr;
}

double measureSortTime(SortFunction sortFunc, int a[], int n, unsigned long long& comp) {
    auto start = high_resolution_clock::now();
    sortFunc(a, n, comp);
    auto end = high_resolution_clock::now();
    duration<double, milli> time = end - start;
    return time.count();
}

template <class T>
void Swap(T &a, T &b)
{
    T x = a;
    a = b;
    b = x;
}

void GenerateRandomData(int a[], int n)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        a[i] = rand()%n;
    }
}

void GenerateSortedData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
}

void GenerateReverseData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = n - 1 - i;
    }
}

void GenerateNearlySortedData(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }
    srand((unsigned int) time(NULL));
    for (int i = 0; i < 10; i ++)
    {
        int r1 = rand()%n;
        int r2 = rand()%n;
        Swap(a[r1], a[r2]);
    }
}

void GenerateData(int a[], int n, int dataType)
{
    switch (dataType)
    {
    case 0: 
        GenerateRandomData(a, n);
        break;
    case 1: 
        GenerateSortedData(a, n);
        break;
    case 2: 
        GenerateReverseData(a, n);
        break;
    case 3: 
        GenerateNearlySortedData(a, n);
        break;
    default:
        printf("Error: unknown data type!\n");
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

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "không hợp lệ\n";
        return 1;
    }

    string mode = argv[1];

    if (mode == "-a") {
        string algorithm = argv[2];
        SortFunction sortFunc = getSortFunction(algorithm);

        if (argc == 5) {
            string arg3 = argv[3]; 
            string output_param = argv[4];

            if (!isNumber(arg3)) {
                string input_file = arg3;
                int n = 0;
                int* a = nullptr;
                readFromFile(input_file, a, n);

                unsigned long long comp = 0;
                double time = measureSortTime(sortFunc, a, n, comp);

                cout << "ALGORITHM MODE\n";
                cout << "Algorithm: " << algorithm << "\n";
                cout << "Input file: " << input_file << "\n";
                cout << "Input size: " << n << "\n";
                cout << "-------------------------\n";
                if (output_param == "-time" || output_param == "-both") cout << "Running time: " << time << " ms\n";
                if (output_param == "-comp" || output_param == "-both") cout << "Comparisons: " << comp << "\n";

                writeToFile("output.txt", a, n);
                delete[] a;

            } else {
                int input_size = stoi(arg3);
                string orderNames[] = {"Randomize", "Sorted", "Reversed", "Nearly Sorted"};

                cout << "ALGORITHM MODE\n";
                cout << "Algorithm: " << algorithm << "\n";
                cout << "Input size: " << input_size << "\n\n";

                for (int i = 0; i < 4; ++i) {
                    int* a = new int[input_size];
                    GenerateData(a, input_size, i);
                    writeToFile("input_" + to_string(i + 1) + ".txt", a, input_size);

                    unsigned long long comp = 0;
                    double time = measureSortTime(sortFunc, a, input_size, comp);

                    cout << "Input order: " << orderNames[i] << "\n";
                    cout << "-------------------------\n";
                    if (output_param == "-time" || output_param == "-both") cout << "Running time: " << time << " ms\n";
                    if (output_param == "-comp" || output_param == "-both") cout << "Comparisons: " << comp << "\n\n";

                    delete[] a;
                }
            }
        } 
        else if (argc == 6) {
            int input_size = stoi(argv[3]);
            string input_order = argv[4];
            string output_param = argv[5];

            int* a = new int[input_size];
            GenerateData(a, input_size, getOrderType(input_order));
            writeToFile("input.txt", a, input_size);

            unsigned long long comp = 0;
            double time = measureSortTime(sortFunc, a, input_size, comp);

            cout << "ALGORITHM MODE\n";
            cout << "Algorithm: " << algorithm << "\n";
            cout << "Input size: " << input_size << "\n";
            cout << "Input order: " << input_order << "\n";
            cout << "-------------------------\n";
            if (output_param == "-time" || output_param == "-both") cout << "Running time: " << time << " ms\n";
            if (output_param == "-comp" || output_param == "-both") cout << "Comparisons: " << comp << "\n";

            writeToFile("output.txt", a, input_size);
            delete[] a;
        }
    }
    else if (mode == "-c") {
        string algo1 = argv[2];
        string algo2 = argv[3];
        SortFunction sortFunc1 = getSortFunction(algo1);
        SortFunction sortFunc2 = getSortFunction(algo2);

        if (argc == 5) {
            string input_file = argv[4];
            int n = 0;
            int* a1 = nullptr;
            readFromFile(input_file, a1, n);
            int* a2 = new int[n];
            for (int i = 0; i < n; ++i) a2[i] = a1[i];

            unsigned long long comp1 = 0, comp2 = 0;

            double time1 = measureSortTime(sortFunc1, a1, n, comp1);
            double time2 = measureSortTime(sortFunc2, a2, n, comp2);

            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algo1 << " | " << algo2 << "\n";
            cout << "Input file: " << input_file << "\n";
            cout << "Input size: " << n << "\n";
            cout << "-------------------------\n";
            cout << "Running time: " << time1 << " ms | " << time2 << " ms\n";
            cout << "Comparisons: " << comp1 << " | " << comp2 << "\n";

            delete[] a1;
            delete[] a2;
        } 
        else if (argc == 6) {
            int input_size = stoi(argv[4]);
            string input_order = argv[5];

            int* a1 = new int[input_size];
            GenerateData(a1, input_size, getOrderType(input_order));
            writeToFile("input.txt", a1, input_size);

            int* a2 = new int[input_size];
            for (int i = 0; i < input_size; ++i) a2[i] = a1[i];

            unsigned long long comp1 = 0, comp2 = 0;

            double time1 = measureSortTime(sortFunc1, a1, input_size, comp1);
            double time2 = measureSortTime(sortFunc2, a2, input_size, comp2);

            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algo1 << " | " << algo2 << "\n";
            cout << "Input size: " << input_size << "\n";
            cout << "Input order: " << input_order << "\n";
            cout << "-------------------------\n";
            cout << "Running time: " << time1 << " ms | " << time2 << " ms\n";
            cout << "Comparisons: " << comp1 << " | " << comp2 << "\n";

            delete[] a1;
            delete[] a2;
        }
    } 
    else {
        cout << "không tìm thấy command line hợp lệ\n";
    }
    return 0;
}