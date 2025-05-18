#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

struct HashTable {
	static const int size = 2000;
	Company table[size];
	bool occupied[size];
	HashTable() {
		for (int i = 0; i < size; i++) {
			occupied[i] = false;
		}
	}
};

vector<Company> readCompanyList(string file_name);
long long hashString(string company_name);
HashTable* createHashTable(vector<Company> list_company);
void insert(HashTable* hash_table, Company company);
Company* search(HashTable* hash_table, string company_name);

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Nhap tham so phu hop." << endl;
		system("pause");
		return 0;
	}

	string mstFile = argv[1];
	string inputFile = argv[2];
	string outputFile = argv[3];
	ifstream inFile(inputFile);
	ofstream outFile(outputFile);
	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << "Khong the mo file!" << endl;
		system("pause");
		return 0;
	}
	vector<Company> companyList = readCompanyList(mstFile);
	HashTable* hashTable = createHashTable(companyList);
	string companyName;
	while (getline(inFile, companyName)) {
		Company* company = search(hashTable, companyName);
		if (company != NULL) {
			outFile << company->name << "|" << company->profit_tax << "|" << company->address << endl;
		}
	}
	cout << "Da ghi thanh cong." << endl;
	inFile.close();
	outFile.close();
	delete hashTable;
	system("pause");
	return 0;
}

vector<Company> readCompanyList(string file_name) {
	vector<Company> company;
	ifstream file(file_name);
	if (!file.is_open()) {
		cerr << "Khong the mo file!" << endl;
		return company;
	}
	string line;
	getline(file, line);
	while (getline(file, line)) {
		stringstream dong(line);
		string name, tax, address;
		getline(dong, name, '|');
		getline(dong, tax, '|');
		getline(dong, address, '|');
		Company c;
		c.name = name;
		c.profit_tax = tax;
		c.address = address;
		company.push_back(c);
	}
	return company;
}

long long hashString(string company_name) {
	int p = 31;
	int m = 2000;
	string s;
	if (company_name.length() <= 20) {
		s = company_name;
	}
	else {
		s = company_name.substr(company_name.length() - 20);
	}
	long long hKey = 0;
	long long power = 1;
	for (int i = 0; i < s.length(); i++) {
		hKey = (hKey + s[i] * power % m) % m;
		power = power * p % m;
	}
	return hKey;
}

HashTable* createHashTable(vector<Company> list_company) {
	HashTable* table = new HashTable();
	for (int i = 0; i < list_company.size(); i++) {
		Company& c = list_company[i];
		long long index = hashString(c.name);
		while (table->occupied[index]) {
			index = (index + 1) % table->size;
		}
		table->table[index] = c;
		table->occupied[index] = true;
	}
	return table;
}

void insert(HashTable* hash_table, Company company) {
	long long index = hashString(company.name);
	int initial = index;
	while (hash_table->occupied[index]) {
		index = (index + 1) % hash_table->size;
		if (index == initial) {
			cerr << "Bang da day!" << endl;
			return;
		}
	}
	hash_table->table[index] = company;
	hash_table->occupied[index] = true;
	return;
}

Company* search(HashTable* hash_table, string company_name) {
	long long index = hashString(company_name);
	int initial = index;
	while (hash_table->occupied[index]) {
		if (hash_table->table[index].name == company_name) {
			return &(hash_table->table[index]);
		}
		index = (index + 1) % hash_table->size;
		if (index == initial) {
			break;
		}
	}
	return NULL;
}