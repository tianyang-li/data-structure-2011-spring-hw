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

class Corsair {
public:
	Corsair();
	void Init();

private:
	int n_;  // # of coins
	int val_[60];  // value of coins
	int owner_[60];  // owner_[i] is the owner of the i^th coin
	int tot_;  // total val of coins
};

Corsair::Corsair() : tot_(0) {
}

void Corsair::Init() {
	std::cin >> this->n_;
	for (int i = 0; i != this->n; ++i) {
		std::cin >> this->val_[i];
		this->tot_ += this->val_[i];
	}
}

int main(int argc, char **argv) {
	Corsair corsair;
	corsair.Init();
	return 0;
}
