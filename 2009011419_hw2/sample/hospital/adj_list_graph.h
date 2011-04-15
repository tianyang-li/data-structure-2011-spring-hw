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

template <class T, class U>  // T - vertex, U - edge
class AdjListGraph {
public:
	class Edge;
	class Vertex {
	public:
		class AdjInfo {
		public:
			AdjInfo() {
			}

			AdjInfo(Vertex *cur_vert, Edge *cur_edge) : vert(cur_vert), edge(cur_edge) {
			}

			~AdjInfo() {
			}

			AdjInfo(AdjInfo const &cur_adj_info)
			: vert(cur_adj_info.vert), edge(cur_adj_info.edge) {
			}

			AdjInfo &operator=(AdjInfo const &cur_adj_info) {
				if (this != &cur_adj_info) {
					this->vert = cur_adj_info.vert;
					this->edge = cur_adj_info.edge;
				}
				return *this;
			}

			Vertex *vert;
			Edge *edge;
		};

		Vertex();
		Vertex(T const &new_data) : data(new_data) {
		}

		CircList<AdjListGraph<T, U>::Vertex::AdjInfo> adj_list;  // adjacency list
		T data;
	};
	typedef Vertex *VertexPtr;

	class Edge {
	public:
		Edge();
		Edge(U const &new_data) : data(new_data) {
		}

		VertexPtr v[2];  // connects v1 v2 (v1->v2 in directed graph)
		U data;
	};
	typedef Edge *EdgePtr;

	class ProcVert {  // process vertex
	public:
		virtual void Proc(VertexPtr cur_vert
				, VertexPtr from_vert /* entered cur_vert from from_vert */
				, EdgePtr from_edge /*entered cur_vert from from_vert using from_edge*/) = 0;
		// args should have been set in each vertex
		// XXX: modify this approach?
	};

	AdjListGraph();  // alloc memory for ptr
	~AdjListGraph();

	inline std::size_t GetSize() const {
		return this->V_;
	}
	inline VertexPtr GetVertexPtr(std::size_t get_vert) const {
		return this->vertex_[get_vert];
	}
	inline void AddVert(std::size_t new_vert);  // no bound checking! only after MallocVertPtr, alloc memory for vertex
	inline void AddVert(std::size_t new_vert, T const &new_data);  // no bound checking! only after MallocVertPtr, alloc memory for vertex

	inline bool MallocVertPtr(std::size_t more_vert);  // alloc memory for more_vert new vertice ptrs

	inline void AddNeighbor(std::size_t cur_v, std::size_t new_nb);  // directed, no checking, add new_nb to cur_v's neighbor (= add edge), cur_v -> new_nb
	inline void DFS(VertexPtr start, ProcVert &proc1, ProcVert &proc2
			, VertexPtr from_vert = NULL, EdgePtr from_edge = NULL);  // depth first search
	inline void BFS(VertexPtr start, ProcVert &proc1, ProcVert &proc2
			, VertexPtr from_vert = NULL, EdgePtr from_edge = NULL);  // breadth first search
	inline bool MallocEdgePtr(std::size_t more_edge);

protected:
	static std::size_t const kInitTabSize = 32;
	std::size_t vert_tab_size_;
	std::size_t V_;  // # of vertices
	AdjListGraph<T, U>::VertexPtr *vertex_;
	std::size_t E_;  // # of edges
	std::size_t edge_tab_size_;
	AdjListGraph<T, U>::EdgePtr *edge_;

	inline void Init();
	inline void InitEdge();
};

template <class T, class U>
inline bool AdjListGraph<T, U>::MallocEdgePtr(size_t more_edge) {
	std::size_t size_need = more_edge + this->E_;
	if (size_need >= this->edge_tab_size_) {
		while (size_need >= this->edge_tab_size_) {
			this->edge_tab_size_ <<= 1;
		}
		AdjListGraph<T, U>::EdgePtr *new_edge = new (std::nothrow) AdjListGraph<T, U>::EdgePtr;
		if (NULL == new_edge) {
			std::cerr << "AdjListGraph<T, U>::EdgePtr *new_edge = new (std::nothrow) AdjListGraph<T, U>::EdgePtr;";
			std::cerr << std::endl << "Memory allocation error" << std::endl;
			return false;
		}
		for (std::size_t i = 0; i != this->E_; ++i) {
			new_edge[i] = this->edge_[i];
		}
		delete [] this->edge_;
		this->edge_ = new_edge;
	}
	return true;
}

template <class T, class U>
inline void AdjListGraph<T, U>::InitEdge() {
	this->edge_ = new (std::nothrow) AdjListGraph<T, U>::EdgePtr[this->kInitTabSize];
	if (NULL == this->edge_) {
		std::cerr << "this->edge_ = new (std::nothrow) AdjListGraph<T, U>::VertexPtr[this->kInitTabSize];";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
		return;
	}
}

template <class T, class U>
AdjListGraph<T, U>::AdjListGraph()
: vert_tab_size_(AdjListGraph<T, U>::kInitTabSize), V_(0), vertex_(NULL)
  , E_(0), edge_tab_size_(AdjListGraph<T, U>::kInitTabSize), edge_(NULL)  {
	this->Init();
}

template <class T, class U>
AdjListGraph<T, U>::~AdjListGraph() {
	for (std::size_t i = 0; i != this->V_; ++i) {
		delete this->vertex_[i];
	}
	delete [] this->vertex_;
	for (std::size_t i = 0; i != this->E_; ++i) {
		delete this->edge_[i];
	}
	delete [] this->edge_;
}

template <class T, class U>
inline void AdjListGraph<T, U>::Init() {
	this->vertex_ = new (std::nothrow) AdjListGraph<T, U>::VertexPtr[this->kInitTabSize];
	if (NULL == this->vertex_) {
		std::cerr << "this->vertex_ = new (std::nothrow) AdjListGraph<T, U>::VertexPtr[this->kInitTabSize];";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
		return;
	}
	this->InitEdge();
}

template <class T, class U>
inline bool AdjListGraph<T, U>::MallocVertPtr(std::size_t more_vert) {
	std::size_t size_need = this->V_ + more_vert;
	if (size_need >= this->vert_tab_size_) {  // dynamic table (CLRS)
		while (size_need >= this->vert_tab_size_) {
			this->vert_tab_size_ <<= 1;
		}
		AdjListGraph<T, U>::VertexPtr *new_vert = new (std::nothrow) AdjListGraph<T, U>::VertexPtr[this->vert_tab_size_];
		if (NULL == new_vert) {
			std::cerr << "new_vert = new (std::nothrow) AdjListGraph<T, U>::VertexPtr[this->vert_tab_size_];";
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

template <class T, class U>
inline void AdjListGraph<T, U>::AddVert(std::size_t new_vert) {
	this->vertex_[new_vert] = new (std::nothrow) AdjListGraph<T, U>::Vertex;
	if (NULL == this->vertex_[new_vert]) {
		std::cerr << "this->vertex_[new_vert] = new (std::nothrow) AdjListGraph<T, U>::Vertex;";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
	}
}

template <class T, class U>
inline void AdjListGraph<T, U>::AddVert(std::size_t new_vert, T const &new_data) {
	this->vertex_[new_vert] = new (std::nothrow) AdjListGraph<T, U>::Vertex(new_data);
	if (NULL == this->vertex_[new_vert]) {
		std::cerr << "this->vertex_[new_vert] = new (std::nothrow) AdjListGraph<T, U>::Vertex(new_data);";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
	}
}

template <class T, class U>
inline void AdjListGraph<T, U>::AddNeighbor(std::size_t cur_v, std::size_t new_nb) {
	typename Vertex::AdjInfo temp_adj(this->vertex_[new_nb], this->edge_[this->E_]);
	++this->E_;
	this->vertex_[cur_v]->adj_list.Append(temp_adj);
}

template <class T, class U>
inline void AdjListGraph<T, U>::DFS(VertexPtr start, ProcVert &proc1, ProcVert &proc2
		, VertexPtr from_vert, EdgePtr from_edge) {
	proc1.Proc(start, from_vert, from_edge);
	ListNode<typename Vertex::AdjInfo> *cur_nb = start->adj_list.GetHead();
	while (NULL != cur_nb) {
		// TODO
		proc2.Proc(start, from_vert, from_edge);
		cur_nb = start->adj_list.IterateNext(cur_nb);
	}
}

template <class T, class U>
inline void AdjListGraph<T, U>::BFS(VertexPtr start, ProcVert &proc1, ProcVert &proc2
		, VertexPtr from_vert, EdgePtr from_edge) {
	// TODO
}

#endif

