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

#include "list_node.h"

template <class T>
class ListStack {
public:
	ListStack();
	~ListStack();

protected:
	ListNode<T> *top_;  // top of stack
};

template <class T>
ListStack<T>::ListStack() : top_(NULL) {
}

template <class T>
ListStack<T>::~ListStack() {
	if (this->top_ != NULL) {
		ListNode<T> *temp1 = this->top_, *temp2 = this->top_->next_;
		while (temp1 != NULL) {
			delete temp1;
			temp1 = temp2;
			if (temp1 != NULL) {
				temp2 = temp1->next_;
			}
		}
	}
}

#endif  // LIST_STACK_H
