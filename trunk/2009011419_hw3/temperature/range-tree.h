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

// static range tree
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
	typedef Point *PointPtr;

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
		Point *p;

		inline XNode() : lc(NULL), rc(NULL), par(NULL), root(NULL), p(NULL) {
		}
		inline ~XNode() {
			if (lc) {
				delete lc;
			}
			if (rc) {
				delete rc;
			}
			delete root;
			delete [] p;
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

	inline XNode *BuildX(std::size_t const low, std::size_t const high, XNodePtr const from);
	inline YNode *BuildY(std::size_t const low, std::size_t const high, YNodePtr const from, PointPtr const p);
};

template <class T, class U>
inline typename RangeTree<T, U>::XNode *RangeTree<T, U>::BuildX(std::size_t const low, std::size_t const high, XNodePtr const from) {
	if (low > high) {
		return NULL;
	}
	XNode *node = new (std::nothrow) XNode;
	node->par = from;
	node->p = new (std::nothrow) Point[high - low + 1];
	for (std::size_t i = low; i <= high; ++i) {
		node->p[i - low] = points[i];
	}
	node->root = BuildY(low, high, NULL, node->p);
	if (low != high) {
		std::size_t mid = (low + high) >> 1;
		node->lc = BuildX(low, mid, node);
		node->rc = BuildX(mid + 1, high, node);
	}
	return node;
}

template <class T, class U>
inline typename RangeTree<T, U>::YNode *RangeTree<T, U>::BuildY(std::size_t const low, std::size_t const high, YNodePtr const from, PointPtr const p) {
	if (low > high) {
		return NULL;
	}
	YNode *node = new (std::nothrow) YNode;
	node->par = from;
	if (low == high) {
		node->point = &(p[low]);
	}
	else {
		std::size_t mid = (low + high) >> 1;
		node->lc = BuildY(low, mid, from, p);
		node->rc = BuildY(mid + 1, high, from, p);
	}
	return node;
}

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
	root = BuildX(0, size - 1, NULL);
}

#endif
