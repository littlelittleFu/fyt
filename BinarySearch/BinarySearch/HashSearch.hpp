#pragma once
#include <vector>
#include<iostream>
#define MAXNUM 9999
namespace hash {
	typedef int Status;
	typedef int KeyType;

	struct RcdType {
		KeyType key;
	};

	struct HashTable {
		RcdType* rcd;  // ���ֵ
		int size;
		int count;
		int* tag;
	};

	// ��ϣ���ؽ���С
	int hashSize[] = { 11,21,61,127,251,503 };
	int idx = 0;

	Status InitHashTable(HashTable& H, int size) {
		int i;
		H.rcd = new RcdType[size];
		H.tag = new int[size];
		if (nullptr == H.rcd || nullptr == H.tag)return -1;
		for (int i = 0; i < size; i++) {
			H.tag[i] = 0;
			H.rcd[i].key = MAXNUM;
		}
		H.size = size;
		H.count = 0;
		return 0;
	}

	// ����hash�ĺ��� ����������
	int Hash(KeyType key, int m) {
		return (3 * key) % m;
	}

	// ����hash��ͻ���߳�̽��   �����������ַ
	void collision(int& p, int m) {
		// �����һ��
		p = (p + 1) % m;
	}

	// hash���ѯ
	Status SearchHash(HashTable H, KeyType key, int& p, int& c) {
		p = Hash(key, H.size);

		int h = p;
		c = 0;
		while ((1 == H.tag[p] && H.rcd[p].key != key) || -1 == H.tag[p]) {
			collision(p, H.size); c++;
		}

		if (1 == H.tag[p] && key == H.rcd[p].key)return 0;
		else return -1;
	}

	void print(HashTable H) {
		for (int i = 0; i < H.size; i++) {
			std::cout << H.rcd[i].key << std::endl;
		}
	}

	void RecreateHash(HashTable& H) {
	
	}

	Status InsertHash(HashTable& H, KeyType key) {
		int p, c;
		if (-1 == SearchHash(H, key, p, c)) {
			//��ѯû����ͬkey
			if (c * 1.0 / H.size < 0.5) {
				// ��ͻû�ﵽ����
				// Search ����keyֵ��
				H.rcd[p].key = key;
				H.tag[p] = 1;// ��־λ
				H.count++;
				return 0;
			}
			else {
				//���������
				//RecreateHash(H);
			}
			return -1;
		}
	}
}

