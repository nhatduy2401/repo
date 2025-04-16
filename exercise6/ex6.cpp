#include <iostream>
using namespace std;

bool twoNumsSum(int a[], int n, int target);

int main() {
	int n, target;
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "Nhap so: ";
	cin >> target;
	if (twoNumsSum(a, n, target)) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	delete[] a;
	system("pause");
	return 0;
}

bool twoNumsSum(int a[], int n, int target) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (a[i] + a[j] == target) {
				return true;
			}
		}
	}
	return false;
}