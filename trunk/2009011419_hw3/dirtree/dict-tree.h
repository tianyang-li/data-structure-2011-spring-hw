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

#ifndef DICT_TREE_H
#define DICT_TREE_H

#include <iostream>
#include <new>
#include <cstddef>

#include "red-black-tree.h"

template <class T>
class DictTree {
public:
	class Node {
	public:
		inline Node() : par(NULL) {
		}
		inline Node(T const &new_data) : par(NULL), data(new_data) {
		}

		Node *par;  // parent
		RBTree<T> ch;  // children
		T data;
	private:
	};
	typedef Node *NodePtr;

	NodePtr root;

	inline DictTree() : root(NULL) {
	}

private:
};

#endif

