// e f j i a u d n g i o k
// a f j i = u d n g i o k
// a = j i f u d n g i o k
// a e j i f u d n g i o k
// 
// 
// e f j i a u d n g i o k
// e f j i a u d n g i o k
// e f j i a u d n g i o k
// e f j i a u d n g i o k
// e f j i a u d n g i o k
// e f j i a u d n g i o k

namespace quick
{
	int partition(int* arr, int l, int r) {
		int pivot = arr[l];
		int lidx = l;
		int ridx = r;
		//int idx = l;

		while (ridx > lidx) {
		    //ridx 从右向左比较
			while (ridx > lidx) {
				if (arr[ridx] < pivot) {
					arr[lidx] = arr[ridx];
					//idx = ridx;
					lidx++;
					break;
				}
				ridx--;
			}

			//lrdx 从左向右比较
			while (ridx > lidx) {
				if (arr[lidx] > pivot) {
					arr[ridx] = arr[lidx];
					//idx = lidx;
					ridx--;
					break;
				}
				lidx++;
			}
		}

		arr[lidx] = pivot;
		//return idx;
		return lidx;
	}

	int partition1(int* arr, int l, int r) {
		int key = arr[l];
		int pivot = l;
		int end = l;
		for (int i = l + 1; i <= r; i++) {
			if (arr[i] < key) {
				int tmp = arr[i];
				arr[i] = arr[pivot];
				arr[pivot] = tmp;
				// end存放空值地址
				if (end == pivot) {
					end = i;
				}
				pivot++;
			}
		}

		if (end > pivot) {
			arr[end] = arr[pivot];
			arr[pivot] = key;
		}

		return pivot;	
	}


	void quickProcess(int* arr, int l, int r) {
		//递归退出条件
		if (l >= r)return;
		// 获取基准元素位置
		int p = partition(arr, l, r);
		quickProcess(arr, l, p - 1);
		quickProcess(arr, p + 1, r);
	}

	void sort(int* arr, int size) {
		if (arr == nullptr || size <= 1)return;
		quickProcess(arr, 0, size - 1);
	}

}