#include"BinaryTree.hpp"
#include<iostream>
#include<algorithm>
#include<vector>

#include<chrono>
class STimer
{
public:
	STimer() {
		auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		m_StartTime = tmp.count();
	};
	~STimer() {
		auto tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		std::cout << "cur life cycle cast:" << tmp.count() - m_StartTime << " ms!" << std::endl;
	};


private:
	int64_t m_StartTime = 0;
};

int main(){

	std::vector<int> arr;
	for (int i = 0; i < 10000; i++) {
		arr.push_back(i);
	}
	std::random_shuffle(arr.begin(),arr.end());
	

	auto tree = new AVLTree();


	{
		STimer t;
		for (int i = 0; i < 10000; i++) {
			tree->root = tree->Insert(tree->root, arr[i]);
		}
	}
	tree->DisPlay(tree->root);



	return 0;
}