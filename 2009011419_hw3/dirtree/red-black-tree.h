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
	enum Color {RED, BLACK};

public:
	class Node {
		friend class RBTree<T>;

	public:
		inline Node() : par(NULL), rc(NULL), lc(NULL), col(RED) {
		}
		inline Node(T const &new_data) : par(NULL), rc(NULL), lc(NULL), data(new_data), col(RED) {
		}
		inline ~Node() {
		}

		Node *par;  // parent
		Node *rc, *lc;  // right-child, left-child
		T data;

	private:
		Color col;
	};
	typedef Node *NodePtr;

	NodePtr root;

	inline RBTree() : root(NULL) {
	}

	inline NodePtr Insert(T const &new_key);
	inline NodePtr Search(T const &key);

	static inline NodePtr Min(NodePtr const cur);  // first element
	static inline NodePtr Max(NodePtr const cur);  // last element
	static inline NodePtr Next(NodePtr const cur);  // successor
	static inline NodePtr Prev(NodePtr const cur);  // predecessor

private:
	inline void LeftRot(NodePtr const x);
	inline void RightRot(NodePtr const y);
	inline void InsertFix(NodePtr const z);
};

template <class T>
inline typename RBTree<T>::NodePtr RBTree<T>::Min(NodePtr const cur) {
	NodePtr tmp1 = cur->lc, tmp2 = cur;
	while (NULL != tmp1) {
		tmp2 = tmp1;
		tmp1 = tmp1->lc;
	}
	return tmp2;
}

template <class T>
inline typename RBTree<T>::NodePtr RBTree<T>::Max(NodePtr const cur) {
	NodePtr tmp1 = cur->rc, tmp2 = cur;
	while (NULL != tmp1) {
		tmp2 = tmp1;
		tmp1 = tmp1->rc;
	}
	return tmp2;
}

template <class T>
inline typename RBTree<T>::NodePtr RBTree<T>::Next(NodePtr const cur) {
	if (NULL != cur->rc) {
		return Min(cur->rc);
	}
	NodePtr tmp1 = cur, tmp2 = cur->par;
	while ((NULL != tmp2) && (tmp1 == tmp2->rc)) {
		tmp1 = tmp2;
		tmp2 = tmp2->par;
	}
	return tmp2;
}

template <class T>
inline void RBTree<T>::InsertFix(NodePtr const cur) {
	NodePtr z = cur, y;
	while ((NULL != z->par) && (RED == z->par->col)) {
		if (z->par == z->par->par->lc) {
			y = z->par->par->rc;
			if (RED == y->col) {
				z->par->col = BLACK;
				y->col = BLACK;
				z->par->par->col = RED;
				z = z->par->par;
			}
			else {
				if (z == z->par->rc) {
					z = z->par;
					LeftRot(z);
				}
				z->par->col = BLACK;
				z->par->par->col = RED;
				RightRot(z->par->par);
			}
		}
		else {
			y = z->par->par->lc;
			if (RED == y->col) {
				z->par->col = BLACK;
				y->col = BLACK;
				z->par->par->col = RED;
				z = z->par->par;
			}
			else {
				if (z == z->par->lc) {
					z = z->par;
					RightRot(z);
				}
				z->par->col = BLACK;
				z->par->par->col = RED;
				LeftRot(z->par->par);
			}
		}
	}
	root->col = BLACK;
}

template <class T>
inline void RBTree<T>::LeftRot(NodePtr const x) {
	NodePtr y = x->rc;
	x->rc = y->lc;
	if (NULL != y->lc) {
		y->lc->par = x;
	}
	y->par = x->par;
	if (NULL == x->par) {
		root = y;
	}
	else {
		if (x == x->par->lc) {
			x->par->lc = y;
		}
		else {
			x->par->rc = y;
		}
	}
	y->lc = x;
	x->par = y;
}

template <class T>
inline void RBTree<T>::RightRot(NodePtr const y) {
	NodePtr x = y->lc;
	y->lc = x->rc;
	if (NULL != x->rc) {
		x->rc->par = y;
	}
	x->par = y->par;
	if (NULL == y->par) {
		root = x;
	}
	else {
		if (y == y->par->lc) {
			y->par->lc = x;
		}
		else {
			y->par->rc = x;
		}
	}
	x->rc = y;
	y->par = x;
}

template<class T>
inline typename RBTree<T>::NodePtr RBTree<T>::Insert(T const &new_key) {
	NodePtr y = NULL, x = root;
	while (NULL != x) {
		y = x;
		if (x->data > new_key) {
			x = x->lc;
		}
		else {
			if (x->data < new_key) {
				x = x->rc;
			}
			else {
				return x;
			}
		}
	}
	NodePtr z = new Node(new_key);
	z->par = y;
	if (NULL == y) {
		root = z;
	}
	else {
		if (new_key < y->data) {
			y->lc = z;
		}
		else {
			y->rc = z;
		}
	}
	// lc, rc, col in z are all initialized
	InsertFix(z);
	return z;
}

template <class T>
inline typename RBTree<T>::NodePtr RBTree<T>::Search(T const &key) {
	NodePtr tmp = root;
	while (NULL != tmp) {
		if (tmp->data == key) {
			return tmp;
		}
		if (tmp->data < key) {
			tmp = tmp->rc;
		}
		else {
			tmp = tmp->lc;
		}
	}
}

#endif

