#ifndef __VECTOR
#include <vector>
#endif

inline int BinarySearch(std::vector<int>& v, int value, int low, int high) {
	if (v.empty())return -1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (v[mid] == value) {
			return mid;
		}
		else if (v[mid] > value) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return -1;
}