#pragma once
#include<iostream>
#include<string>

#define BLACK 1
#define RED 0

struct Node {
	int value;
	bool color;
	Node *l, *r, *parent;
	Node() :value(0), color(RED), l(nullptr), r(nullptr), parent(nullptr) {};
	
	Node* GrandParent() {
		if (parent == nullptr) {
			return nullptr;
		}
		return parent->parent;
	}

	Node* Uncle() {
		if (GrandParent() == nullptr)return nullptr;
		if (parent == GrandParent()->r)return GrandParent()->l;
		if (parent == GrandParent()->l)return GrandParent()->r;
	}

	Node* Bro() {
		if (parent == nullptr)return nullptr;
		if (parent->l == this)return parent->r;
		return parent->l;
	}

};

typedef Node* PNODE;

class RBT {
private:
	//右旋 参数node是旋转的轴
	//        0             1
	//      1    2   ->   3   0
	//    3                     2
	void Rotate_r(PNODE node) {
		if (nullptr == node->parent) {
			root = node;
			return;
		}
		PNODE gp = node->GrandParent();
		PNODE pp = node->parent;
		PNODE childrp = node->r;

		pp->l = childrp;

		if (nullptr != childrp)
			childrp->parent = pp;

		childrp->r = pp;
		pp->parent = node;

		if (root == pp)
			root = node;

		childrp->parent = gp;
		if (nullptr != gp) {
			if (gp->l == pp)
				gp->l = node;
			else
				gp->r = node;
		}
	};

	void Rotate_l(PNODE node) {

		if (nullptr == node->parent) {
			root = node;
			return;
		}
		PNODE gp = node->GrandParent();
		PNODE pp = node->parent;
		PNODE childlp = node->l;

		pp->r = childlp->GrandParent();
		if (nullptr != childlp)
			childlp->parent = pp;
		node->l = pp;
		pp->parent = node;

		if (root == pp)
			root = node;

		node->parent = gp;

		if (nullptr != gp) {
			if (gp->l == pp)
				gp->l = node;
			else
				gp->r = node;
		}
	}

	void Inorder(PNODE node) {
		if (nullptr == node)return;

		if (node->l)
			Inorder(node->l);
		std::cout << node->value;
		if (node->r)
			Inorder(node->r);
	}

	std::string PrintColor(bool color) {
		return color ? "black" : "red";
	}

	PNODE GetMinChild(PNODE node) {
		if (nullptr == node->l)return node;
		return GetMinChild(node->l);
	}

	void Insert(PNODE node, int data) {
		if (node->value >= data) {
			if (node->l != nullptr) {
				Insert(node->l, data);
			}
			else {
				PNODE tmp = new Node();
				tmp->value = data;
				tmp->parent = node;
				node->l = tmp;
				InsertCase(tmp);
			}
		}
		else {
			if (node->r != nullptr) {
				Insert(node->r, data);
			}
			else {
				PNODE tmp = new Node();
				tmp->value = data;
				tmp->parent = node;
				node->r = tmp;
				InsertCase(tmp);
			}
		}
	}

	void InsertCase(PNODE node)
	{
		if (node->parent == nullptr) {
			root = node;
			node->color = BLACK;
			return;
		}

		if (node->parent->color == RED) {
			if (node->Uncle()->color == RED) {
				node->parent->color = node->Uncle()->color = BLACK;
				node->GrandParent()->color = RED;
				InsertCase(node->GrandParent());
			}
			else {
				if (node->parent->r == node && node->GrandParent()->l == node->parent) {
					Rotate_l(node);
					Rotate_r(node);
					node->color = BLACK;
					node->l->color = node->r->color = RED;
				}
				else if (node->parent->l == node && node->GrandParent()->r == node->parent) {
					Rotate_r(node);
					Rotate_l(node);
					node->color = BLACK;
					node->l->color = node->r->color = RED;
				}
				else if (node->parent->l == node && node->GrandParent()->l == node->parent) {
					node->GrandParent()->color = BLACK;
					node->GrandParent()->color = RED;
					Rotate_r(node->parent);
				}
				else if (node->parent->r == node && node->GrandParent()->r == node->parent) {
					node->parent->color = BLACK;
					node->GrandParent()->color = RED;
					Rotate_l(node->parent);
				}
			}
		}
	}

private:
	PNODE root;


};