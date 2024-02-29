#include<iostream>
#include<algorithm>
#include<chrono>

class timer {
public:
	timer() {
		start = std::chrono::system_clock::now();
	}
	~timer() {
		auto end = std::chrono::system_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
	}
private:
	std::chrono::system_clock::time_point start;
};

namespace HeapSort {
	void CreateMaxHeap(int arr[],int len ,int index) {
		int father = index;
		// 左孩子
		int son = father * 2 + 1;
		while (son <= len - 1) {
			if (son + 1 <= (len - 1) && arr[son] < arr[son + 1])
				// 有右孩子
				son++;

			if (arr[father] > arr[son])
				//符合大堆
				return;
			else {
				std::swap(arr[father], arr[son]);
				// 验证以原孩子节点构成的堆是否符合大堆
				father = son;
				son = father * 2 + 1;
			}
		}
	}

	void MaxHeapSort(int arr[], int size) {
		// 0下标 len/2-1 是最后一个非叶子结点  1下标 len/2是最后一个非叶子结点
		// 从最后一个父节点从后往前构建最大堆
		for (int i = size / 2 - 1; i >= 0; i--) {
			CreateMaxHeap(arr, size, i);
		}
		for (int i = size - 1; i >= 1; i--) {
			// 交换堆头与堆尾 重新构建0节点的最大堆
			std::swap(arr[0], arr[i]);
			CreateMaxHeap(arr, i, 0);
		}
	}

}