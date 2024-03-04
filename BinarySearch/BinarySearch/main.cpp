#include"InsertSearch.hpp"
#include"BinarySearch.hpp"
#include"test.hpp"
#include<iostream>
#include<algorithm>
#include<chrono>



int main() {

	std::vector<int>v;
	for (int i = 0; i < 100000; i++) {
		v.push_back(i);
	}
	//std::random_shuffle(v.begin(), v.end());
	{
		timer t;
		auto ret = BinarySearch(v, v[4000], 0, 99999);
		std::cout << ret << std::endl;
	}

	//std::random_shuffle(v.begin(), v.end());
	{
		timer t;
		auto ret = InsertSearch(v, v[4000], 0, 99999);
		std::cout << ret << std::endl;
	}



	return 0;
}