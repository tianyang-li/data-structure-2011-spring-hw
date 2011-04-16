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

#include "adj_list_graph.h"
#include "circ_list.h"

class Hospital {
public:
	class City {
	public:
		City(int cur_pop) : pop(cur_pop) {
		}
		City() {
		}

		int64_t pop;  // population
		//CircList<int64_t> neigbor_cost;
	};
	typedef City *CityPtr;

	class Br {  // bridge
	public:
		Br() : w(0) {
		}

		int64_t w;  // weighted distance of two subtrees created by removing this bridge
		AdjListGraph<CityPtr, Br *>::EdgePtr rev;  // ptr to reverse edge
	};
	typedef Br *BrPtr;

	class ProcCity1 : public AdjListGraph<CityPtr, BrPtr>::ProcVert {
	public:
		inline void Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge);
	};

	class ProcCity2 : public AdjListGraph<CityPtr, BrPtr>::ProcVert {
	public:
		inline void Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge);
	};

	class ProcCity3 : public AdjListGraph<CityPtr, BrPtr>::ProcVert {
	public:
		inline void Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge);
	};

	Hospital();
	~Hospital() {
		delete [] this->city_;
		delete [] this->br_;
	}

	bool Init();
	int MinCity();

private:
	int n_;  // # of cities
	AdjListGraph<Hospital::CityPtr, BrPtr> city_graph_;  // sort of like a bi-directed graph (non-directed edge is divided up into 2 reverse directed edges)
	Hospital::City *city_;  // point to city data
	Hospital::Br *br_;
	ProcCity1 proc_city1_;
	ProcCity2 proc_city2_;
	ProcCity3 proc_city3_;
};

Hospital::Hospital() {
}

bool Hospital::Init() {
	std::cin >> this->n_;
	if (!this->city_graph_.MallocVertPtr(this->n_)) {
		return false;
	}
	this->city_ = new (std::nothrow) Hospital::City[this->n_];
	if (NULL == this->city_) {
		std::cerr << "this->city_ = new (std::nothrow) Hospital::CityPtr[this->n_];";
		std::cerr << std::endl << "Memory allocation problem!" << std::endl;
		return false;
	}
	int64_t temp_pop;
	for (int i = 0; i != this->n_; ++i) {
		std::cin >> temp_pop;
		this->city_[i].pop = temp_pop;
		this->city_graph_.AddVert(i, &this->city_[i]);
	}
	int n_minus_1 = this->n_ - 1;
	if (!this->city_graph_.MallocEdgePtr(n_minus_1 << 1)) {
		return false;
	}
	this->br_ = new (std::nothrow) Br[n_minus_1 << 1];
	int tmp_city1, tmp_city2;
	AdjListGraph<CityPtr, BrPtr>::EdgePtr cur_br1, cur_br2;
	for (int i = 0 ; i != n_minus_1; ++i) {
		std::cin >> tmp_city1 >> tmp_city2;
		--tmp_city1;
		--tmp_city2;
		cur_br1 = this->city_graph_.AddNeighbor(tmp_city1, tmp_city2, &this->br_[i << 1]);
		cur_br2 = this->city_graph_.AddNeighbor(tmp_city2, tmp_city1, &this->br_[(i << 1) + 1]);
		cur_br1->data->rev = cur_br2;
		cur_br2->data->rev = cur_br1;
	}
	this->city_graph_.InitFlag();
	this->city_graph_.DFS(this->city_graph_.GetVertexPtr(std::rand() % this->city_graph_.GetSize()), this->proc_city1_, this->proc_city2_, this->proc_city3_);
	this->city_graph_.InitFlag();
	this->city_graph_.DFS(this->city_graph_.GetVertexPtr(std::rand() % this->city_graph_.GetSize()), this->proc_city1_, this->proc_city2_, this->proc_city3_);
	return true;
}

void Hospital::ProcCity1::Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge) {

}

void Hospital::ProcCity2::Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge) {

}

void Hospital::ProcCity3::Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
		, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
		, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge) {

}

int Hospital::MinCity() {
	return 0;
}

int main(int argc, char **argv) {
	Hospital hospital;
	if (!hospital.Init()) {
		return 0;
	}
	std::cout << (hospital.MinCity() + 1) << std::endl;
	return 0;
}
