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
	typedef int Index;  // < 0 on error, >= 0 otherwise

	LineList();
	~LineList();

	// insert after cur_node, return a pointer to the new node
	static ListNode<T> *InsertAfter(ListNode<T> *cur_node, T const &new_T);

	// insert before cur_node, return a pointer to the new node
	static ListNode<T> *InsertBefore(ListNode<T> *cur_node, T const &new_T);

	// add data to tail, return a pointer to the new node
	ListNode<T> *Append(T const &new_T);

	// pop n^th node, return a ptr to that ndoe
	List<T> *Pop(LineList<T>::Index to_pop);

	// delete a node from its list, return a pointer to the deleted node
	static ListNode<T> *Delete(ListNode<T> *to_del);

	std::size_t GetLen() const;

	bool Empty() const {
		// return true if empty
		return (head_ == tail_);
	}

	// return NULL if position doesn't exist
	ListNode<T> *GetNode(Index cur_ind) const;

	// return error (Index < 0) when cur_node doesn't exist
	Index GetIndex(ListNode<T> *cur_node) const;

protected:
	ListNode<T> *head_, *tail_;

	void Init();
};

template <class T>
ListNode<T> *LineList<T>::Pop(LineList<T>::Index to_pop) {
	ListNode<T> *cur_node = this->GetNode(to_pop);

	if (cur_node != NULL) {
		LineList<T>::Delete(to_pop);
	}

	return cur_node;
}

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
	this->Init();
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

	if (new_node == NULL) {
		std::cerr << "ListNode<T> *new_node = new (std::nothrow) ListNode<T>" << std::endl;
		std::cerr << "memory allocation error" << std::endl;
		return NULL;
	}

	new_node->data_ = new_T;
	ListNode<T> *old_next = cur_node->next_;
	cur_node->next_ = new_node;
	new_node->prev_ = cur_node;
	new_node->next_ = old_next;

	if (old_next != NULL) {
		old_next->prev_ = new_node;
	}

	return new_node;
}

template <class T>
static ListNode<T> *LineList<T>::InsertBefore(ListNode<T> *cur_node, T const &new_T) {
	ListNode<T> *new_node = new (std::nothrow) ListNode<T>;

	if (new_node == NULL) {
		std::cerr << "ListNode<T> *new_node = new (std::nothrow) ListNode<T>" << std::endl;
		std::cerr << "memory allocation error" << std::endl;
		return NULL;
	}

	return new_node;
}

template <class T>
static ListNode<T> *LineList<T>::Delete(ListNode<T> *to_del) {
	ListNode<T> *prev = to_del->prev_;
	ListNode<T> *next = to_del->next_;

	if (prev != NULL) {
		prev->next_ = next;
	}
	if (next != NULL) {
		next->prev_ = prev;
	}

	return to_del;
}

template <class T>
ListNode<T> *LineList<T>::Append(T const &new_T) {
	return LineList<T>::InsertAfter(tail_, new_T);
}

template <class T>
LineList<T>::Index LineList<T>::GetIndex(ListNode<T> *cur_node) const {
	LineList<T>::Index::Index ind = -1;

	ListNode<T> *temp = head_->next_;

	while (temp != NULL) {
		++ind;

		if (temp == cur_node) {
			return ind;
		}

		temp = temp->next_;
	}

	return -1;
}

template <class T>
ListNode<T> *LineList<T>::GetNode(LineList<T>::Index cur_ind) {
	if (cur_ind < 0) {
		return NULL;
	}

	ListNode<T> *temp = head_->next_;
	LineList<T>::Index count = 0;

	while (temp != NULL) {
		if (count == cur_ind) {
			return temp;
		}

		temp = temp->next_;
		++count;
	}

	return NULL;
}

#endif  // LINE_LIST_H
