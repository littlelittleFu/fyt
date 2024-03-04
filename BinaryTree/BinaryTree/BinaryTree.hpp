#pragma once
#include <iostream>
typedef int type;
struct node {
	int depth;
	node* parent;
	type value;
	node* l;
	node* r;
	node(type k) {
		value = k;
		l = nullptr;
		r = nullptr;
		parent = nullptr;
		depth = 0;
	}
};

class AVLTree {
public:
	node* LL(node* root) {
		node* tmp;
		tmp = root->l;
		root->l = tmp->r;
		tmp->r = root;
		return tmp;
	}

	node* RR(node* root) {
		node* tmp;
		tmp = root->r;
		root->r = tmp->l;
		tmp->l = root;
		return tmp;
	}

	node* LR(node*root){
		node* tmp;
		tmp = root->l;
		root->l = RR(tmp);
		return LL(root);
	}

	node* RL(node* root) {
		node* tmp;
		tmp = root->r;
		root->r = LL(tmp);
		return RR(root);
	}

	int H(const node* root) {
		if (root == nullptr)return 0;

		return std::max(H(root->l), H(root->r)) + 1;
	}
	
	int diff(const node* root) {
		return H(root->l) - H(root->r);
	}

	node* Balance(node* root) {
		int bal = diff(root);
		if (bal > 1) {
			if (diff(root->l) > 0)//LL
				root = LL(root);
			else //LR
				root = LR(root);
		}
		else if (bal < -1) {
			if (diff(root->r) > 0)//RL
				root = RL(root);
			else
				root = RR(root);
		}
		return root;
	}

	node* Insert(node* root, type value) {
		if (nullptr == root) {
			root = new node(value);
			return root;
		}
		else if (value < root->value) {
			root->l = Insert(root->l, value);
			root = Balance(root);
		}
		else if (value > root->value) {
			root->r = Insert(root->r, value);
			root = Balance(root);
		}
		return root;
	}

	void DisPlay(node* root) {
		if (root == nullptr)return;
		if (root->l != nullptr)
			DisPlay(root->l);
		std::cout << root->value << std::endl;
		if (root->r != nullptr)
			DisPlay(root->r);
	}


	node* root;
};



struct m_node {
	m_node* parent;
	type value;
	m_node* l;
	m_node* r;
	int bf;
	m_node(type k) {
		value = k;
		l = nullptr;
		r = nullptr;
		parent = nullptr;
		bf = 0;
	}
};

class mTree {
public:
	int H(const m_node* root) {
		if (root == nullptr)return 0;
		return std::max(H(root->l), H(root->r)) + 1;
	}

	int diff(const node* root) {
		return H(root->l) - H(root->r);
	}

	void Insert(type value) {
		if (root == nullptr) {
			root = new m_node(value);
			return;
		}

		m_node* tmp = root;
		m_node* pa = root;
		while (tmp != nullptr) {
			pa = tmp;
			tmp = tmp->value < val ? tmp->r : tmp->l;
		}
		
		if (value < pa.value) {
			pa->l = new m_node(value);
			pa->l->parent = pa;
			tmp = pa->l;
		}
		else {
			pa->r = new m_node(value);
			pa->r->parent = pa;
			tmp = pa->r;
		}

		while (pa != nullptr) {
			if (pa->l == tmp) {
				pa->bf--;
			}
			else if(pa->r == tmp){
				pa->bf++;
			}
			if (pa->bf >= 2 || pa->bf <= -2)break;
			tmp = pa;
			pa = pa->parent;
		}

		//balance
		if (pa->bf <= -2) {

			if (tmp == -1) {
				tmp->r = pa;
				pa->l = tmp->r;
				tmp->parent = pa->parent;
				if (pa == root) {
					root = tmp;
				}
				else {
					pa->parent->l = tmp;
				}
				pa->parent = tmp;

			}
			else {
			
			}
		
		}
		else if (pa->bf >= 2) {
			if (tmp == 1) {

			}
			else {
			
			}
		}

		

	}


private:
	m_node* root;
};
