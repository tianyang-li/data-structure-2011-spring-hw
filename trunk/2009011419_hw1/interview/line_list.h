/*
 * linear list -- doubly linked
 */

#ifndef LINE_LIST_H
#define LINE_LIST_H

#include <iostream>

template <class T>
class LineList {
public:
	struct LineListNode {
		LineListNode();
		LineListNode *next_, *prev_;
		T data_;
	};

	LineList();
	~LineList();

	std::size_t GetLen() const {
		return len_;
	}
	bool Empty() const {
		// return true if empty
		return (head_ == tail_);
	}

protected:
	LineListNode *head_, *tail_;
	std::size_t len_;  // legnth of list

	void Init();
};

template <class T>
LineList<T>::LineListNode::LineListNode() : next_(NULL), prev_(NULL) {
}

template <class T>
LineList<T>::LineList() : len_(0) {
	Init();
}

template <class T>
void LineList<T>::Init() {
	head_ = tail_ = new (std::nothrow) LineList<T>::LineListNode;

	if (head_ == NULL) {
		std::cerr << "head_ = tail_ = new (std::nothrow) LineList<T>::LineListNode";
		std::cerr << std::endl << "memory allocation error" << std::endl;
	}
}

#endif  // LINE_LIST_H
