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

inline int Min(int a, int b) {
	return (a < b ? a : b);
}

class Corsair {
private:
	static int const kMaxCoin = 60;

public:
	Corsair();

	inline void Init();
	inline int Most();

private:
	int n_;  // # of coins
	int n_ind_;  // = n_ - 1
	int val_[Corsair::kMaxCoin];  // value of coins
	int owner_[Corsair::kMaxCoin];  // owner_[i] is the owner of the i^th coin
	int tot_;  // total val of coins
	int asset_[Corsair::kMaxCoin];
	int cur_max_owner_;  // because owners are searched from 0 up, this says
	int cur_coin_;  // current coin searching for owner, sort of like a stack ptr
	int min_coin_[Corsair::kMaxCoin];  // min_coin_[i] is lowest index in the indices of coins owned by the i^th person
	bool inc_max_owner_[Corsair::kMaxCoin];  // for each coin

	inline void SortCoin();
	inline bool DivPossible(int people);
	inline bool NotReached(int subset, int people);  // Subset sum subset not reached
};

inline bool Corsair::NotReached(int subset, int people) {
	for (int i = 0; i != people; ++i) {
		if (this->asset_[i] != subset) {
			return true;
		}
	}
	return false;
}

inline bool Corsair::DivPossible(int people) {  // people != 1, see Corsair::Most()
	if (((people * this->val_[0]) > this->tot_) || ((this->tot_ % people) != 0)) {
		return false;
	}
	int subset = this->tot_ / people;  // what each person should get
	this->asset_[0] = this->val_[0];
	for (int i = 1; i != people; ++i) {
		this->asset_[i] = 0;
	}
	for (int i = 0; i != this->n_; ++i) {
		this->inc_max_owner_[i] = false;
		this->owner_[i] = -1;
	}
	this->cur_max_owner_ = 0;  // can be equal to this in search
	this->cur_coin_ = 1;
	this->owner_[0] = 0;  // 0^th person has the 0^th coin
	int cur_owner;
	while (0 == this->owner_[0]) {
		if (this->cur_coin_ == this->n_ind_) {
			for (int j = 0; j != people; ++j) {
				this->asset_[j] += this->val_[this->cur_coin_];
				if (this->asset_[j] > subset) {  // TODO: compare performance of this IF
					this->asset_[j] -= this->val_[this->cur_coin_];
					continue;
				}
				if (!this->NotReached(subset, people - 1)) {
					return true;
				}
				this->asset_[j] -= this->val_[this->cur_coin_];
			}
			--this->cur_coin_;  // backtracking
		}
		else {
			cur_owner = this->owner_[this->cur_coin_];
			++this->owner_[this->cur_coin_];
			while ((this->inc_max_owner_[this->cur_coin_] ? (this->owner_[this->cur_coin_] <= this->cur_max_owner_) : (this->owner_[this->cur_coin_] <= this->cur_max_owner_ + 1))
					&& (this->asset_[this->owner_[this->cur_coin_]] + this->val_[this->cur_coin_] > subset)) {  // order of &&
						++this->owner_[this->cur_coin_];
					}
			if (this->inc_max_owner_[this->cur_coin_] ? (this->owner_[this->cur_coin_] > this->cur_max_owner_) : (this->owner_[this->cur_coin_] > this->cur_max_owner_ + 1)) {
				// backtracking
				if (this->inc_max_owner_[this->cur_coin_]) {
					this->inc_max_owner_[this->cur_coin_] = false;
					--this->cur_max_owner_;
				}
				if (-1 != cur_owner) {
					this->asset_[cur_owner] -= this->val_[this->cur_coin_];
				}
				this->owner_[this->cur_coin_] = -1;
				--this->cur_coin_;
			}
			else {
				if (-1 != cur_owner) {
					this->asset_[cur_owner] -= this->val_[this->cur_coin_];
				}
				this->asset_[this->owner_[this->cur_coin_]] += this->val_[this->cur_coin_];
				if (!this->inc_max_owner_[this->cur_coin_] && (this->cur_max_owner_ < people)
						&& (this->cur_max_owner_ + 1 == this->owner_[this->cur_coin_])) {
					this->inc_max_owner_[this->cur_coin_] = true;
					++this->cur_max_owner_;
				}
				++this->cur_coin_;
			}

		}
	}
	return false;
}

inline int Corsair::Most() {
	int people = this->n_;
	while (people != 1) {
		if (this->DivPossible(people)) {
			return people;
		}
		--people;
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
