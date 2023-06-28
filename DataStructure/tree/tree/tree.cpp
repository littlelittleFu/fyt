#include<iostream>
#include<stack>
#include<queue>
#include<string>

#ifdef _TEST

////˫�ױ�ʾ��
#define MAX_TREE_SIZE 100
// ���ڵ����������
typedef int TElemType;

// ���ṹ
typedef struct PTNode {
	TElemType data;
	int parent;
}PTNode;

// ���ṹ
typedef struct {
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;
}PTree;

////���ӱ�ʾ��

////���Ӻ����ֵܱ�ʾ��

#endif 

typedef int valueType;

struct TreeNode {
	int key = 0;
	valueType value = 0;
	TreeNode* r = nullptr;
	TreeNode* l = nullptr;
	TreeNode(int key,int value) :key(key),value(value){};
};

class BinarySearchTree {
public:
	BinarySearchTree() {
		Init();
	}

	void Init() {
		root = nullptr;
	}

	void Insert(int key,int value) {
		TreeNode* node = new TreeNode(key, value);
		if (nullptr == root) {
			root = node;
		}
		InsertNode(node, root);
	}

	// �ж����� keyС ����������ֵ key�� ����������ֵ
	void InsertNode(TreeNode* newNode, TreeNode* oldNode) {
		do {
			if (newNode->key < oldNode->key) {
				if (nullptr == oldNode->l) {
					oldNode->l = newNode;
					return;
				}
				oldNode = oldNode->l;
			}
			else if(newNode->key>oldNode->key){
				if (nullptr == oldNode->r) {
					oldNode->r = newNode;
					return;
				}
				oldNode = oldNode->r;
			}
			else {
				return;
			}
		} while (1);
	}

	//������� stackѹ����ѹ������ѹ����
	void PreOrder(TreeNode* root) {
		if (nullptr == root)return;
		std::stack<TreeNode*>s;
		std::queue<TreeNode*>output;
		while (nullptr != root || !s.empty()) {
			if (nullptr != root) {
				s.push(root);
				output.push(root);// ����
				root = root->l;
			}
			else {
				root = s.top(); // ���ݸ��ڵ�
				s.pop();
				root = root->r;
			}
		}

		while (!output.empty()) {
			std::cout << output.front()->key << std::endl;
			output.pop();
		}
		
	};
	//�������
	void InOrder(TreeNode* root) {
		if (nullptr == root)return;
		std::stack<TreeNode*>s;
		std::queue<TreeNode*>output;
		while (nullptr != root || !s.empty()) {
			if (nullptr != root) {
				s.push(root);
				root = root->l;
			}
			else {
				root = s.top();
				output.push(root); //����
				s.pop();
				root = root->r;
			}
		}

		while (!output.empty()) {
			std::cout << output.front()->key << std::endl;
			output.pop();
		}
	};

	TreeNode* BinarySearch(int key) {
		if (nullptr == root)return nullptr;
		TreeNode* node = root;
		do {
			if (node->key == key) {
				return node;
			}
			else if (node->key > key) {
				node = node->l;
			}
			else {
				node = node->r;
			}
		} while (nullptr != node);
		return nullptr;
	}

	TreeNode* GetMax(int key) {
		auto node = BinarySearch(key);
		if (nullptr == node)return nullptr;
		while (nullptr != node->r) {
			node = node->r;
		}
		return node;
	}

	TreeNode* GetMin(int key) {
		auto node = BinarySearch(key);
		if (nullptr == node)return nullptr;
		while (nullptr != node->l) {
			node = node->l;
		}
		return node;
	}

	bool RemoveNode(int key) {
		enum {
			left = 1,
			right = 2,
		};
		TreeNode* node = root;
		TreeNode* parentNode = node;
		int dir = left;

		while (node->key != key) {
			parentNode = node;
			if (node->key > key) {
				node = node->l;
				dir = left;
			}
			else {
				node = node->r;
				dir = right;
			}
			if (nullptr == node)return false;
		}

		// Ҷ�ӽ��
		if (nullptr == node->l && nullptr == node->r) {
			if (node == root) {
				root = nullptr;
			}
			else {
				if (dir == left) {
					parentNode->l = nullptr;
				}
				else {
					parentNode->r = nullptr;
				}
			}
		}
		else if(nullptr != node->l && nullptr == node->r){
			//ֻ��������
			if (node == root) {
				root = root->l;
			}
			else {
				if (dir == left) {
					parentNode->l = node->l;
				}
				else {
					parentNode->r = node->l;
				}
			}
		}
		else if (nullptr == node->l && nullptr != node->r) {
			// ֻ��������
			if (node == root) {
				root = root->r;
			}
			if (dir == left) {
				parentNode->l = node->r;
			}
			else {
				parentNode->r = node->r;
			}
		}
		else
		{
			// ����������  ���������ҽ���滻 (�����������������滻)
			TreeNode* replaceNode = node->r;
			TreeNode* replaceParentNode = node;
			while (nullptr != replaceNode->l) {
				replaceParentNode = replaceNode;
				replaceNode = replaceNode->l;
			}

			// ɾ�����ĸ�ֵ
			if (node == root) {
				root = replaceNode;
			}
			else {
				if (dir == left) {
					parentNode->l = replaceNode;
				}
				else {
					parentNode->r = replaceNode;
				}
			}
			// �������ĸ�Ϊ��С���
			if(replaceParentNode != node){
				replaceParentNode->l = replaceNode->r;
				replaceNode->l = node->l;
				replaceNode->r = node->r;

			}
			// ���������������д�����С���
			else {
				replaceNode->l = node->l;
			}
		}

		delete node;
		node = nullptr;
		return true;
	}

public:
	TreeNode* root;

};




int main() {
	BinarySearchTree tree;
	tree.Insert(2, 20);
	tree.Insert(5, 50);
	tree.Insert(20, 200);
	tree.Insert(11, 110);
	tree.Insert(17, 170);
	tree.Insert(6, 60);
	tree.Insert(24, 240);
	tree.Insert(1, 10);
	tree.Insert(22, 220);
	tree.Insert(27, 270);

	tree.InOrder(tree.root);
	std::cout << std::endl;

	auto ret = tree.BinarySearch(6);
	auto ret1 = tree.BinarySearch(9);
	std::cout << std::endl;
	tree.RemoveNode(11);

	tree.RemoveNode(20);
	tree.InOrder(tree.root);
	std::cout << std::endl;

	tree.RemoveNode(27);
	tree.InOrder(tree.root);
	std::cout << std::endl;

	tree.RemoveNode(2);
	tree.InOrder(tree.root);
	std::cout << std::endl;

	tree.RemoveNode(1);
	tree.RemoveNode(5);
	tree.RemoveNode(6);
	tree.RemoveNode(11);
	tree.RemoveNode(17);
	tree.RemoveNode(22);
	tree.InOrder(tree.root);
	tree.RemoveNode(24);
	tree.InOrder(tree.root);
	std::cout << std::endl;

	tree.Insert(2, 20);
	tree.Insert(5, 50);
	tree.Insert(11, 110);
	tree.Insert(20, 200);
	tree.InOrder(tree.root);
	std::cout << std::endl;
	tree.Insert(4, 10);

	tree.RemoveNode(5);
	tree.InOrder(tree.root);
	std::cout << std::endl;

	return 0;
}
