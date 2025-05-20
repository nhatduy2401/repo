#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

NODE* createNode(int data) {
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	newNode->height = 0;
	return newNode;
}

int height(NODE* n) {
	if (n == nullptr) {
		return -1;
	}
	return n->height;
}

int getBalance(NODE* n) {
	if (n == nullptr) {
		return 0;
	}
	return height(n->p_left) - height(n->p_right);
}

NODE* rightRotate(NODE* y) {
	NODE* x = y->p_left;
	NODE* T2 = x->p_right;
	x->p_right = y;
	y->p_left = T2;
	y->height = max(height(y->p_left), height(y->p_right)) + 1;
	x->height = max(height(x->p_left), height(x->p_right)) + 1;
	return x;
}

NODE* leftRotate(NODE* x) {
	NODE* y = x->p_right;
	NODE* T2 = y->p_left;
	y->p_left = x;
	x->p_right = T2;
	x->height = max(height(x->p_left), height(x->p_right)) + 1;
	y->height = max(height(y->p_left), height(y->p_right)) + 1;
	return y;
}

void Insert(NODE*& pRoot, int x) {
	if (pRoot == nullptr) {
		pRoot = createNode(x);
		return;
	}
	if (pRoot->key > x) {
		Insert(pRoot->p_left, x);
	}
	else if (pRoot->key < x) {
		Insert(pRoot->p_right, x);
	}
	else {
		return;
	}
	pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
	int balance = getBalance(pRoot);
	if (balance > 1 && x < pRoot->p_left->key) {
		pRoot = rightRotate(pRoot);
		return;
	}
	if (balance < -1 && x > pRoot->p_right->key) {
		pRoot = leftRotate(pRoot);
		return;
	}
	if (balance > 1 && x > pRoot->p_left->key) {
		pRoot->p_left = leftRotate(pRoot->p_left);
		pRoot = rightRotate(pRoot);
		return;
	}
	if (balance < -1 && x < pRoot->p_right->key) {
		pRoot->p_right = rightRotate(pRoot->p_right);
		pRoot = leftRotate(pRoot);
		return;
	}
}

NODE* minNode(NODE* n) {
	NODE* current = n;
	while (current->p_left != nullptr) {
		current = current->p_left;
	}
	return current;
}

void Remove(NODE*& pRoot, int x) {
	if (pRoot == nullptr) {
		return;
	}
	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
			NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
			if (temp == nullptr) {
				temp = pRoot;
				pRoot = nullptr;
			}
			else {
				*pRoot = *temp;
			}
			delete temp;
		}
		else {
			NODE* temp = minNode(pRoot->p_right);
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}
	}
	if (pRoot == nullptr) {
		return;
	}
	pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
	int balance = getBalance(pRoot);
	if (balance > 1 && getBalance(pRoot->p_left) >= 0) {
		pRoot = rightRotate(pRoot);
		return;
	}
	if (balance < -1 && getBalance(pRoot->p_right) <= 0) {
		pRoot = leftRotate(pRoot);
		return;
	}
	if (balance > 1 && getBalance(pRoot->p_left) < 0) {
		pRoot->p_left = leftRotate(pRoot->p_left);
		pRoot = rightRotate(pRoot);
		return;
	}
	if (balance < -1 && getBalance(pRoot->p_right) > 0) {
		pRoot->p_right = rightRotate(pRoot->p_right);
		pRoot = leftRotate(pRoot);
		return;
	}
}

bool isAVL(NODE* pRoot) {
	if (pRoot == nullptr) {
		return true;
	}
	int balance = getBalance(pRoot);
	if (balance > 1 || balance < -1) {
		return false;
	}
	return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}