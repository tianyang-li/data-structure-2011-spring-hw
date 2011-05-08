/*
 *  Copyright (C) 2011 Tianyang Li
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author Tianyang Li
 * E-Mail tmy1018 gmail com
 */

/*
 * template for quick sort, assumes all data are distinct
 */

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <cstdlib>

template <class T>
inline void Swap(T &x, T &y) {
	T temp = x;
	x = y;
	y = temp;
}

template <class T>
class QuickSort {
public:
	typedef bool (*Compare)(T const &x, T const &y);

	inline static void Sort(T *array, int low, int high, Compare less, Compare more);

private:
	inline static int Partition(T *array, int low, int high, Compare less, Compare more);
};


template <class T>
inline int QuickSort<T>::Partition(T *array, int low, int high, Compare less, Compare more) {
	// quicksort's partition
	// [low, high] in array[]
	// increasing order
	// 1st partition < pivot_val, 2nd partition >= pivot_val
	int pivot = low + int(float(high - low) * float(std::rand()) / float(RAND_MAX));
	T pivot_val = array[pivot];
	Swap<T>(array[pivot], array[high]);
	pivot = high;
	--high;
	while (low <= high) {
		while (less(array[low], pivot_val)) {
			++low;
			if (low > pivot) {
				break;
			}
		}
		while (more(array[high], pivot_val)) {
			--high;
			if (high < 0) {
				break;
			}
		}
		if (low < high) {
			Swap<T>(array[low], array[high]);
			++low;
			--high;
		}
	}
	Swap(array[pivot], array[low]);
	return low;
}

template <class T>
inline void QuickSort<T>::Sort(T *array, int low, int high, Compare less, Compare more) {
	// sort array[] in range [low, high]
	// increasing order
	if (low < high) {
		int pivot = Partition(array, low, high, less, more);
		Sort(array, low, pivot - 1, less, more);
		Sort(array, pivot + 1, high, less, more);
	}
}

#endif  // QUICK_SORT_H

