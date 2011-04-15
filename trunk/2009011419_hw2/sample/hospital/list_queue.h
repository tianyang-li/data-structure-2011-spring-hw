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

// queue using linked list

#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "list_node.h"

template <class T>
class ListQueue {
public:
	ListQueue();
	~ListQueue();

	// TODO

protected:
	ListNode<T> *sentry_;
	ListNode<T> *head_, *tail_;

	// TODO
};

#endif

