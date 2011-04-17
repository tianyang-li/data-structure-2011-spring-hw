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

// graph implemented using adjacency list (directed graph)

#include <cstddef>
#include <new>

#include "circ_list.h"
#include "list_queue.h"

template <class T>  // T - vertex, U - edge
class AdjListGraph {
public:
	class Vertex {
	public:
		class AdjInfo {
		public:
			AdjInfo() {
			}

			AdjInfo(Vertex *cur_vert) : vert(cur_vert) {
			}

			~AdjInfo() {
			}

			AdjInfo(AdjInfo const &cur_adj_info)
			: vert(cur_adj_info.vert) {
			}

			AdjInfo &operator=(AdjInfo const &cur_adj_info) {
				if (this != &cur_adj_info) {
					this->vert = cur_adj_info.vert;
				}
				return *this;
			}

			Vertex *vert;
		};

		Vertex();
		Vertex(T const &new_data) : data(new_data) {
		}

		CircList<typename AdjListGraph<T>::Vertex::AdjInfo> adj_list;  // adjacency list
		T data;
		bool flag;  // used in DFS, BFS, etc.
	};
	typedef Vertex *VertexPtr;

	// XXX: modify this approach?
	class NoEdgeDFSProcVert1 {  // process vertex
	public:
		inline virtual void Proc(VertexPtr cur_vert
				, VertexPtr from_vert /* entered cur_vert from from_vert */) = 0;
		// args should have been set in each vertex, edge
	};

	class NoEdgeDFSProcVert2 {  // process vertex
	public:
		inline virtual void Proc(VertexPtr cur_vert
				, VertexPtr from_vert /* entered cur_vert from from_vert */
				, VertexPtr to_vert /* entered cur_vert from from_vert */) = 0;
		// args should have been set in each vertex, edge
	};

	class NoEdgeDFSProcVert3 {  // process vertex
	public:
		inline virtual void Proc(VertexPtr cur_vert
				, VertexPtr from_vert /* entered cur_vert from from_vert */
				, VertexPtr to_vert /* entered cur_vert from from_vert */) = 0;
		// args should have been set in each vertex, edge
	};

	class NoEdgeDFSProcVert4 {  // process vertex
	public:
		inline virtual void Proc(VertexPtr cur_vert
				, VertexPtr from_vert /* entered cur_vert from from_vert */) = 0;
		// args should have been set in each vertex, edge
	};

	AdjListGraph();  // alloc memory for ptr
	~AdjListGraph();

	inline std::size_t GetSize() const {
		return this->V_;
	}
	inline VertexPtr GetVertexPtr(std::size_t get_vert) const {
		return this->vertex_[get_vert];
	}
	inline VertexPtr AddVert(std::size_t new_vert);  // no bound checking! only after MallocVertPtr, alloc memory for vertex
	inline VertexPtr AddVert(std::size_t new_vert, T const &new_data);  // no bound checking! only after MallocVertPtr, alloc memory for vertex

	inline bool MallocVertPtr(std::size_t more_vert);  // alloc memory for more_vert new vertice ptrs

	inline void AddNeighbor(std::size_t cur_v, std::size_t new_nb);  // directed, no checking, add new_nb to cur_v's neighbor (= add edge), cur_v -> new_nb

	inline void NoEdgeDFS(VertexPtr start, NoEdgeDFSProcVert1 &proc1, NoEdgeDFSProcVert2 &proc2
			, NoEdgeDFSProcVert3 &proc3, NoEdgeDFSProcVert4 &proc4
			, VertexPtr from_vert = NULL /* entered start from from_vert */);  // depth first search

	// TODO BFS(), BFSProc classes
	/*
	inline void BFS(VertexPtr start, ProcVert &proc
			, VertexPtr from_vert = NULL, EdgePtr from_edge = NULL);  // breadth first search
	*/

	inline void InitVertFlag() {  // set all flags in Vertex to false
		for (std::size_t i = 0; i != this->V_; ++i) {
			this->vertex_[i]->flag = false;
		}
	}

	// enough ptrs?
	inline bool NeedVertPtr(std::size_t more_vert = 1) {
		return (this->vert_tab_size_ <= (this->V_ + more_vert));
	}

protected:
	static std::size_t const kInitTabSize = 32;
	std::size_t vert_tab_size_;
	std::size_t V_;  // # of vertices
	typename AdjListGraph<T>::VertexPtr *vertex_;
	std::size_t E_;  // # of edges

	inline void Init();
};

template <class T>
AdjListGraph<T>::AdjListGraph()
: vert_tab_size_(AdjListGraph<T>::kInitTabSize), V_(0), vertex_(NULL)
  , E_(0) {
	this->Init();
}

template <class T>
AdjListGraph<T>::~AdjListGraph() {
	for (std::size_t i = 0; i != this->V_; ++i) {
		delete this->vertex_[i];
	}
	delete [] this->vertex_;
}

template <class T>
inline void AdjListGraph<T>::Init() {
	this->vertex_ = new (std::nothrow) VertexPtr[this->kInitTabSize];
	if (NULL == this->vertex_) {
		std::cerr << "this->vertex_ = new (std::nothrow) AdjListGraph<T>::VertexPtr[this->kInitTabSize];";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
		return;
	}
}

template <class T>
inline bool AdjListGraph<T>::MallocVertPtr(std::size_t more_vert) {
	std::size_t size_need = this->V_ + more_vert;
	if (size_need >= this->vert_tab_size_) {  // dynamic table (CLRS)
		while (size_need >= this->vert_tab_size_) {
			this->vert_tab_size_ <<= 1;
		}
		typename AdjListGraph<T>::VertexPtr *new_vert = new (std::nothrow) typename AdjListGraph<T>::VertexPtr[this->vert_tab_size_];
		if (NULL == new_vert) {
			std::cerr << "new_vert = new (std::nothrow) AdjListGraph<T>::VertexPtr[this->vert_tab_size_];";
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

template <class T>
inline typename AdjListGraph<T>::VertexPtr AdjListGraph<T>::AddVert(std::size_t new_vert) {
	this->vertex_[new_vert] = new (std::nothrow) typename AdjListGraph<T>::Vertex;
	if (NULL == this->vertex_[new_vert]) {
		std::cerr << "this->vertex_[new_vert] = new (std::nothrow) AdjListGraph<T>::Vertex;";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
	}
	++this->V_;
	return this->vertex_[new_vert];
}

template <class T>
inline typename AdjListGraph<T>::VertexPtr AdjListGraph<T>::AddVert(std::size_t new_vert, T const &new_data) {
	this->vertex_[new_vert] = new (std::nothrow) typename AdjListGraph<T>::Vertex(new_data);
	if (NULL == this->vertex_[new_vert]) {
		std::cerr << "this->vertex_[new_vert] = new (std::nothrow) AdjListGraph<T>::Vertex(new_data);";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
		return NULL;
	}
	++this->V_;
	return this->vertex_[new_vert];
}

template <class T>
inline void AdjListGraph<T>::AddNeighbor(std::size_t cur_v, std::size_t new_nb) {
	typename Vertex::AdjInfo temp_adj(this->vertex_[new_nb]);
	++this->E_;
	this->vertex_[cur_v]->adj_list.Append(temp_adj);
}

template <class T>
inline void AdjListGraph<T>::NoEdgeDFS(VertexPtr start, NoEdgeDFSProcVert1 &proc1, NoEdgeDFSProcVert2 &proc2
		, NoEdgeDFSProcVert3 &proc3, NoEdgeDFSProcVert4 &proc4, VertexPtr from_vert) {
	start->flag = true;
	proc1.Proc(start, from_vert);
	ListNode<typename Vertex::AdjInfo> *cur_nb = start->adj_list.GetHead();
	while (NULL != cur_nb) {
		if (false == cur_nb->data_.vert->flag) {
			proc2.Proc(start, from_vert, cur_nb->data_.vert);
			this->NoEdgeDFS(cur_nb->data_.vert, proc1, proc2, proc3, proc4, start);
			proc3.Proc(start, from_vert, cur_nb->data_.vert);
		}
		cur_nb = start->adj_list.IterateNext(cur_nb);
	}
	proc4.Proc(start, from_vert);
}

/*
template <class T>
inline void AdjListGraph<T>::BFS(VertexPtr start, ProcVert &proc
		, VertexPtr from_vert, EdgePtr from_edge) {
	// TODO
}
*/

#endif

