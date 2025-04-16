#include <iostream>
using namespace std;

int factorial(int n) {
	if (n == 0 || n == 1) return 1;
	return n * factorial(n - 1);
}

int main() {
	int n;
	cout << "Nhap n: ";
	cin >> n;
	if (n < 0) {
		cout << "Loi n nho hon 0" << endl;
	}
	else {
		cout << n << "! = " << factorial(n) << endl;
	}
	system("pause");
	return 0;
}