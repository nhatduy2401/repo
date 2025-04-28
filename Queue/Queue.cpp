#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Queue {
	NODE* head;
	NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue& q, int key);
int dequeue(Queue& q);
int size(Queue q);
bool isEmpty(Queue q);
void inFile(Queue*& q, ifstream& fin, ofstream& fout);
void outFile(Queue q, ofstream& fout);

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if (!fin.is_open() || !fout.is_open()) {
		cout << "Khong the mo file" << endl;
		return -1;
	}
	Queue* q = nullptr;
	inFile(q, fin, fout);
	fin.close();
	fout.close();
	return 0;
}

Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = q->tail = nullptr;
	return q;
}

void enqueue(Queue& q, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = nullptr;
	if (q.head == nullptr) {
		q.head = q.tail = newNode;
	}
	else {
		q.tail->p_next = newNode;
		q.tail = newNode;
	}
}

int dequeue(Queue& q) {
	if (q.head == nullptr) {
		return -1;
	}
	NODE* temp = q.head;
	int value = q.head->key;
	q.head = temp->p_next;
	if (q.head == nullptr) {
		q.tail = nullptr;
	}
	delete temp;
	return value;
}

int size(Queue q) {
	int count = 0;
	NODE* current = q.head;
	while (current != nullptr) {
		current = current->p_next;
		count++;
	}
	return count;
}

bool isEmpty(Queue q) {
	if (q.head == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void inFile(Queue*& q, ifstream& fin, ofstream& fout) {
	string command;
	while (fin >> command) {
		if (command == "init") {
			q = initializeQueue();
			outFile(*q, fout);
		}
		else if (command == "enqueue") {
			int value;
			fin >> value;
			enqueue(*q, value);
			outFile(*q, fout);
		}
		else if (command == "dequeue") {
			if (!isEmpty(*q)) {
				dequeue(*q);
			}
			outFile(*q, fout);
		}
	}
}

void outFile(Queue q, ofstream& fout) {
	if (isEmpty(q)) {
		fout << "EMPTY" << endl;
	}
	else {
		NODE* current = q.head;
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