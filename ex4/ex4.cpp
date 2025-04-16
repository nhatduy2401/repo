#include <iostream>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
	if (n == 1) {
		cout << "Chuyen dia 1 tu cot " << from_rod << " qua cot " << to_rod << endl;
		return;
	}
	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	cout << "Chuyen dia " << n << " tu cot " << from_rod << " qua cot " << to_rod << endl;
	towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
	int n;
	cout << "Nhap so dia: ";
	cin >> n;
	towerOfHanoi(n, 'A', 'C', 'B');
	cout << endl;
	system("pause");
	return 0;
}