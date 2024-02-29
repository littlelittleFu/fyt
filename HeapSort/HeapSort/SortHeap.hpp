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
		// ����
		int son = father * 2 + 1;
		while (son <= len - 1) {
			if (son + 1 <= (len - 1) && arr[son] < arr[son + 1])
				// ���Һ���
				son++;

			if (arr[father] > arr[son])
				//���ϴ��
				return;
			else {
				std::swap(arr[father], arr[son]);
				// ��֤��ԭ���ӽڵ㹹�ɵĶ��Ƿ���ϴ��
				father = son;
				son = father * 2 + 1;
			}
		}
	}

	void MaxHeapSort(int arr[], int size) {
		// 0�±� len/2-1 �����һ����Ҷ�ӽ��  1�±� len/2�����һ����Ҷ�ӽ��
		// �����һ�����ڵ�Ӻ���ǰ��������
		for (int i = size / 2 - 1; i >= 0; i--) {
			CreateMaxHeap(arr, size, i);
		}
		for (int i = size - 1; i >= 1; i--) {
			// ������ͷ���β ���¹���0�ڵ������
			std::swap(arr[0], arr[i]);
			CreateMaxHeap(arr, i, 0);
		}
	}

}