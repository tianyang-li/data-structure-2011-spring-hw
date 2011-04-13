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

#include "list_stack.h"

class Corsair {
private:
	static int const kMaxCoin = 60;

public:
	class State {  // search state
	public:
		State() {
		}

		State(State const &cur_state) {
			for (int i = 0; i != Corsair::kMaxCoin; ++i) {
				this->state[i] = cur_state.state[i];
			}
		}

		~State() {
		}

		bool state[Corsair::kMaxCoin];  // state[i] == true if i is added in a round

		State &operator=(State const &cur_state) {
			if (this != &cur_state) {
				for (int i = 0; i != Corsair::kMaxCoin; ++i) {
					this->state[i] = cur_state.state[i];
				}
			}
			return *this;
		}
	};

	Corsair();

	inline void Init();
	inline int Most();

private:
	int n_;  // # of coins
	int val_[Corsair::kMaxCoin];  // value of coins
	int owner_[Corsair::kMaxCoin];  // owner_[i] is the owner of the i^th coin
	int tot_;  // total val of coins
	static int const kNoOwner = -1;  // a coin doesn't have a owner
	int min_coin_[Corsair::kMaxCoin];
	static int const kNoCoin = -1;  // a owner doesn't have a coin, for this->min_coin_
	ListStack<State> state_;  // used in search
	int asset_[Corsair::kMaxCoin];  // the amount each person currently has

	inline void SortCoin();
	inline bool DivPossible(int people);
	inline bool NotReached(int subset, int people);  // Subset sum subset not reached
};

inline bool Corsair::NotReached(int subset, int people) {
	for (int i = 1; i != people; ++i) {
		if (this->asset_[i] != subset) {
			return true;
		}
	}
	return true;
}

inline bool Corsair::DivPossible(int people) {
	if (((people * this->val_[this->n_ - 1]) > this->tot_) || ((this->tot_ % people) != 0)) {
		return false;
	}
	this->state_.Clear();
	int subset = this->tot_ / people;  // what each person should get
	this->owner_[0] = 0;  // 0^th person has the 0^th coin
	for (int i = 1; i != this->n_; ++i) {
		this->owner_[i] = Corsair::kNoOwner;
	}
	this->min_coin_[0] = 0;  // 0^th person has the 0^th coin
	this->asset_[0] = this->val_[0];
	for (int i = 1; i != people; ++i) {
		this->min_coin_[i] = Corsair::kNoCoin;
		this->asset_[i] = 0;
	}
	while (this->NotReached(subset, people)) {
		return false;
	}
	return true;
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
	for (int i = this->n_ - 1; i != -1; --i) {
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
	this->SortCoin();
}

int main(int argc, char **argv) {
	Corsair corsair;
	corsair.Init();
	std::cout << corsair.Most() << std::endl;
	return 0;
}
