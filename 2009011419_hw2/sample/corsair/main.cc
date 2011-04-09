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
	int coins_[60][60];  // coins_[i][j] is the j^th coin owned by the i^th person
	int num_[60];  // num_[i] is the # of coins owned by the i^th person

	void SortCoin();
};

Corsair::Corsair() : tot_(0) {
}

void Corsair::SortCoin() {
	int temp_swap;
	for (int i = this->n_ - 1; i != -1; --i) {
		for (int j = 0; j != i; ++i) {
			if (this->val_[j] > this->val_[j + 1]) {
				temp_swap = this->val_[j];
				this->val_[j] = this->val_[j + 1];
				this->val_[j + 1] = temp_swap;
			}
		}
	}
}

void Corsair::Init() {
	std::cin >> this->n_;
	for (int i = 0; i != this->n_; ++i) {
		std::cin >> this->val_[i];
		this->tot_ += this->val_[i];
		this->num_[i] = 0;
	}
}

int main(int argc, char **argv) {
	Corsair corsair;
	corsair.Init();
	return 0;
}
