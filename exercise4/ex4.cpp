#include <iostream>
using namespace std;

bool canShip(int a[], int n, int days, int capacity);
int shipWithinDays(int a[], int n, int days);

int main() {
	int n, day;
	cout << "Nhap so luong: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << "Nhap so ngay: ";
	cin >> day;
	cout << shipWithinDays(a, n, day) << endl;
	delete[] a;
	system("pause");
	return 0;
}

bool canShip(int a[], int n, int days, int capacity) {
	int sum = 0, dayCount = 1;
	for (int i = 0; i < n; i++) {
		if (sum + a[i] > capacity) {
			dayCount++;
			sum = 0;
		}
		sum += a[i];
	}
	if (dayCount > days) {
		return false;
	}
	return true;
}

int shipWithinDays(int a[], int n, int days) {
	int left = a[0], right = 0;
	for (int i = 0; i < n; i++) {
		if (left < a[i]) {
			left = a[i];
		}
		right += a[i];
	}
	while (left < right) {
		int mid = left + (right - left) / 2;
		if (canShip(a, n, days, mid)) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return left;
}