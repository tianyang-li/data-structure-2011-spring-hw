/*
 * template for
 * binary search
 */

#ifndef BIN_SEARCH_H
#define BIN_SEARCH_H

template <class T>
bool BinSearch(int low, int high, T *array, T const &query, int &index) {
	// search for query in [low, high] in array
	// true if found
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (array[mid] == query) {
			index = mid;
			return true;
		}
		else {
			if (array[mid] < query) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
	}
	return false;
}

#endif  // BIN_SEARCH_H
