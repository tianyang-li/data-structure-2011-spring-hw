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

#ifndef RANGE_TREE_H
#define RANGE_TREE_H

#include <new>
#include <cstddef>

#include "quick-sort.h"

/*
 * Reference:
 *
 * Computational Geometry: Algorithms and Applications
 * Third Edition (March 2008)
 * Mark de Berg, TU Eindhoven (the Netherlands)
 * Otfried Cheong, KAIST (Korea)
 * Marc van Kreveld, Mark Overmars, Utrecht University (the Netherlands)
 */

template <class T, class U>
class RangeTree {
public:
	class Coord {
	public:
		struct Tuple {
			T x, y;

			inline bool operator<(Tuple const &cur) const {
				return ((x < cur.x) || ((x == cur.x) && (y < cur.y)));
			}
			inline bool operator>(Tuple const &cur) const {
				return ((x > cur.x) || ((x == cur.x) && (y > cur.y)));
			}
			inline static bool YLess(Tuple const &x, Tuple const &y) {
				return ((x.y < y.y) || ((x.y == y.y) && (x.x < y.x)));
			}
			inline static bool YMore(Tuple const &x, Tuple const &y) {
				return ((x.y > y.y) || ((x.y == y.y) && (x.x > y.x)));
			}
		} tuple;

		U data;

		// compares (px|py)
		inline bool operator<(Coord const &cur) const {
			return (tuple < cur.tuple);
		}
		inline bool operator>(Coord const &cur) const {
			return (tuple > cur.tuple);
		}
		inline static bool YLess(Coord const &x, Coord const &y) {
			return Tuple::YLess(x.tuple, y.tuple);
		}
		inline static bool YMore(Coord const &x, Coord const &y) {
			return Tuple::YMore(x.tuple, y.tuple);
		}

	private:
	};

	class Node {
	public:
		Node *lc, *rc, *par;
		Coord::Tuple tuple;

		inline Node() : lc(NULL), rc(NULL), par(NULL) {
		}
		inline ~Node() {
			if (NULL != lc) {
				delete lc;
			}
			if (NULL != rc) {
				delete rc;
			}
		}

	private:
	};

	Coord *points;
	std::size_t size;  // # of points in tree

	inline RangeTree();
	inline ~RangeTree();
	inline Coord *SetSize(std::size_t tot) {
		size = tot;
		points = new (std::nothrow) Coord[tot];
		return points;
	}
	inline void BuildTree();

private:
};

template <class T, class U>
inline void RangeTree<T, U>::BuildTree() {
	QuickSort(points, 0, size - 1);
}

template <class T, class U>
inline RangeTree<T, U>::RangeTree() : points(NULL) {
}

template <class T, class U>
inline RangeTree<T, U>::~RangeTree() {
	delete [] points;
}

#endif
