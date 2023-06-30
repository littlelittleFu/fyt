#pragma once
#include<iostream>

typedef struct AVLNode Tree;
typedef int Elemtype;

struct AVLNode {
	int height;
	Tree* parent;
	Elemtype value;
	Tree* l;
	Tree* r;
	AVLNode(int val = 0):height(0),parent(nullptr),value(val),l(nullptr),r(nullptr) {}
};

class AVLTree {
public:
	AVLTree() {
		root = nullptr;
	};
	~AVLTree() {};

	int CalcHeight(Tree* node) {
		if (nullptr == node->r && nullptr == node->l) {
			return 1;
		}
		else if (nullptr == node->r && nullptr != node->l) {
			return node->l->height + 1;
		}
		else if (nullptr != node->r && nullptr == node->l) {
			return node->r->height + 1;
		}
		else {
			return node->l->height > node->r->height ? node->l->height + 1 : node->r->height + 1;
		}
	}

	int CalcBF(Tree* node) {
		if (nullptr == node) {
			return 0;
		}
		else if (nullptr == node->l && nullptr == node->r) {
			return 0;
		}
		else if (nullptr == node->r) {
			return node->l->height;
		}
		else if (nullptr == node->l) {
			return - node->r->height;
		}
		else {
			return node->l->height - node->r->height;
		}
	}

	bool Insert(Elemtype value) {
		if (nullptr == root) {
			root = new Tree(value);
			return true;
		}
		return Insert(value, root);
	}

	// 整体运用递归思想插入
	bool Insert(Elemtype value, Tree* node) {
		if (value < node->value) {
			if (nullptr == node->l) {
				node->l = new Tree(value);
				node->l->parent = node;
			}
			else {
				Insert(value, node->l);
			};
		}
		else if (value > node->value) {
			if (nullptr == node->r) {
				node->r = new Tree(value);
				node->r->parent = node;
			}
			else {
				Insert(value, node->r);
			}
		}

		// 刷新高度
		node->height = CalcHeight(node);

		if (CalcBF(node) > 1) {
			if (CalcBF(node->l) == -1) {
				node->l = L_rotate(node->l);
			}
			node = R_rotate(node);
		}

		if (CalcBF(node) < -1) {
			if (CalcBF(node->r) == 1) {
				node->r = R_rotate(node);
			}
			node = L_rotate(node);
		}
		return node;
	}

	Tree* L_rotate(Tree* node) {
		Tree* oldRoot = node;
		Tree* newRoot = node->r;
		Tree* parent = node->parent;
		// new 替换 old
		if (nullptr != parent) {
			if (oldRoot->parent->value > oldRoot->value) {
				parent->l = newRoot;
			}
			else {
				parent->r = newRoot;
			}
		}
		newRoot->parent = parent;

		// 重组old
		oldRoot->r = newRoot->l;
		if (nullptr != newRoot->l) {
			newRoot->l->parent = oldRoot;
		}

		// old变为new的左子树
		newRoot->l = oldRoot;
		oldRoot->parent = newRoot;

		oldRoot->height = CalcHeight(oldRoot);
		newRoot->height = CalcHeight(newRoot);

		return newRoot;
	}

	Tree* R_rotate(Tree* node) {
	
	}

private:
	Tree* root;
};