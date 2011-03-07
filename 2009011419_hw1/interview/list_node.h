/*
 * generic list node
 */

#ifndef LIST_NODE_H
#define LIST_NODE_H

template <class T>
struct ListNode {
	ListNode();

	ListNode<T> *next_;
	ListNode<T> *prev_;

	T data_;
};

template <class T>
ListNode<T>::ListNode() : next_(NULL), prev_(NULL) {
}

#endif  // LIST_NODE_H
