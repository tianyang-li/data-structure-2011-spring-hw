/*
 * linear list -- doubly linked
 */

#ifndef LINE_LIST_H
#define LINE_LIST_H

#include <iostream>

template <class T>
struct ListNode {
	ListNode();
	ListNode *next_, *prev_;
	T data_;
};

template <class T>
ListNode<T>::ListNode() : next_(NULL), prev_(NULL) {
}

template <class T>
class LineList {
public:
	LineList();
	~LineList();

	// insert after cur_node, return a pointer to the new node
	static ListNode<T> *InsertAfter(ListNode<T> *cur_node, T const &new_T);

	// insert before cur_node, return a pointer to the new node
	static ListNode<T> *InsertBefore(ListNode<T> *cur_node, T const &new_T);

	// delete a node from its list, return a pointer to the deleted node
	static ListNode<T> *Delete(ListNode<T> *to_del);

	std::size_t GetLen() const;

	bool Empty() const {
		// return true if empty
		return (head_ == tail_);
	}

protected:
	ListNode<T> *head_, *tail_;

	void Init();
};

template <class T>
std::size_t LineList<T>::GetLen() const {
	size_t count = 0;
	ListNode<T> *temp1 = head_->next_;

	while (temp1 != NULL) {
		++count;
		temp1 = temp1->next_;
	}

	return count;
}

template <class T>
LineList<T>::LineList() {
	Init();
}

template <class T>
void LineList<T>::Init() {
	head_ = new (std::nothrow) ListNode<T>;

	if (head_ == NULL) {
		std::cerr << "head_ = tail_ = new (std::nothrow) LineList<T>::LineListNode";
		std::cerr << std::endl << "memory allocation error" << std::endl;
	}

	tail_ = head_;
}

template <class T>
LineList<T>::~LineList() {
	ListNode<T> *temp1, *temp2;
	temp1 = head_;
	temp2 = head_->next_;

	while (temp1 != NULL) {
		delete temp1;
		temp1 = temp2;
		if (temp2 != NULL) {
			temp2 = temp2->next_;
		}
	}
}

template <class T>
static ListNode<T> *LineList<T>::InsertAfter(ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = new (std::nothrow) ListNode<T>;
	return new_node;
}

template <class T>
static ListNode<T> *LineList<T>::InsertBefore(ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = new (std::nothrow) ListNode<T>;
	return new_node;
}

template <class T>
static ListNode<T> *LineList<T>::Delete(ListNode<T> *to_del) {
	return to_del;
}

#endif  // LINE_LIST_H
