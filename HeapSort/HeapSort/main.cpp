#include<iostream>
#include"SortHeap.hpp"
int arr[100] = { 0,1,2,3,4,5,6,7,8,9 };

int arr1[100] = { 100,10,9,56,78,98,43,4,6,66 };

int main() {
	HeapSort::MaxHeapSort(arr, 10);
	{
		timer d;
		for (int i = 0; i < 10 - 1; i++) {
			for (int j = 0; j < 10 - 1 - i; j++) {
				if (arr1[j] > arr1[j + 1]) {
					std::swap(arr1[j], arr1[j + 1]);
				}
			}
		}
	}

	auto c = arr;
}