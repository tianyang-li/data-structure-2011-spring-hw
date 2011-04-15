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

		int64_t pop;  // population
		CircList<int64_t> neigbor_cost;
	};
	typedef City *CityPtr;

	class Br {  // bridge
	public:
		int64_t w;  // weighted distance of two subtrees created by removing this bridge
	};
	typedef Br *BrPtr;

	class ProcCity1 : public AdjListGraph<CityPtr, BrPtr>::ProcVert {
	public:
		void Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge);
	};

	class ProcCity2 : public AdjListGraph<CityPtr, BrPtr>::ProcVert {
	public:
		void Proc(AdjListGraph<CityPtr, BrPtr>::VertexPtr cur_vert
				, AdjListGraph<CityPtr, BrPtr>::VertexPtr from_vert
				, AdjListGraph<CityPtr, BrPtr>::EdgePtr from_edge);
	};

	Hospital();

	bool Init();
	int MinCity();

private:
	int n_;  // # of cities
	AdjListGraph<Hospital::CityPtr, BrPtr> city_graph_;  // sort of like a bi-directed graph (non-directed edge is divided up into 2 reverse directed edges)
	Hospital::CityPtr *city_ptr_;  // point to city data
	ProcCity1 proc_city_1_;
	ProcCity2 proc_city_2_;
};

Hospital::Hospital() {
}

bool Hospital::Init() {
	std::cin >> this->n_;
	if (!this->city_graph_.MallocVertPtr(this->n_) || !this->city_graph_.MallocEdgePtr((this->n_ - 1) << 1)) {  // 2 (n -1) directed edges
		return false;
	}
	this->city_ptr_ = new (std::nothrow) Hospital::CityPtr[this->n_];
	if (NULL == this->city_ptr_) {
		std::cerr << "this->city_ptr_ = new (std::nothrow) Hospital::CityPtr[this->n_];";
		std::cerr << std::endl << "Memory allocation problem!" << std::endl;
		return false;
	}
	int temp_pop;
	for (int i = 0; i != this->n_; ++i) {
		std::cin >> temp_pop;
		this->city_ptr_[i] = new (std::nothrow) Hospital::City(temp_pop);
		if (NULL == this->city_ptr_[i]) {
			std::cerr << "this->city_ptr_[i] = new (std::nothrow) Hospital::City(temp_pop);";
			std::cerr << std::endl << "Memory allocation error!" << std::endl;
			return false;
		}
		this->city_graph_.AddVert(i, this->city_ptr_[i]);
	}
	int n_minus_1 = this->n_ - 1;
	int tmp_city1, tmp_city2;
	for (int i = 0 ; i != n_minus_1; ++i) {
		std::cin >> tmp_city1 >> tmp_city2;
		this->city_graph_.AddNeighbor(tmp_city1, tmp_city2);
		this->city_graph_.AddNeighbor(tmp_city1, tmp_city2);
	}
	this->city_graph_.DFS(this->city_graph_.GetVertexPtr(std::rand() % this->city_graph_.GetSize()), this->proc_city_1_, this->proc_city_2_);
	this->city_graph_.DFS(this->city_graph_.GetVertexPtr(std::rand() % this->city_graph_.GetSize()), this->proc_city_1_, this->proc_city_2_);
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

int Hospital::MinCity() {
	return 0;
}

int main(int argc, char **argv) {
	Hospital hospital;
	if (!hospital.Init()) {
		return 0;
	}
	std::cout << hospital.MinCity() << std::endl;
	return 0;
}
