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

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <new>
#include <iostream>
#include <cstddef>

template <class T>
class RBTree {
public:
	class Node {
	public:
		inline Node() : par(NULL), rc(NULL), lc(NULL) {
		}

		inline Node(T const &new_data) : par(NULL), rc(NULL), lc(NULL), data(new_data) {
		}

		Node *par;  // parent
		Node *rc, *lc;  // right-child, left-child
		T data;
	private:
	};
	typedef Node *NodePtr;

	NodePtr root;

	inline RBTree() : root(NULL) {
	}

private:
	inline static bool Compare(T const &t1, T const &t2);
};

#endif

