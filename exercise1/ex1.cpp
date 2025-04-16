#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k);

int main() {
	int n, k;
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "Nhap so can tim: ";
	cin >> k;
	int result = linearSearch(a, n, k);
	cout << result << endl;
	delete[] a;
	system("pause");
	return 0;
}

int linearSearch(int a[], int n, int k) {
	for (int i = 0; i < n; i++) {
		if (a[i] == k) {
			return i;
		}
	}
	return -1;
}