#include <iostream>
using namespace std;

void generateBinaryStrings(int n, string str) {
	if (str.length() == n) {
		cout << str << endl;
		return;
	}
	generateBinaryStrings(n, str + "0");
	generateBinaryStrings(n, str + "1");
}

int main() {
	int n;
	string str;
	cout << "Nhap do dai: ";
	cin >> n;
	generateBinaryStrings(n, str);
	system("pause");
	return 0;
}