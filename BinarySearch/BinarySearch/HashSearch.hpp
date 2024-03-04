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
		RcdType* rcd;  // 存放值
		int size;
		int count;
		int* tag;
	};

	// 哈希表重建大小
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

	// 构建hash的函数 除留余数法
	int Hash(KeyType key, int m) {
		return (3 * key) % m;
	}

	// 处理hash冲突：线程探测   还可以链表地址
	void collision(int& p, int m) {
		// 往后加一个
		p = (p + 1) % m;
	}

	// hash表查询
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
			//查询没有相同key
			if (c * 1.0 / H.size < 0.5) {
				// 冲突没达到上限
				// Search 返回key值的
				H.rcd[p].key = key;
				H.tag[p] = 1;// 标志位
				H.count++;
				return 0;
			}
			else {
				//最大数量了
				//RecreateHash(H);
			}
			return -1;
		}
	}
}

