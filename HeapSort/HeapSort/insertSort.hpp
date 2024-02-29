// -+++----+-+--++
// -+++----+-+--++
// --+++---+-+--++
// ---+++--+-+--++
// ----+++-+-+--++
// ------++++-+--++
// -------+++++--++
// --------+++++-++
// ---------+++++++


namespace insert {
	void sort(int* arr, int size) {
		for (int i = 1; i < size; i++) {
			if (arr[i] >= arr[i - 1]) continue;
			int tmp = arr[i];
			int j;
			for (j = i - 1; j >= 0 && tmp < arr[j]; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = tmp;

		}
	}
}