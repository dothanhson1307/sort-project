#include <iostream>
#include <string>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include "sorts.h"


int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "không hợp lệ\n";
        return 1;
    }
    string mode = argv[1];
    if (mode == "-a") {
        string algorithm = argv[2];
        SortFunction sortFunc = getSortFunction(algorithm);
        NoCompSortFunction noCompSortFunc = getNoCompSortFunction(algorithm);

        if (argc == 5) {
            string arg3 = argv[3]; 
            string output_p = argv[4];

            if (!isNumber(arg3)) {
                string input_file = arg3;
                int n = 0;
                int* a = nullptr;
                readFromFile(input_file, a, n);
                int* a_time = new int[n];
                int* a_comp = new int[n];
                for(int i=0; i<n; ++i) { a_time[i] = a[i]; a_comp[i] = a[i]; }

                unsigned long long comp = 0;
                sortFunc(a_comp, n, comp);

                cout << "ALGORITHM MODE\n";
                cout << "Algorithm: " << algorithm << "\n";
                cout << "Input file: " << input_file << "\n";
                cout << "Input size: " << n << "\n";
                cout << "-------------------------\n";
                double time = measureSortTime(noCompSortFunc, a_time, n);
                if (output_p == "-time" || output_p == "-both") cout << "Running time: " << time << " ms\n";
                if (output_p == "-comp" || output_p == "-both") cout << "Comparisons: " << comp << "\n";

                writeToFile("output.txt", a_time, n);
                delete[] a; delete[] a_time; delete[] a_comp;

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

                    int* a_time = new int[input_size];
                    int* a_comp = new int[input_size];
                    for(int j=0; j<input_size; ++j) { a_time[j] = a[j]; a_comp[j] = a[j]; }

                    unsigned long long comp = 0;
                    sortFunc(a_comp, input_size, comp);
                    cout << "Input order: " << orderNames[i] << "\n";
                    cout << "-------------------------\n";
                    double time = measureSortTime(noCompSortFunc, a_time, input_size);
                    if (output_p == "-time" || output_p == "-both") cout << "Running time: " << time << " ms\n";
                    if (output_p == "-comp" || output_p == "-both") cout << "Comparisons: " << comp << "\n\n";

                    delete[] a; delete[] a_time; delete[] a_comp;
                }
            }
        } 
        else if (argc == 6) {
            int input_size = stoi(argv[3]);
            string input_order = argv[4];
            string output_p = argv[5];

            int* a = new int[input_size];
            GenerateData(a, input_size, getOrderType(input_order));
            writeToFile("input.txt", a, input_size);

            int* a_time = new int[input_size];
            int* a_comp = new int[input_size];
            for(int i=0; i<input_size; ++i) { a_time[i] = a[i]; a_comp[i] = a[i]; }

            unsigned long long comp = 0;
            sortFunc(a_comp, input_size, comp);

            cout << "ALGORITHM MODE\n";
            cout << "Algorithm: " << algorithm << "\n";
            cout << "Input size: " << input_size << "\n";
            cout << "Input order: " << input_order << "\n";
            cout << "-------------------------\n";
            double time = measureSortTime(noCompSortFunc, a_time, input_size);
            if (output_p == "-time" || output_p == "-both") cout << "Running time: " << time << " ms\n";
            if (output_p == "-comp" || output_p == "-both") cout << "Comparisons: " << comp << "\n";

            writeToFile("output.txt", a_time, input_size);
            delete[] a; delete[] a_time; delete[] a_comp;
        }
    }
    else if (mode == "-c") {
        string algo1 = argv[2];
        string algo2 = argv[3];
        SortFunction sortFunc1 = getSortFunction(algo1);
        SortFunction sortFunc2 = getSortFunction(algo2);
        NoCompSortFunction noCompSortFunc1 = getNoCompSortFunction(algo1);
        NoCompSortFunction noCompSortFunc2 = getNoCompSortFunction(algo2);

        if (argc == 5) {
            string input_file = argv[4];
            int n = 0;
            int* a = nullptr;
            readFromFile(input_file, a, n);
            
            int* a1_time = new int[n]; int* a1_comp = new int[n];
            int* a2_time = new int[n]; int* a2_comp = new int[n];
            for(int i=0; i<n; ++i) { 
                a1_time[i] = a[i]; a1_comp[i] = a[i];
                a2_time[i] = a[i]; a2_comp[i] = a[i];
            }

            unsigned long long comp1 = 0, comp2 = 0;
            sortFunc1(a1_comp, n, comp1);
            sortFunc2(a2_comp, n, comp2);

            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algo1 << " | " << algo2 << "\n";
            cout << "Input file: " << input_file << "\n";
            cout << "Input size: " << n << "\n";
            cout << "-------------------------\n";
            double time1 = measureSortTime(noCompSortFunc1, a1_time, n);
            double time2 = measureSortTime(noCompSortFunc2, a2_time, n);
            cout << "Running time: " << time1 << " ms | " << time2 << " ms\n";
            cout << "Comparisons: " << comp1 << " | " << comp2 << "\n";

            delete[] a; delete[] a1_time; delete[] a1_comp; delete[] a2_time; delete[] a2_comp;
        } 
        else if (argc == 6) {
            int input_size = stoi(argv[4]);
            string input_order = argv[5];

            int* a = new int[input_size];
            GenerateData(a, input_size, getOrderType(input_order));
            writeToFile("input.txt", a, input_size);

            int* a1_time = new int[input_size]; int* a1_comp = new int[input_size];
            int* a2_time = new int[input_size]; int* a2_comp = new int[input_size];
            for(int i=0; i<input_size; ++i) { 
                a1_time[i] = a[i]; a1_comp[i] = a[i];
                a2_time[i] = a[i]; a2_comp[i] = a[i];
            }

            unsigned long long comp1 = 0, comp2 = 0;

            sortFunc1(a1_comp, input_size, comp1);
            sortFunc2(a2_comp, input_size, comp2);

            cout << "COMPARE MODE\n";
            cout << "Algorithm: " << algo1 << " | " << algo2 << "\n";
            cout << "Input size: " << input_size << "\n";
            cout << "Input order: " << input_order << "\n";
            cout << "-------------------------\n";
            double time1 = measureSortTime(noCompSortFunc1, a1_time, input_size);
            double time2 = measureSortTime(noCompSortFunc2, a2_time, input_size);
            cout << "Running time: " << time1 << " ms | " << time2 << " ms\n";
            cout << "Comparisons: " << comp1 << " | " << comp2 << "\n";

            delete[] a; delete[] a1_time; delete[] a1_comp; delete[] a2_time; delete[] a2_comp;
        }
    } 
    else {
        cout << "không tìm thấy command line hợp lệ\n";
    }
    return 0;
}