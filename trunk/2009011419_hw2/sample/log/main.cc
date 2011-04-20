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
#include <cstdio>

#include "list_stack.h"

class Log {
public:
	void Proc();  // process log

private:
	ListStack<int> store_;  // warehouse storage
	ListStack<int> max_;  // max in warehouse
};

void Log::Proc() {
	int n;  // # of lines in log
	std::cin >> n;

	int action;  // 0 - in, 1 - out, 2 - query
	int mass;  // mass IO
	for (int i = 0; i != n; ++i) {
		std::scanf("%d", &action);
		switch (action) {
		//XXX: no error checking here!
		case 0:
			std::scanf("%d", &mass);
			if (!this->max_.Empty()) {
				if (mass >= this->max_.Top()) {
					this->max_.Push(mass);
				}
			}
			else {
				this->max_.Push(mass);
			}
			this->store_.Push(mass);
			break;
		case 1:
			mass = this->store_.Top();
			this->store_.Pop();
			if (mass == this->max_.Top()) {
				this->max_.Pop();
			}
			break;
		case 2:
			std::printf("%d\n", this->max_.Top());
			break;
		}
	}
}

int main(int argc, char **argv) {
	Log log;
	log.Proc();
	return 0;
}
