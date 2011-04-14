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
private:
	static int const kMaxCoin = 60;

public:
	Corsair();

	inline void Init();
	inline int Most();

private:
	int n_;  // # of coins
	int n_ind_;  // this->n_ -1
	int val_[Corsair::kMaxCoin];  // value of coins
	int tot_;  // total val of coins
	int asset_[Corsair::kMaxCoin];
	int people_;
	int subset_;
	int max_person_;

	inline void SortCoin();
	inline bool DivPossible();
	inline bool DFS(int cur_coin);
};

inline bool Corsair::DFS(int cur_coin) {
	if (cur_coin == this->n_) {
		return true;
	}
	bool ok = false;
	for (int i = 0; i <= this->max_person_; ++i) {
		int cur_asset = this->asset_[i] + this->val_[cur_coin];
		if (cur_asset <= this->subset_) {
			this->asset_[i] = cur_asset;
			ok = this->DFS(cur_coin + 1);
			if (ok) {
				return true;
			}
			this->asset_[i] -= this->val_[cur_coin];
		}
	}
	if (this->max_person_ != this->n_ind_) {
		++this->max_person_;
		int cur_asset = this->asset_[this->max_person_] + this->val_[cur_coin];
		if (cur_asset <= this->subset_) {
			this->asset_[this->max_person_] = cur_asset;
			ok = this->DFS(cur_coin + 1);
			if (ok) {
				return true;
			}
			this->asset_[this->max_person_] -= this->val_[cur_coin];
		}
		--this->max_person_;
	}
	return false;
}

inline bool Corsair::DivPossible() {  // people != 1, see Corsair::Most()
	this->subset_ = this->tot_ / this->people_;
	if (this->subset_ < this->val_[0]) {
		return false;
	}
	this->asset_[0] = this->val_[0];
	for (int i = 1; i != this->people_; ++i) {
		this->asset_[i] = 0;
	}
	return this->DFS(1);
}

inline int Corsair::Most() {
	this->max_person_ = 0;
	this->people_ = this->n_;
	while (this->people_ != 1) {
		if ((this->tot_ % this->people_ == 0) && this->DivPossible()) {
			return this->people_;
		}
		--this->people_;
	}
	return 1;
}

Corsair::Corsair() : tot_(0) {
}

inline void Corsair::SortCoin() {  // bubble sort
	int temp_swap;
	for (int i = this->n_ind_; i != -1; --i) {
		for (int j = 0; j != i; ++j) {
			if (this->val_[j] < this->val_[j + 1]) {
				temp_swap = this->val_[j];
				this->val_[j] = this->val_[j + 1];
				this->val_[j + 1] = temp_swap;
			}
		}
	}
}

inline void Corsair::Init() {
	std::cin >> this->n_;
	for (int i = 0; i != this->n_; ++i) {
		std::cin >> this->val_[i];
		this->tot_ += this->val_[i];
	}
	this->n_ind_ = this->n_ - 1;
	this->SortCoin();
}

int main(int argc, char **argv) {
	Corsair corsair;
	corsair.Init();
	std::cout << corsair.Most() << std::endl;
	return 0;
}
