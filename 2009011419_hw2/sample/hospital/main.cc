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

#include "adj_list_graph.h"
#include "circ_list.h"

class Hospital {
public:
	class City {
	public:
		City(int cur_pop) : pop(cur_pop) {
		}

		int pop;  // population
		CircList<int> neigbor_cost;
	};
	typedef City *CityPtr;

	class ProcCity : public AdjListGraph<CityPtr>::ProcVert {
	public:
		void Proc(AdjListGraph<CityPtr>::VertexPtr cur_vert) {
		}
	};

	Hospital();

	bool Init();

private:
	int n_;  // # of cities
	AdjListGraph<Hospital::CityPtr> city_graph_;
	Hospital::CityPtr *city_ptr_;  // point to city data
	ProcCity proc_sity_;  // function obj
};

Hospital::Hospital() {
}

bool Hospital::Init() {
	std::cin >> this->n_;
	if (!this->city_graph_.MallocVertPtr(this->n_)) {
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
	this->city_graph_.DFS(this->city_graph_.GetVertexPtr(std::rand() % this->city_graph_.GetSize()), this->proc_sity_);
	this->city_graph_.DFS(this->city_graph_.GetVertexPtr(std::rand() % this->city_graph_.GetSize()), this->proc_sity_);
	return true;
}

int main(int argc, char **argv) {
	Hospital hospital;
	if (!hospital.Init()) {
		return 0;
	}
	return 0;
}
