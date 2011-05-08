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

// T is coordiante type, U is type of data associated with each point
template <class T, class U>
class RangeTree {
public:
	struct Tuple {  // coordinates
		T x, y;
	};

	struct Point {
		Tuple coord;
		U data;
	};

	class YNode {
	public:
		YNode *lc, *rc, *par;
		Tuple coord;
		Point *point;

		inline YNode() : lc(NULL), rc(NULL), par(NULL), point(NULL) {
		}
		inline ~YNode() {
			if (lc) {
				delete lc;
			}
			if (rc) {
				delete rc;
			}
		}
	};
	typedef YNode *YNodePtr;

	class XNode {
	public:
		XNode *lc, *rc, *par;
		YNode *root;
		Tuple coord;

		inline XNode() : lc(NULL), rc(NULL), par(NULL), root(NULL) {
		}
		inline ~XNode() {
			if (lc) {
				delete lc;
			}
			if (rc) {
				delete rc;
			}
			delete root;
		}
	private:
	};
	typedef XNode *XNodePtr;

	Point *points;
	XNode *root;

	inline RangeTree();
	inline ~RangeTree();
	inline Point *SetSize(std::size_t tot) {
		size = tot;
		points = new (std::nothrow) Point[tot];
		return points;
	}
	inline void BuildTree();

private:
	size_t size;

	inline static bool XLess(Point const &a, Point const &b) {
		return ((a.coord.x < b.coord.x) || ((a.coord.x == b.coord.x) && (a.coord.y < b.coord.y)));
	}
	inline static bool XMore(Point const &a, Point const &b) {
		return ((a.coord.x > b.coord.x) || ((a.coord.x == b.coord.x) && (a.coord.y > b.coord.y)));
	}
	inline static bool YLess(Point const &a, Point const &b) {
		return ((a.coord.y < b.coord.y) || ((a.coord.y == b.coord.y) && (a.coord.x < b.coord.x)));
	}
	inline static bool YMore(Point const &a, Point const &b) {
		return ((a.coord.y > b.coord.y) || ((a.coord.y == b.coord.y) && (a.coord.x > b.coord.x)));
	}
};

template <class T, class U>
inline RangeTree<T, U>::RangeTree() : points(NULL) {
}

template <class T, class U>
inline RangeTree<T, U>::~RangeTree() {
	delete [] points;
	delete root;
}

template <class T, class U>
inline void RangeTree<T, U>::BuildTree() {
	QuickSort<Point>::Sort(points, 0, size - 1, &XLess, &XMore);
}

#endif
