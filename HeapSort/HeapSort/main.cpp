#include<iostream>
#include<algorithm>
#include"SortHeap.hpp"
#include"insertSort.hpp"
#include"bubbleSort.hpp"
#include"binarySort.hpp"
#include"quickSort.hpp"

void print(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << std::endl;
	}
}

void mess(int* arr, int size) {

	for (int i = 0; i < 100000; i++) {
		arr[i] = rand() % 100001;
	}
}


int arr[100000];

int main() {
	mess(arr, 100000); 
	{
		timer t;
		//bubble::sort(arr, 100000);
	}
	std::cout << std::is_sorted(arr, arr + 100000)<<std::endl;

	mess(arr, 100000);
	{
		timer t;
		binaryInsert::sort(arr, 100000);

	}
	std::cout << std::is_sorted(arr, arr + 100000)<<std::endl;

	mess(arr, 100000);
	{
		timer t;
		insert::sort(arr, 100000);

	}
	std::cout << std::is_sorted(arr, arr + 100000)<<std::endl;

	mess(arr, 100000);
	{
		timer t;
		quick::sort(arr, 100000);
	}
	std::cout << std::is_sorted(arr, arr + 100000) << std::endl;

	mess(arr, 100000);
	{
		timer t;
		HeapSort::MaxHeapSort(arr, 100000);
	}
	std::cout << std::is_sorted(arr, arr + 100000)<<std::endl;


}