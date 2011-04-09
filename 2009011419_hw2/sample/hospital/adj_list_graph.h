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

#ifndef ADJ_LIST_GRAPH_H_
#define ADJ_LIST_GRAPH_H_

// graph implemented using adjacency list

#include <cstddef>
#include <new>

#include "circ_list.h"

template <class T>
class AdjListGraph {
public:
	class Vertex {
	public:
		CircList<AdjListGraph<T>::Vertex *> adj_list;  // adjacency list
		T data;
	};
	typedef Vertex *VertexPtr;

	AdjListGraph(std::size_t init_size = 0);
	~AdjListGraph();

	std::size_t GetSize() const {
		return this->V_;
	}

	inline bool MallocVert(std::size_t more_vert);  // alloc memory for more_vert new vertices

protected:
	static std::size_t const kInitTabSize = 32;
	std::size_t tab_size_;
	std::size_t V_;  // # of vertices
	AdjListGraph<T>::VertexPtr *vertex_;

	void Init();
};

template <class T>
AdjListGraph<T>::AdjListGraph(std::size_t init_size) : tab_size_(AdjListGraph<T>::kInitTabSize), V_(init_size), vertex_(NULL) {
	this->Init();
}

template <class T>
AdjListGraph<T>::~AdjListGraph() {
	delete [] this->vertex_;
}

template <class T>
void AdjListGraph<T>::Init() {
	this->vertex_ = new (std::nothrow) AdjListGraph<T>::VertexPtr[this->kInitTabSize];
	if (this->vertex_ == NULL) {
		std::cerr << "this->vertex_ = new (std::nothrow) AdjListGraph<T>::VertexPtr[this->kInitTabSize];";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
		return;
	}
}

template <class T>
inline bool AdjListGraph<T>::MallocVert(std::size_t more_vert) {
	if (this->V_ + more_vert == this->tab_size_) {  // dynamic table (CLRS)
		AdjListGraph<T>::VertexPtr *new_vert;
		this->tab_size_ <<= 1;
		new_vert = new (std::nothrow) AdjListGraph<T>::VertexPtr[this->tab_size_];
		if (new_vert == NULL) {
			std::cerr << "new_vert = new (std::nothrow) AdjListGraph<T>::VertexPtr[this->tab_size_];";
			std::cerr << std::endl << "Memory allocation error" << std::endl;
			return false;
		}
		for (std::size_t i = 0; i != this->V_; ++i) {
			new_vert[i] = this->vertex_[i];
		}
		delete [] this->vertex_;
		this->vertex_ = new_vert;
	}
	return true;
}

#endif

