#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data) {
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	return newNode;
}

vector<int> NLR(NODE* pRoot) {
	vector<int> res;
	if (pRoot == nullptr) {
		return res;
	}
	res.push_back(pRoot->key);
	vector<int> left = NLR(pRoot->p_left);
	vector<int> right = NLR(pRoot->p_right);
	res.insert(res.end(), left.begin(), left.end());
	res.insert(res.end(), right.begin(), right.end());
	return res;
}

vector<int> LNR(NODE* pRoot) {
	vector<int> res;
	if (pRoot == nullptr) {
		return res;
	}
	vector<int> left = LNR(pRoot->p_left);
	res.insert(res.end(), left.begin(), left.end());
	res.push_back(pRoot->key);
	vector<int> right = LNR(pRoot->p_right);
	res.insert(res.end(), right.begin(), right.end());
	return res;
}

vector<int> LRN(NODE* pRoot) {
	vector<int> res;
	if (pRoot == nullptr) {
		return res;
	}
	vector<int> left = LRN(pRoot->p_left);
	res.insert(res.end(), left.begin(), left.end());
	vector<int> right = LRN(pRoot->p_right);
	res.insert(res.end(), right.begin(), right.end());
	res.push_back(pRoot->key);
	return res;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> res;
	if (pRoot == nullptr) {
		return res;
	}
	queue<NODE*> q;
	q.push(pRoot);
	while (!q.empty()) {
		int size = q.size();
		vector<int> level;
		for (int i = 0; i < size; i++) {
			NODE* node = q.front();
			q.pop();
			level.push_back(node->key);
			if (node->p_left) {
				q.push(node->p_left);
			}
			if (node->p_right) {
				q.push(node->p_right);
			}
		}
		res.push_back(level);
	}
	return res;
}

int countNode(NODE* pRoot) {
	if (pRoot == nullptr) {
		return 0;
	}
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot) {
	if (pRoot == nullptr) {
		return 0;
	}
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

int height(NODE* node) {
	if (node == nullptr) {
		return -1;
	}
	int left = height(node->p_left);
	int right = height(node->p_right);
	return 1 + max(left, right);
}
int heightNode(NODE* pRoot, int value) {
	if (pRoot == nullptr) {
		return -1;
	}
	if (pRoot->key == value) {
		return height(pRoot);
	}
	int left = heightNode(pRoot->p_left, value);
	if (left != -1) {
		return left;
	}
	return heightNode(pRoot->p_right, value);
}

int Level(NODE* pRoot, NODE* p) {
	if (pRoot == nullptr) {
		return -1;
	}
	if (pRoot == p) {
		return 0;
	}
	queue<NODE*> q;
	int level = 0;
	q.push(pRoot);
	q.push(nullptr);
	while (!q.empty()) {
		NODE* temp = q.front();
		q.pop();
		if (temp == nullptr) {
			level++;
			if (!q.empty()) {
				q.push(nullptr);
			}
		}
		else {
			if (temp == p) {
				return level;
			}
			if (temp->p_left) {
				q.push(temp->p_left);
			}
			if (temp->p_right) {
				q.push(temp->p_right);
			}
		}
	}
	return -1;
}

int countLeaf(NODE* pRoot) {
	if (pRoot == nullptr) {
		return 0;
	}
	if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) {
		return 1;
	}
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}