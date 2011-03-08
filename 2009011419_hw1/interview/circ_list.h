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

	// insert new_T after position pos in the list
	// return a pointer to the new node
	// this->list_ptr_ NOT modified
	ListNode<T> *InsertAfter(T const &new_T, std::size_t pos);

	// insert new_T before position pos in the list
	// return a pointer to the new node
	// this->list_ptr_ MAY BE modified
	ListNode<T> *InsertBefore(T const &new_T, std::size_t pos);

	// delete data at position pos in the list
	// stpre value of data stored at (pos % this->len_) before deletion
	// return false when list is empty
	bool Delete(std::size_t pos, T &del_data);

	// remove to_rm from cur_list
	static void Remove(CircList<T> &cur_list, ListNode<T> *to_rm);

	// true if list is empty
	bool Empty() const {
		return (this->list_ptr_ == NULL);
	}

	// return a ptr to the new node
	// cur_list.list_ptr_ NOT modified
	static ListNode<T> *InsertAfter(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T);

	// return a ptr to the new node
	// cur_list.list_ptr_ MAY BE modified
	static ListNode<T> *InsertBefore(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T);

	// NULl returned on error
	ListNode<T> *GetNode(std::size_t pos);

	// get index of cur_node in this
	// false returned on error
	bool GetIndex(ListNode<T> *cur_node, std::size_t &index);

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

	if (cur_node == cur_list.list_ptr_) {
		cur_list.list_ptr_ = new_node;
	}

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

	return new_node;
}

template <class T>
T CircList<T>::Delete(std::size_t pos, T &del_data) {
	if (this->Empty()) {
		return false;
	}

	return true;
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

template <class T>
void CircList<T>::Remove(CircList<T> cur_list, ListNode<T> *to_rm) {
	--cur_list.len_;
}

template <class T>
ListNode<T> *CircList<T>::GetNode(std::size_t pos) {
	if (this->Empty()) {
		return NULL;
	}

	std::size_t cur_pos = pos % (this->len_);
}

template <class T>
bool CircList<T>::GetIndex(ListNode<T> *cur_node, std::size_t &index) {
	return true;
}

#endif  // CIRC_LIST_H


