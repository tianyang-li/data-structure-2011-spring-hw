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

	inline PrQue() {
	}

	inline ~PrQue() {
		delete [] data;
	}

	inline void SetSize(std::size_t const new_size) {
		size = new_size;
		data = new (std::nothrow) T[new_size];  // XXX: error detection
	}

	inline void Insert(T const &new_data) {
		++size;
	}

	inline std::size_t Pop() { // remove top
		--size;
		return (size + 1);
	}
};

#endif
