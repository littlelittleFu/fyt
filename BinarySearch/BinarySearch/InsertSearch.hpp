#pragma once

#include<iostream>
#include <vector>
#include"test.hpp"


// �������
// ռ�� (high - low) * (value - v[low]) / (v[high] - v[low])
inline int InsertSearch(std::vector<int>& v, int value, int low, int high)
{
	int mid = 0;
	if (v.empty())return -1;
	if (low == high)return (value == v[low]) ? low : -1;
	if (value<v[low] || value>v[high])return -1;
	while (low <= high) {
		// mid��Ϊ ��ֵռ��Χ�ı���ȥ�趨�е�
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
