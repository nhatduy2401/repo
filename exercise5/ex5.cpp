#include <iostream>
using namespace std;

int minLengthSum(int target, int a[], int n);

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
	cout << minLengthSum(target, a, n) << endl;
	delete[] a;
	system("pause");
	return 0;
}

int minLengthSum(int target, int a[], int n) {
	int left = 0, sum = 0;
	int minLength = n + 1;
	for (int right = 0; right < n; right++) {
		sum += a[right];
		while (sum >= target) {
			int length = right - left + 1;
			if (length < minLength) {
				minLength = length;
			}
			sum -= a[left];
			left++;
		}
	}
	if (minLength == n + 1) {
		return 0;
	}
	else {
		return minLength;
	}
}