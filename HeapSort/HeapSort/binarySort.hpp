// 相较于插入排序减少了 判断是否要进行交换的操作
namespace binaryInsert {
	void sort(int* arr, int size) {
		for (int i = 1; i < size; i++) {
			if (arr[i] >= arr[i - 1])continue;
			int key = arr[i];
			int l = 0, r = i - 1;
			while (l <= r) {
				int mid = l + (r - l) / 2;
				if (arr[mid] > key)
					r = mid - 1;
				else
					l = mid + 1;
			}
			for (int j = i - 1; j >= l; j--)
				arr[j + 1] = arr[j];

			arr[l] = key;
		}
	}
}