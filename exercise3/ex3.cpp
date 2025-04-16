#include <iostream>
using namespace std;

int minimum(int a[], int n);

int main() {
	int n;
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int min = minimum(a, n);
	cout << min << endl;
	delete[] a;
	system("pause");
	return 0;
}

int minimum(int a[], int n) {
	int low = 0, high = n - 1;
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (a[mid] > a[high]) {
			low = mid + 1;
		}
		else {
			high = mid;
		}
	}
	return a[low];
}