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

#ifndef PRIOR_QUEUE_H
#define PRIOR_QUEUE_H

#include <new>
#include <cstddef>

// min heap
template <class T>
class PrQue {
public:
	std::size_t size;
	T *data;

	inline PrQue() : size(0) {
	}

	inline ~PrQue() {
		delete [] data;
	}

	inline void SetSize(std::size_t const new_size) {
		data = new (std::nothrow) T[new_size];  // XXX: error detection
	}

	inline void Insert(T const &new_data) {
		data[size] = new_data;
		std::size_t cur = size;
		while ((cur > 0) && (data[cur] < data[cur >> 1])) {
			PQSwap(data[cur], data[cur >> 1]);
			cur = cur >> 1;
		}
		++size;
	}

	inline void Pop() { // remove top
		--size;
		data[0] = data[size];
		std::size_t l, r, smallest = 0, cur = 0;
		if ((1 < size) && (data[1] < data[0])) {
			smallest = 1;
		}
		if ((2 < size) && (data[2] < data[smallest])) {
			smallest = 2;
		}
		while (smallest != cur) {
			PQSwap(data[cur], data[smallest]);
			cur = smallest;
			l = (cur << 1) + 1;
			r = (cur << 1) + 2;
			if ((l < size) && (data[l] < data[smallest])) {
				smallest = l;
			}
			if ((r < size) && (data[r] < data[smallest])) {
				smallest = r;
			}
		}
	}

private:
	inline void PQSwap(T &x, T &y) {
		T tmp = x;
		x = y;
		y = tmp;
	}
};

#endif
