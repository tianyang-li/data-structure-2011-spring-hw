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
 * stack using linked list
 */

#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <cstddef>
#include <new>

#include "list_node.h"

template <class T>
class ListStack {  // similar to STL stack
public:
	ListStack();
	~ListStack();

	inline bool Empty() const;
	inline std::size_t Size() const;
	inline T Top() const;  // get top of stack, undefined when this->top_ == this->sentry_

	inline void Pop();
	inline void Push(T const &new_T);
protected:
	ListNode<T> *top_;  // top of stack
	ListNode<T> *sentry_;

	std::size_t size_;

	inline void Init();
};

template <class T>
void ListStack<T>::Init() {
	this->sentry_ = ListNode<T>::CreateNewNode();
	this->top_ = this->sentry_;
}

template <class T>
void ListStack<T>::Push(T const &new_T) {
	++this->size_;
	ListNode<T> *temp = ListNode<T>::CreateNewNode(new_T);
	temp->prev_ = this->top_;
	this->top_ = temp;
}

template <class T>
void ListStack<T>::Pop() {
	if (this->sentry_ == this->top_) {
		return;
	}

	--this->size_;
	ListNode<T> * temp = this->top_;
	this->top_ = temp->prev_;
	delete temp;
}

template <class T>
T ListStack<T>::Top() const {
	return this->top_->data_;
}

template <class T>
std::size_t ListStack<T>::Size() const {
	return this->size_;
}

template<class T>
bool ListStack<T>::Empty() const {
	return (this->sentry_ == this->top_);
}

template <class T>
ListStack<T>::ListStack() : top_(NULL), sentry_(NULL), size_(0) {
	this->Init();
}

template <class T>
ListStack<T>::~ListStack() {
	ListNode<T> *temp1 = this->top_, *temp2 = this->top_->prev_;
	while (temp1 != NULL) {
		delete temp1;
		temp1 = temp2;
		if (temp1 != NULL) {
			temp2 = temp1->prev_;
		}
	}
}

#endif  // LIST_STACK_H
