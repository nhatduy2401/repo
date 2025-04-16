#include "Header.h"

// Hàm phát sinh m?ng d? li?u ng?u nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// Hàm phát sinh m?ng d? li?u có th? t? t?ng d?n
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh m?ng d? li?u có th? t? ng??c (gi?m d?n)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh m?ng d? li?u g?n nh? có th? t?
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ng?u nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có th? t?
		GenerateSortedData(a, n);
		break;
	case 2:	// có th? t? ng??c
		GenerateReverseData(a, n);
		break;
	case 3:	// g?n nh? có th? t?
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int findMin(int a[], int low, int n, long long& count) {
	int min = low;
	for (int i = low + 1; i < n; i++) {
		count++;
		if (a[i] < a[min]) {
			min = i;
		}
	}
	return min;
}

void selectionSort(int a[], int n, long long& count) {
	for (int i = 0; i < n; i++) {
		int min = findMin(a, i, n, count);
		HoanVi(a[i], a[min]);
	}
}

void insertionSort(int a[], int n, long long& count) {
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;
		while (j >= 0) {
			count++;
			if (a[j] > key) {
				a[j + 1] = a[j];
				j--;
			}
			else {
				break;
			}
		}
		a[j + 1] = key;
	}
}

void bubbleSort(int a[], int n, long long& count) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			count++;
			if (a[j] > a[j + 1]) {
				HoanVi(a[j], a[j + 1]);
			}
		}
	}
}

void heapify(int a[], int n, int i, long long& count) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n) {
		count++;
		if (a[left] > a[largest]) {
			largest = left;
		}
	}
	if (right < n) {
		count++;
		if (a[right] > a[largest]) {
			largest = right;
		}
	}
	if (largest != i) {
		HoanVi(a[i], a[largest]);
		heapify(a, n, largest, count);
	}
}

void heapSort(int a[], int n, long long& count) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i, count);
	}
	for (int i = n - 1; i > 0; i--) {
		HoanVi(a[0], a[i]);
		heapify(a, i, 0, count);
	}
}

void merge(int a[], int left, int mid, int right, long long& count) {
	int i = left, j = mid + 1, k = 0;
	int* temp = new int[right - left + 1];

	while (i <= mid && j <= right) {
		count++;
		if (a[i] <= a[j]) {
			temp[k++] = a[i++];
		}
		else {
			temp[k++] = a[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = a[i++];
	}
	while (j <= right) {
		temp[k++] = a[j++];
	}
	for (int x = 0; x < k; x++) {
		a[left + x] = temp[x]; 
	}
	delete[] temp;
}


void mergeSort(int a[], int left, int right, long long& count) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(a, left, mid, count);
		mergeSort(a, mid + 1, right, count);
		merge(a, left, mid, right, count);
	}
}

int partition(int a[], int low, int high, long long& count) {
	int pivot = a[low + (high - low) / 2];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		count++;
		if (a[j] < pivot) {
			i++;
			HoanVi(a[i], a[j]);
		}
	}
	HoanVi(a[i + 1], a[high]);
	return i + 1;
}

void quickSort(int a[], int low, int high, long long& count) {
	if (low < high) {
		int pi = partition(a, low, high, count);
		quickSort(a, low, pi - 1, count);
		quickSort(a, pi + 1, high, count);
	}
}

int getMax(int a[], int n, long long& count) {
	int max = a[0];
	for (int i = 1; i < n; i++) {
		count++;
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

void countSort(int a[], int n, int exp) {
	int* output = new int[n];
	int count[10] = { 0 };
	for (int i = 0; i < n; i++) {
		count[(a[i] / exp) % 10]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		int digit = (a[i] / exp) % 10;
		output[--count[digit]] = a[i];
	}
	for (int i = 0; i < n; i++) {
		a[i] = output[i];
	}
}

void radixSort(int a[], int n, long long& count) {
	int max = getMax(a, n, count);
	for (int exp = 1; max / exp > 0; exp *= 10) {
		countSort(a, n, exp);
	}
}

bool readInputFile(string filename, int a[], int& n) {
	ifstream in(filename);
	if (!in.is_open()) return false;

	in >> n;
	for (int i = 0; i < n; ++i)
		in >> a[i];

	in.close();
	return true;
}

void writeOutputFile(string filename, int a[], int n) {
	ofstream out(filename);
	out << n << endl;
	for (int i = 0; i < n; ++i)
		out << a[i] << " ";
	out << endl;
	out.close();
}