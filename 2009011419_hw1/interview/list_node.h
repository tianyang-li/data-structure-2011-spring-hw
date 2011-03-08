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
