#include<iostream>
#ifndef __VECTOR
#include <vector>
#endif
#include "BinarySearch.h"
// Õ¼±È (high - low) * (value - v[low]) / (v[high] - v[low])
int InsertSearch(std::vector<int>& v, int value, int low, int high)
{
	int mid = 0;
	if (v.empty())return -1;
	if (v[high] == v[low])return (value == v[low]) ? low : -1;
	if (value<v[low] || value>v[high])return -1;

	while (low <= high) {
		mid = low + (high - low) * (value - v[low]) / (v[high] - v[low]);
		if (value == v[mid]) {
			return mid;
		}else if(value > v[mid]){
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}

int main() {

	std::vector<int>v{6, 9, 11, 12, 13, 14, 15, 16, 17, 18, 22};
	auto ret = InsertSearch(v, 22, 5, 9);
	auto ret1 = BinarySearch(v, 22, 5, 9);
	std::cout << ret << std::endl;

}