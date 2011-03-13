/*
 * template for quick sort
 */

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <cstdlib>

template <class T>
void Swap(T &x, T &y) {
	T temp = x;
	x = y;
	y = temp;
}

template <class T>
int Partition(T *array, int low, int high) {
	// quicksort's partition
	// [low, high] in array[]
	// increasing order
	// 1st partition < pivot_val, 2nd partition >= pivot_val
	T pivot_val = array[low + int(float(high - low) * float(std::rand()) / float(RAND_MAX))];
	while (low < high) {
		while (array[low] < pivot_val) {
			++low;
		}
		while (array[high] >= pivot_val) {
			--high;
		}
		if (low < high) {
			Swap(array[low], array[high]);
			++low;
			--high;
		}
	}
	return low;
}

template <class T>
void QuickSort(T *array, int low, int high) {
	// sort array[] in range [low, high]
	// increasing order
	if (low < high) {
		int pivot = Partition(array, low, high);
		QuickSort(array, low, pivot - 1);
		QuickSort(array, pivot + 1, high);
	}
}

#endif  // QUICK_SORT_H

