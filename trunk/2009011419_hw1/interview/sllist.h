/*
 * singly linked list
 */

#ifndef SLLIST_H
#define SLLIST_H

#include <iostream>
#include <cstddef>

template <class T>
class SLList {
public:
	class SLListNode {
	public:
		SLListNode();
	protected:
		SLListNode *next_;
		T data_;
	};
	SLList();
	~SLList();

	bool InsertAfter(SLListNode *cur_node);  // insert after cur_node

	std::size_t Legnth() const;
	bool Empty();  // true if empty

protected:
	SLListNode *head_;
	SLListNode *tail_;

	void Init();
};



template <class T>
bool SLList<T>::Empty() {
	if (head_->next_ == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template <class T>
SLList<T>::SLListNode::SLListNode() : next_(NULL) {
}

template <class T>
SLList<T>::SLList() : tail_(NULL) {
	Init();
}

template <class T>
void SLList<T>::Init() {
	head_ = new (std::nothrow) SLList<T>::SLListNode;
	if (head_ == NULL) {
		std::cerr << "head_ = new (nothrow) SLList<T>::SLListNode\nMemory allocation error\n";
	}
}

template <class T>
SLList<T>::~SLList() {
	SLList<T>::SLListNode *temp1, *temp2;
	temp1 = head_;
	temp2 = head_->next_;

	while (temp1 != NULL) {
		delete temp1;
		temp1 = temp2;
		temp2 = temp2->next_;
	}
}

template <class T>
std::size_t SLList<T>::Legnth() const {
	SLList<T>::SLListNode *temp1 = head_;
	std::size_t len = 0;

	while (temp1->next_ != NULL) {
		++len;
		temp1 = temp1->next_;
	}

	return len;
}

#endif  // SLLIST_H
