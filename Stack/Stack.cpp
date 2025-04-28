#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

Stack* initializeStack();
void push(Stack& s, int key);
int pop(Stack& s);
int size(Stack s);
bool isEmpty(Stack s);
void inFile(Stack*& s, ifstream& fin, ofstream& fout);
void outFile(Stack s, ofstream& fout);

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open() || !fout.is_open()) {
		cout << "Khong the mo file" << endl;
		return -1;
	}
	Stack* s = nullptr;
	inFile(s, fin, fout);
	fin.close();
	fout.close();
	return 0;
}

Stack* initializeStack() {
	Stack* s = new Stack;
	s->top = nullptr;
	return s;
}

void push(Stack& s, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = s.top;
	s.top = newNode;
}

int pop(Stack& s) {
	if (s.top == nullptr) {
		return -1;
	}
	NODE* temp = s.top;
	int value = temp->key;
	s.top = temp->p_next;
	delete temp;
	return value;
}

int size(Stack s) {
	int count = 0;
	NODE* current = s.top;
	while (current != nullptr) {
		current = current->p_next;
		count++;
	}
	return count;
}

bool isEmpty(Stack s) {
	if (s.top == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void inFile(Stack*& s, ifstream& fin, ofstream& fout) {
	string command;
	while (fin >> command) {
		if (command == "init") {
			s = initializeStack();
			outFile(*s, fout);
		}
		else if (command == "push") {
			int value;
			fin >> value;
			push(*s, value);
			outFile(*s, fout);
		}
		else if (command == "pop") {
			if (!isEmpty(*s)) {
				pop(*s);
			}
			outFile(*s, fout);
		}
	}
}

void outFile(Stack s, ofstream& fout) {
	if (isEmpty(s)) {
		fout << "EMPTY" << endl;
	}
	else {
		NODE* current = s.top;
		while (current != nullptr) {
			fout << current->key;
			if (current->p_next != nullptr) {
				fout << " ";
			}
			current = current->p_next;
		}
		fout << endl;
	}
}