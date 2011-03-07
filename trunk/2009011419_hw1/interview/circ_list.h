/*
 * circular list
 */

#ifndef CIRC_LIST_H
#define CIRC_LIST_H

#include <cstddef>

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
	bool Insert(T const &new_T, std::size_t pos = 0);

	// delete data at position pos in the list
	// return value of data stored at (pos % this->len_) before deletion
	// undefined when list is empty
	T Delete(std::size_t pos = 0);

	// true if list is empty
	bool Empty() const {
		return (this->list_ptr_ == NULL);
	}

protected:
	ListNode<T> *list_ptr_;  // point to the actual list storing data

	std::size_t len_;  // list length
};

template <class T>
bool CircList<T>::Insert(T const &new_T, std::size_t pos) {

}

template <class T>
T CircList<T>::Delete(std::size_t pos) {
	T del_data;

	if (!this->Empty()) {

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


