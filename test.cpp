#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <string>
#include <cstdlib>
#include "sorts.h"
using namespace std;

template <class T>
void Swap(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Function to generate an array with random data
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Function to generate an array with ascending order data
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Function to generate an array with descending order data
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Function to generate an array with nearly sorted data
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
	case 0:	// random
		GenerateRandomData(a, n);
		break;
	case 1:	// sorted
		GenerateSortedData(a, n);
		break;
	case 2:	// reverse sorted
		GenerateReverseData(a, n);
		break;
	case 3:	// nearly sorted
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

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "không hợp lệ";
        return 1;
    }
    string mode = argv[1];
    if (mode == "-a") {
		cout << "ALGORITHM MODE" <<'\n';
        string algorithm = argv[2];
        if (argc == 5) {
            string arg3 = argv[3]; 
            string output_param = argv[4];
            if (!isNumber(arg3)) {
                string input_file = arg3;
            } else {
                int input_size = stoi(arg3);
            }
        } 
        else if (argc == 6) {
            int input_size = stoi(argv[3]);
            string input_order = argv[4];
            string output_param = argv[5];
        }
    }
    else if (mode == "-c") {
		cout << "COMPARISON MODE" <<'\n';
        string algo1 = argv[2];
        string algo2 = argv[3];
        if (argc == 5) {
            string input_file = argv[4];
        } 
        else if (argc == 6) {
            int input_size = stoi(argv[4]);
            string input_order = argv[5];
        }
    } 
    else {
        cout << "không tìm thấy command line hợp lệ";
    }

    return 0;
}