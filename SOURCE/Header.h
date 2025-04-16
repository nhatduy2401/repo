#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;
using namespace std;

template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}

void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);
int findMin(int a[], int low, int n, long long& count);
void selectionSort(int a[], int n, long long& count);
void insertionSort(int a[], int n, long long& count);
void bubbleSort(int a[], int n, long long& count);
void heapify(int a[], int n, int i, long long& count);
void heapSort(int a[], int n, long long& count);
void merge(int a[], int left, int mid, int right, long long& count);
void mergeSort(int a[], int left, int right, long long& count);
int partition(int a[], int low, int high, long long& count);
void quickSort(int a[], int low, int high, long long& count);
int getMax(int a[], int n, long long& count);
void countSort(int a[], int n, int exp);
void radixSort(int a[], int n, long long& count);
bool readInputFile(string filename, int a[], int& n);
void writeOutputFile(string filename, int a[], int n);