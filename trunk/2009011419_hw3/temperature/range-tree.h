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

/*
 * Reference:
 *
 * Computational Geometry: Algorithms and Applications
 * Third Edition (March 2008)
 * Mark de Berg, TU Eindhoven (the Netherlands)
 * Otfried Cheong, KAIST (Korea)
 * Marc van Kreveld, Mark Overmars, Utrecht University (the Netherlands)
 */

template <class T>
class RangeTree {
public:
	class Coord {
	public:
		T x, y;

		inline bool operator<(Coord const &cur) const {
			return ((x < cur.x) || ((x == cur.x) && (y < cur.y)));
		}
		inline bool operator>(Coord const &cur) const {
			return ((x > cur.x) || ((x == cur.x) && (y > cur.y)));
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

private:
};

template <class T>
inline RangeTree<T>::RangeTree() : points(NULL) {
}

#endif
