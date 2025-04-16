#include "Header.h"

int main(int argc, char* argv[]) {
	string algorithm, inputFile, outputFile;
	long long count = 0;
	int* a = nullptr;
	int n = 0;
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-a") {
			algorithm = argv[i + 1];
		}
		else if (string(argv[i]) == "-i") {
			inputFile = argv[i + 1];
		}
		else if (string(argv[i]) == "-o") {
			outputFile = argv[i + 1];
		}
	}
	if (algorithm.empty() || inputFile.empty() || outputFile.empty()) {
		cout << "Thieu du lieu" << endl;
		return -1;
	}
	int temp[10];
	if (!readInputFile(inputFile, temp, n)) {
		cout << "Khong doc duoc file input!" << endl;
		return -1;
	}
	else {
		a = new int[n];
		for (int i = 0; i < n; ++i) {
			a[i] = temp[i];
		}
	}
	if (algorithm == "selection-sort")
		selectionSort(a, n, count);
	else if (algorithm == "insertion-sort")
		insertionSort(a, n, count);
	else if (algorithm == "bubble-sort")
		bubbleSort(a, n, count);
	else if (algorithm == "heap-sort")
		heapSort(a, n, count);
	else if (algorithm == "merge-sort")
		mergeSort(a, 0, n - 1, count);
	else if (algorithm == "quick-sort")
		quickSort(a, 0, n - 1, count);
	else if (algorithm == "radix-sort")
		radixSort(a, n, count);
	else {
		cout << "Thuat toan khong hop le.\n";
		delete[] a;
		return 1;
	}
	writeOutputFile(outputFile, a, n);
	delete[] a;
	return 0;
}