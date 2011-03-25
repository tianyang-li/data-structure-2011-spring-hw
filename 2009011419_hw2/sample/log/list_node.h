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

/*
 * generic list node
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <iostream>
#include <new>

template <class T>
struct ListNode {
	ListNode();
	ListNode(T const &new_T);

	static ListNode<T> *CreateNewNode(T const &new_T);

	ListNode<T> *next_;
	ListNode<T> *prev_;

	T data_;
};

template <class T>
ListNode<T> *ListNode<T>::CreateNewNode(T const &new_T) {
	ListNode<T> *new_node;
	new_node = new (std::nothrow) ListNode<T>;

	if (new_node == NULL) {
		std::cerr << "new_node = new (std::nothrow) ListNode<T>";
		std::cerr << std::endl << "memory allocation error" << std::endl;
		return NULL;
	}

	new_node->data_ = new_T;

	return new_node;
}

template <class T>
ListNode<T>::ListNode(T const &new_T) : next_(NULL), prev_(NULL), data_(new_T) {
}

template <class T>
ListNode<T>::ListNode() : next_(NULL), prev_(NULL) {
}

#endif  // LIST_NODE_H
