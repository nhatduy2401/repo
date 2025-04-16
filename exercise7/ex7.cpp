#include <iostream>
using namespace std;

void swap(int a[], int i, int j);
void bubbleSort(int a[], int n);
void threeSum(int a[], int n);

int main() {
	int n;
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	threeSum(a, n);
	delete[] a;
	system("pause");
	return 0;
}

void swap(int a[], int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void bubbleSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				swap(a, j, j + 1);
			}
		}
	}
}

void threeSum(int a[], int n) {
	bubbleSort(a, n);
	for (int i = 0; i < n - 2; i++) {
		if (i > 0 && a[i] == a[i - 1]) {
			continue;
		}
		int left = i + 1, right = n - 1;
		while (left < right) {
			int sum = a[i] + a[left] + a[right];
			if (sum < 0) {
				left++;
			}
			else if (sum > 0) {
				right--;
			}
			else {
				cout << "[" << a[i] << "," << a[left] << "," << a[right] << "]\n";
				while (left < right && a[left] == a[left + 1]) {
					left++;
				}
				while (left < right && a[right] == a[right - 1]) {
					right--;
				}
				left++;
				right--;
			}
		}
	}
}