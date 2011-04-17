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

#include <iostream>
#include <new>
#include <cstdlib>
#include <stdint.h>
#include <ctime>
#include <cstdio>

#include "adj_list_graph.h"
#include "circ_list.h"

class Hospital {
public:
	class City {
	public:
		City() : cost(0), subtree_weight(0) {
		}

		int64_t pop;  // population
		int64_t cost;  // cost of building at this city
		int64_t subtree_weight;  //  weight of all subtrees by removing this city
	};
	typedef City *CityPtr;

	class DFS1ProcCity1 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert1 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert);
	};

	class DFS1ProcCity2 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert2 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr>::VertexPtr to_vert);
	};

	class DFS1ProcCity3 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert3 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr>::VertexPtr to_vert);
	};

	class DFS1ProcCity4 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert4 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert);
	};

	class DFS2ProcCity1 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert1 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert);
	};

	class DFS2ProcCity2 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert2 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr>::VertexPtr to_vert);
	};

	class DFS2ProcCity3 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert3 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr>::VertexPtr to_vert);
	};

	class DFS2ProcCity4 : public AdjListGraph<CityPtr>::NoEdgeDFSProcVert4 {
	public:
		inline void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr>::VertexPtr from_vert);
	};

	Hospital();
	~Hospital() {
		delete [] this->city_;
	}

	bool Init();
	int MinCity();

private:
	int n_;  // # of cities
	AdjListGraph<Hospital::CityPtr> city_graph_;  // sort of like a bi-directed graph (non-directed edge is divided up into 2 reverse directed edges)
	Hospital::City *city_;  // point to city data

	DFS1ProcCity1 dfs1_proc_city1_;
	DFS1ProcCity2 dfs1_proc_city2_;
	DFS1ProcCity3 dfs1_proc_city3_;
	DFS1ProcCity4 dfs1_proc_city4_;

	DFS2ProcCity1 dfs2_proc_city1_;
	DFS2ProcCity2 dfs2_proc_city2_;
	DFS2ProcCity3 dfs2_proc_city3_;
	DFS2ProcCity4 dfs2_proc_city4_;
};

Hospital::Hospital() {
}

bool Hospital::Init() {
	std::cin >> this->n_;
	this->city_ = new (std::nothrow) Hospital::City[this->n_];
	if (NULL == this->city_) {
		std::cerr << "this->city_ = new (std::nothrow) Hospital::CityPtr[this->n_];";
		std::cerr << std::endl << "Memory allocation problem!" << std::endl;
		return false;
	}
	if (!this->city_graph_.MallocVertPtr(this->n_)) {
		return false;
	}
	int64_t temp_pop;
	for (int i = 0; i != this->n_; ++i) {
		std::scanf("%lld", &temp_pop);
		this->city_[i].pop = temp_pop;
		this->city_graph_.AddVert(i, &this->city_[i]);
	}
	int n_minus_1 = this->n_ - 1;
	int tmp_city1, tmp_city2;
	for (int i = 0 ; i != n_minus_1; ++i) {
		std::scanf("%d %d", &tmp_city1, &tmp_city2);
		--tmp_city1;
		--tmp_city2;
		this->city_graph_.AddNeighbor(tmp_city1, tmp_city2);
		this->city_graph_.AddNeighbor(tmp_city2, tmp_city1);
	}
	std::srand(std::time(NULL));
	int root = std::rand() % this->city_graph_.GetSize();
	this->city_graph_.InitVertFlag();
	this->city_graph_.NoEdgeDFS(this->city_graph_.GetVertexPtr(root), this->dfs1_proc_city1_
			, this->dfs1_proc_city2_, this->dfs1_proc_city3_, this->dfs1_proc_city4_);
	this->city_graph_.InitVertFlag();
	this->city_graph_.NoEdgeDFS(this->city_graph_.GetVertexPtr(root), this->dfs2_proc_city1_
			, this->dfs2_proc_city2_, this->dfs2_proc_city3_, this->dfs2_proc_city4_);
	return true;
}

inline void Hospital::DFS1ProcCity1::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert) {
}

inline void Hospital::DFS1ProcCity2::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr>::VertexPtr to_vert) {
}

inline void Hospital::DFS1ProcCity3::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr>::VertexPtr to_vert) {
	static int64_t tmp2;
	tmp2 = to_vert->data->subtree_weight + to_vert->data->pop;
	cur_vert->data->subtree_weight += tmp2;
	cur_vert->data->cost += (to_vert->data->cost + tmp2);  // cost of current vertex
}

inline void Hospital::DFS1ProcCity4::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert) {
}

inline void Hospital::DFS2ProcCity1::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert) {
	if (NULL != from_vert) {
		static int64_t tmp1;
		tmp1 = from_vert->data->subtree_weight - cur_vert->data->pop + from_vert->data->pop;
		cur_vert->data->cost = from_vert->data->cost - cur_vert->data->subtree_weight + tmp1
				- cur_vert->data->pop - cur_vert->data->subtree_weight;
		cur_vert->data->subtree_weight = tmp1;
	}
}

inline void Hospital::DFS2ProcCity2::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr>::VertexPtr to_vert) {
}

inline void Hospital::DFS2ProcCity3::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr>::VertexPtr to_vert) {
}

inline void Hospital::DFS2ProcCity4::Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr>::VertexPtr from_vert) {
}

int Hospital::MinCity() {
	int min = 0;
	for (int i = 1; i != this->n_; ++i) {
		if (this->city_[i].cost < this->city_[min].cost) {
			min = i;
		}
	}
	return min;
}

int main(int argc, char **argv) {
	Hospital hospital;
	if (!hospital.Init()) {
		return 0;
	}
	std::cout << (hospital.MinCity() + 1) << std::endl;
	return 0;
}
