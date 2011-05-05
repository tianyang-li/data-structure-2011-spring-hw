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

#ifndef DJSET_H
#define DJSET_H

#include <stdint.h>

template <class T>
class DJSet {
public:
	inline DJSet() : rank(0), par(this) {
	}
	inline DJSet(T const &new_data) : rank(0), par(this), data(new_data) {
	}
	inline ~DJSet() {
	}
	inline static void Union(DJSet<T> &x, DJSet<T> &y) {
		Link(*FindSet(x), *FindSet(y));
	}
	inline static void Link(DJSet<T> &x, DJSet<T> &y) {
		if (x.rank > y.rank) {
			y.par = &x;
			return;
		}
		x.par = &y;
		if (x.rank == y.rank) {
			++y.rank;
		}
	}
	inline static DJSet<T> *FindSet(DJSet<T> &x) {
		if (x.par != &x) {
			x.par = FindSet(*x.par);
		}
		return x.par;
	}

private:
	uint32_t rank;
	DJSet *par;  // parent
	T data;
};

#endif

