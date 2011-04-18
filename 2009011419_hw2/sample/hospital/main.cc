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

	class DFSData {
	public:
		DFSData() : cur(NULL), to(NULL) {
		}

		AdjListGraph<CityPtr>::VertexPtr cur;
		ListNode<AdjListGraph<CityPtr>::VertexPtr> *to;
	};

	Hospital();
	~Hospital() {
		delete [] this->city_;
		delete [] this->stack;
	}

	bool Init();
	int MinCity();

private:
	int n_;  // # of cities
	AdjListGraph<Hospital::CityPtr> city_graph_;  // sort of like a bi-directed graph (non-directed edge is divided up into 2 reverse directed edges)
	Hospital::City *city_;  // point to city data

	DFSData *stack;
	inline void DFS1(AdjListGraph<CityPtr>::VertexPtr start);
	inline void DFS2(AdjListGraph<CityPtr>::VertexPtr start);
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
	AdjListGraph<CityPtr>::VertexPtr start = this->city_graph_.GetVertexPtr(root);
	// TODO: use DFS1() DFS2(), use my own stack
	this->stack = new (std::nothrow) DFSData[this->n_];
	this->city_graph_.InitVertFlag();
	/*
	this->city_graph_.NoEdgeDFS(this->city_graph_.GetVertexPtr(root), this->dfs1_proc_city1_
			, this->dfs1_proc_city2_, this->dfs1_proc_city3_, this->dfs1_proc_city4_);
	*/
	this->DFS1(start);
	this->city_graph_.InitVertFlag();
	/*
	this->city_graph_.NoEdgeDFS(this->city_graph_.GetVertexPtr(root), this->dfs2_proc_city1_
			, this->dfs2_proc_city2_, this->dfs2_proc_city3_, this->dfs2_proc_city4_);
	*/
	this->DFS2(start);
	return true;
}

inline void Hospital::DFS1(AdjListGraph<CityPtr>::VertexPtr start) {
	int64_t tmp;
	int top = 0;
	this->stack[0].cur = start;
	this->stack[0].to = start->adj_list.GetHead();
	start->flag = true;
	while (true) {
		if (stack[top].to == NULL) {
			--top;
			if (top == -1) {
				break;
			}
			tmp = stack[top].to->data_->data->subtree_weight + stack[top].to->data_->data->pop;
			stack[top].cur->data->subtree_weight += tmp;
			stack[top].cur->data->cost += (tmp + stack[top].to->data_->data->cost);
			stack[top].to = stack[top].cur->adj_list.IterateNext(stack[top].to);
		}
		else {
			if (!stack[top].to->data_->flag) {
				stack[top].to->data_->flag = true;
				stack[top + 1].cur = stack[top].to->data_;
				++top;
				stack[top].to = stack[top].cur->adj_list.GetHead();
			}
			else {
				stack[top].to = stack[top].cur->adj_list.IterateNext(stack[top].to);
			}
		}
	}
}

inline void Hospital::DFS2(AdjListGraph<CityPtr>::VertexPtr start) {
	bool *flag;
	flag = new (std::nothrow) bool[this->n_];
	int64_t tmp;
	int top = 0;
	this->stack[0].cur = start;
	this->stack[0].to = start->adj_list.GetHead();
	start->flag = true;
	while (true) {
		if (stack[top].to == NULL) {
			--top;
			if (top == -1) {
				break;
			}
			stack[top].to = stack[top].cur->adj_list.IterateNext(stack[top].to);
		}
		else {
			if (!flag[top] && top > 0) {
				tmp = stack[top - 1].cur->data->subtree_weight - stack[top].cur->data->pop
						+ stack[top - 1].cur->data->pop;
				stack[top].cur->data->cost = stack[top - 1].cur->data->cost +
						- (stack[top].cur->data->subtree_weight << 1) + tmp
						- stack[top].cur->data->pop;
				stack[top].cur->data->subtree_weight = tmp;
				flag[top] = 1;
			}
			if (!stack[top].to->data_->flag) {
				stack[top].to->data_->flag = true;
				stack[top + 1].cur = stack[top].to->data_;
				++top;
				stack[top].to = stack[top].cur->adj_list.GetHead();
				flag[top] = false;
			}
			else {
				stack[top].to = stack[top].cur->adj_list.IterateNext(stack[top].to);
			}
		}
	}
	delete [] flag;
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


