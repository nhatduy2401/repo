#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* Search(NODE* pRoot, int x) {
	while (pRoot != nullptr) {
		if (pRoot->key == x) {
			return pRoot;
		}
		else if (pRoot->key > x) {
			pRoot = pRoot->p_left;
		}
		else {
			pRoot = pRoot->p_right;
		}
	}
	return nullptr;
}

void Insert(NODE*& pRoot, int x) {
	if (pRoot == nullptr) {
		pRoot = new NODE{ x, nullptr, nullptr };
		return;
	}
	if (pRoot->key > x) {
		Insert(pRoot->p_left, x);
	}
	else if (pRoot->key < x) {
		Insert(pRoot->p_right, x);
	}
}

void Remove(NODE*& pRoot, int x) {
	if (pRoot == nullptr) {
		return;
	}
	if (pRoot->key > x) {
		Remove(pRoot->p_left, x);
	}
	else if (pRoot->key < x) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
			delete pRoot;
			pRoot = nullptr;
		}
		else if (pRoot->p_left == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_right;
			delete temp;
		}
		else if (pRoot->p_right == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_left;
			delete temp;
		}
		else {
			NODE* temp = pRoot->p_right;
			while (temp->p_left != nullptr) {
				temp = temp->p_left;
			}
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}
	}
}

NODE* createTree(int a[], int n) {
	NODE* pRoot = nullptr;
	for (int i = 0; i < n; i++) {
		Insert(pRoot, a[i]);
	}
	return pRoot;
}

void removeTree(NODE*& pRoot) {
	if (pRoot == nullptr) {
		return;
	}
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}

int Height(NODE* pRoot) {
	if (pRoot == nullptr) {
		return -1;
	}
	int left = Height(pRoot->p_left);
	int right = Height(pRoot->p_right);
	return 1 + max(left, right);
}

int countLess(NODE* pRoot, int x) {
	if (pRoot == nullptr) {
		return 0;
	}
	if (pRoot->key >= x) {
		return countLess(pRoot->p_left, x);
	}
	else {
		return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
	}
}

int countGreater(NODE* pRoot, int x) {
	if (pRoot == nullptr) {
		return 0;
	}
	if (pRoot->key <= x) {
		return countGreater(pRoot->p_right, x);
	}
	else {
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	}
}

bool isBSTUtil(NODE* pRoot, NODE* min, NODE* max) {
	if (pRoot == nullptr) {
		return true;
	}
	if (min != nullptr && pRoot->key <= min->key) {
		return false;
	}
	if (max != nullptr && pRoot->key >= max->key) {
		return false;
	}
	return isBSTUtil(pRoot->p_left, min, pRoot) && isBSTUtil(pRoot->p_right, pRoot, max);
}
bool isBST(NODE* pRoot) {
	return isBSTUtil(pRoot, nullptr, nullptr);
}

bool isFullBST(NODE* pRoot) {
	if (pRoot == nullptr) {
		return true;
	}
	if (!isBST(pRoot)) {
		return false;
	}
	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
		return true;
	}
	if (pRoot->p_left && pRoot->p_right) {
		return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
	}
	return false;
}