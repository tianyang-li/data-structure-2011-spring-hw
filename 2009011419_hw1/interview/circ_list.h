/*
 * circular list
 */

#ifndef CIRC_LIST_H
#define CIRC_LIST_H

#include <cstddef>
#include <new>
#include <iostream>

#include "list_node.h"

template <class T>
class CircList {
public:
	CircList();
	~CircList();

	std::size_t GetLen() const {
		return this->len_;
	}

	// insert new_T at position pos in the list
	// return a pointer to the new node
	ListNode<T> *Insert(T const &new_T, std::size_t pos = 0);

	// delete data at position pos in the list
	// return value of data stored at (pos % this->len_) before deletion
	// undefined when list is empty
	T Delete(std::size_t pos = 0);

	// true if list is empty
	bool Empty() const {
		return (this->list_ptr_ == NULL);
	}

	// return a ptr to the new node
	// cur_list.list_ptr_ NOT modified
	static ListNode<T> *InsertAfter(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T);

	// return a ptr to the new node
	// cur_list.list_ptr_ NOT modified
	static ListNode<T> *InsertBefore(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T);

protected:
	ListNode<T> *list_ptr_;  // point to the actual list storing data

	std::size_t len_;  // list length
};

template <class T>
ListNode<T> *CircList<T>::InsertAfter(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = new (std::nothrow) ListNode<T>(new_T);

	if (new_node == NULL) {
		std::cerr << "ListNode<T> *new_node = new (std::nothrow) ListNode<T>(new_T)";
		std::cerr << std::endl << "memory allocation failed" << std::endl;
		return NULL;
	}

	++cur_list.len_;

	new_node->prev_ = cur_node;
	new_node->next_ = cur_node->next_;

	cur_node->next_->prev_ = new_node;
	cur_node->next_ = new_node;

	return new_node;
}

template <class T>
ListNode<T> *CircList<T>::InsertBefore(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = new (std::nothrow) ListNode<T>(new_T);

	if (new_node == NULL) {
		std::cerr << "ListNode<T> *new_node = new (std::nothrow) ListNode<T>(new_T)";
		std::cerr << std::endl << "memory allocation failed" << std::endl;
		return NULL;
	}

	++cur_list.len_;

	new_node->next_ = cur_node;
	new_node->prev_ = cur_node->prev_;

	cur_node->prev_->next_ = new_node;
	cur_node->prev_ = new_node;

	return new_node;
}

template <class T>
ListNode<T> * CircList<T>::Insert(T const &new_T, std::size_t pos) {
	ListNode<T> *new_node = new (std::nothrow) ListNode<T>(new_T);

	if (new_node == NULL) {
		std::cerr << "ListNode<T> *new_node = new (std::nothrow) ListNode<T>(new_T)";
		std::cerr << std::endl << "memory allocation failed" << std::endl;
		return NULL;
	}

	++this->len_;

	return new_node;
}

template <class T>
T CircList<T>::Delete(std::size_t pos) {
	T del_data;
	std::size_t cur_pos = pos % (this->len_);

	if (!this->Empty()) {
		--this->len_;
	}

	return del_data;
}

template <class T>
CircList<T>::CircList() : list_ptr_(NULL) {
}

template <class T>
CircList<T>::~CircList() {
	if (this->list_ptr_ == NULL) {
		return;
	}

	ListNode<T> *temp1 = this->list_ptr_;
	ListNode<T> *temp2 = temp1->next_;

	do {
		delete temp1;
		temp1 = temp2;
		if (temp2 != this->list_ptr_) {
			temp2 = temp2->next_;
		}
	} while (temp1 != this->list_ptr_);
}

#endif  // CIRC_LIST_H


