#include <iostream>

#include "circ_list.h"
#include "list_node.h"

class Subway {
public:
	Subway();

	void MinCost();

private:
	struct Station {
		int u_;  // current total cost after U
		int d_;  // current total cost after D
		int c_;  // current total cost after C
	};

	int N_;  // # of stations

	CircList<Subway::Station> stations_;

	Subway::Station cur_station_;

	void Init();
};

Subway::Subway() {
	this->Init();

	this->cur_station_.u_ = this->cur_station_.d_ = this->cur_station_.c_ = 0;
	this->stations_.Append(this->cur_station_);

	Subway::Station temp_station1;
	for (int i = 0; i != this->N_; ++i) {
		std::cin >> temp_station1.u_ >> temp_station1.d_ >> temp_station1.c_;

		if (this->cur_station_.u_ + temp_station1.d_
				< this->cur_station_.c_ + temp_station1.d_) {
			temp_station1.d_ = this->cur_station_.u_ + temp_station1.d_;
		}
		else {
			temp_station1.d_ = this->cur_station_.c_ + temp_station1.d_;
		}

		if (this->cur_station_.u_ + temp_station1.c_
				< this->cur_station_.d_ + temp_station1.c_) {
			temp_station1.c_ = this->cur_station_.u_ + temp_station1.c_;
		}
		else {
			temp_station1.c_ = this->cur_station_.d_ + temp_station1.c_;
		}

		if (this->cur_station_.d_ + temp_station1.u_
				< this->cur_station_.c_ + temp_station1.u_) {
			temp_station1.u_ = this->cur_station_.d_ + temp_station1.u_;
		}
		else {
			temp_station1.u_ = this->cur_station_.c_ + temp_station1.u_;
		}

		this->cur_station_ = temp_station1;
		this->stations_.Append(this->cur_station_);
	}
}

void Subway::Init() {
	std::cin >> this->N_;
}

void Subway::MinCost() {
	int min_cost = this->cur_station_.u_;
	if (min_cost > this->cur_station_.d_) {
		min_cost = this->cur_station_.d_;
	}
	if (min_cost > this->cur_station_.c_) {
		min_cost = this->cur_station_.c_;
	}
	std::cout << min_cost;
}

int main(int argc, char **argv) {
	Subway subway;
	subway.MinCost();
	return 0;
}

