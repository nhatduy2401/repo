#include <iostream>
using namespace std;

int linearSearchWithSentinel(int a[], int n, int k);

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
	int result = linearSearchWithSentinel(a, n, k);
	cout << result << endl;
	delete[] a;
	system("pause");
	return 0;
}

int linearSearchWithSentinel(int a[], int n, int k) {
	int last = a[n - 1];
	a[n - 1] = k;
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	a[n - 1] = last;
	if (i < n - 1 || a[n - 1] == k)
		return i;
	return -1;
}