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
		Point *point;
		int p_ptr;  // index of point (if exists)

		inline YNode() : lc(NULL), rc(NULL), par(NULL), point(NULL), p_ptr(-1) {
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
		struct FC {  // used for fractional cascading
			int lc, rc;

			inline FC() : lc(-1), rc(-1) {
			}
		};

		XNode *lc, *rc, *par;
		YNode *root;
		Tuple coord;
		Point *p;  // points under this XNode
		std::size_t n;  // # of points under this node
		FC *fc;

		inline XNode() : lc(NULL), rc(NULL), par(NULL), root(NULL), p(NULL), n(1), fc(NULL) {
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
			delete [] fc;
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
	inline void FracCascadeLeft(XNodePtr const par);
	inline void FracCascadeRight(XNodePtr const par);
};

template <class T, class U>
inline void RangeTree<T, U>::FracCascadeLeft(XNodePtr const par) {
	std::size_t p = 0, c = 0;  // index for par and ch
	while ((p != par->n) && (c != par->lc->n)) {
		if (YMore(par->p[p], par->lc->p[c])) {
			++c;
		}
		else {
			par->fc[p].lc = int(c);
			++p;
		}
	}
}

template <class T, class U>
inline void RangeTree<T, U>::FracCascadeRight(XNodePtr const par) {
	std::size_t p = 0, c = 0;
	while ((p != par->n) && (c != par->rc->n)) {
		if (YMore(par->p[p], par->rc->p[c])) {
			++c;
		}
		else {
			par->fc[p].rc = int(c);
			++p;
		}
	}
}

template <class T, class U>
inline typename RangeTree<T, U>::XNode *RangeTree<T, U>::BuildX(std::size_t const low, std::size_t const high, XNodePtr const from) {
	if (low > high) {
		return NULL;
	}
	XNode *node = new (std::nothrow) XNode;
	node->par = from;
	std::size_t n = high -  low;  // tmp var
	node->n += n;
	node->p = new (std::nothrow) Point[n + 1];
	node->fc = new (std::nothrow) typename XNode::FC[n + 1];
	for (std::size_t i = low; i <= high; ++i) {
		node->p[i - low] = points[i];
	}
	QuickSort<Point>::Sort(node->p, 0, high - low, &YLess, &YMore);
	node->root = BuildY(low, high, NULL, node->p);
	if (low != high) {
		std::size_t mid = (low + high) >> 1;
		node->coord = points[mid].coord;
		node->lc = BuildX(low, mid, node);
		if (node->lc) {
			FracCascadeLeft(node);
		}
		node->rc = BuildX(mid + 1, high, node);
		if (node->rc) {
			FracCascadeRight(node);
		}
	}
	else {
		node->coord = points[low].coord;
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
		node->p_ptr = int(low);
	}
	else {
		std::size_t mid = (low + high) >> 1;
		node->point = new (std::nothrow) Point;
		node->point->coord = p[mid].coord;
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
