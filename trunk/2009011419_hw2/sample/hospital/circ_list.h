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

	ListNode<T> *Append(T const &new_T) {
		if (this->list_ptr_ == NULL) {
			return this->InitListNode(new_T);
		}
		return CircList<T>::InsertAfter(*this, this->list_ptr_->prev_, new_T);
	}

protected:
	ListNode<T> *list_ptr_;  // point to the actual list storing data

	std::size_t len_;  // list length

	// create a node when the list is empty
	ListNode<T> *InitListNode(T const &new_T);
};

template <class T>
ListNode<T> *CircList<T>::InitListNode(T const &new_T) {
	ListNode<T> *new_node = ListNode<T>::CreateNewNode(new_T);

	if (new_node == NULL) {
		return NULL;
	}

	new_node->next_ = new_node;
	new_node->prev_ = new_node;

	this->list_ptr_ = new_node;

	return new_node;
}

template <class T>
ListNode<T> *CircList<T>::InsertAfter(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = ListNode<T>::CreateNewNode(new_T);

	if (new_node == NULL) {
		return NULL;
	}

	++cur_list.len_;

	new_node->prev_ = cur_node;
	new_node->next_ = cur_node->next_;

	cur_node->next_->prev_ = new_node;
	cur_node->next_ = new_node;

	return new_node;
}  // TODO: testing needed for this function

template <class T>
ListNode<T> *CircList<T>::InsertBefore(CircList<T> &cur_list, ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = ListNode<T>::CreateNewNode(new_T);

	if (new_node == NULL) {
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
}  // TODO: testing needed for this function

template <class T>
ListNode<T> * CircList<T>::InsertAfter(T const &new_T, std::size_t pos) {
	ListNode<T> *cur_node = this->GetNode(pos);
	if (cur_node == NULL) {
		++this->len_;
		return this->InitListNode(new_T);
	}
	else {
		return CircList<T>::InsertAfter(*this, cur_node, new_T);
	}
}

template <class T>
ListNode<T> *CircList<T>::InsertBefore(T const &new_T, std::size_t pos) {
	ListNode<T> *cur_node = this->GetNode(pos);
	if (cur_node == NULL) {
		++this->len_;
		return this->InitListNode(new_T);
	}
	else {
		return CircList<T>::InsertBefore(*this, cur_node, new_T);
	}
}

template <class T>
bool CircList<T>::Delete(std::size_t pos, T &del_data) {
	if (this->Empty()) {
		return false;
	}

	ListNode<T> *to_del = this->GetNode(pos);

	CircList<T>::Remove(*this, to_del);

	del_data = to_del->data_;
	delete to_del;

	return true;
}  // TODO: testing needed for this function

template <class T>
CircList<T>::CircList() : list_ptr_(NULL), len_(0) {
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
}  // TODO: testing needed for this function

template <class T>
void CircList<T>::Remove(CircList<T> &cur_list, ListNode<T> *to_rm) {
	--cur_list.len_;
	to_rm->prev_->next_ = to_rm->next_;
	to_rm->next_->prev_ = to_rm->prev_;
	to_rm->next_ = NULL;
	to_rm->prev_ = NULL;

	if (cur_list.len_ == 0) {
		cur_list.list_ptr_ = NULL;
		return;
	}
}  // TODO: testing needed for this function

template <class T>
ListNode<T> *CircList<T>::GetNode(std::size_t pos) {
	if (this->Empty()) {
		return NULL;
	}

	std::size_t to_pos = pos % (this->len_);
	std::size_t cur_pos = 0;

	ListNode<T> *temp = this->list_ptr_;

	do {
		if (cur_pos == to_pos) {
			return temp;
		}

		++cur_pos;
	} while (cur_pos != this->len_);
}

template <class T>
bool CircList<T>::GetIndex(ListNode<T> *cur_node, std::size_t &index) {
	if (this->Empty()) {
		return false;
	}

	index = 0;
	ListNode<T> *temp = this->list_ptr_;

	do {
		if (temp == cur_node) {
			return true;
		}

		++index;
		temp = temp->next_;
	} while (temp != this->list_ptr_);

	return false;
}  // TODO: testing needed for this function

#endif  // CIRC_LIST_H


