#include <iostream>
using namespace std;

bool isSorted(int arr[], int n) {
	if (n == 0 || n == 1) 
		return true;
	if (arr[n - 1] < arr[n - 2])
		return false;
	return isSorted(arr, n - 1);
}

int main() {
	int arr[] = { 1,2,3,4,5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	isSorted(arr, n);
	if (isSorted(arr, n)) {
		cout << "Mang da duoc sap xep." << endl;
	}
	else {
		cout << "Mang chua duoc sap xep" << endl;
	}
	system("pause");
	return 0;
}