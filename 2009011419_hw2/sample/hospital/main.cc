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

#include "adj_list_graph.h"

class Hospital {
public:
	Hospital();

	void Init();

private:
	int n_;  // # of cities
	AdjListGraph<int> city_;
};

Hospital::Hospital() {
}

void Hospital::Init() {
	std::cin >> this->n_;
	city_.MallocVert(this->n_);
}

int main(int argc, char **argv) {
	Hospital hospital;
	hospital.Init();
	return 0;
}
