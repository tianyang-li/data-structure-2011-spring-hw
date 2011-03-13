#include <iostream>
#include <stdint.h>
#include <new>

#include "bin_search.h"
#include "quick_sort.h"

class Lottery {
public:
	Lottery();
	~Lottery();

	bool Win();

private:
	int n_;  // # of numbers_
	int64_t *numbers_;

	int sorted_size_;
	int64_t *sorted_;  // contain no repeats

	void Init();

	void RemoveRepeat();  // remove repeats in input
};

Lottery::Lottery() : sorted_size_(0) {
	this->Init();
}

Lottery::~Lottery() {
	delete [] this->numbers_;
	delete [] this->sorted_;
}

void Lottery::Init() {
	std::cin >> this->n_;
	this->numbers_ = new (std::nothrow) int64_t[this->n_];

	if (this->numbers_ == NULL) {
		std::cerr << "this->numbers_ = new (std::nothrow) std::int64_t[this->n_]";
		std::cerr << std::endl << "memory allocation error" << std::endl;
		return;
	}

	for (int i = 0; i != this->n_; ++i) {
		std::cin >> this->numbers_[i];
	}

	QuickSort<int64_t>(this->numbers_, 0, this->n_ - 1);

	this->RemoveRepeat();
}

void Lottery::RemoveRepeat() {
	this->sorted_ = new (std::nothrow) int64_t[this->n_];

	if (this->sorted_ == NULL) {
		std::cerr << "this->sorted_ = new (std::nothrow) int64_t[this->n_]";
		std::cerr << std::endl << "memory allocation error" << std::endl;
		return;
	}

	this->sorted_[0] = this->numbers_[0];

	for (int i = 1; i != this->n_; ++i) {
		if (this->numbers_[i] != this->sorted_[this->sorted_size_]) {
			++this->sorted_size_;
			this->sorted_[this->sorted_size_] = this->numbers_[i];
		}
	}
	++this->sorted_size_;
}

bool Lottery::Win() {
	int index;  // index of c such that there exists a, b such that a + b == c
	for (int i = 0; i != this->n_; ++i) {
		for (int j = 0; j != this->n_ - 1; ++j) {
			if (BinSearch<int64_t>(0, this->sorted_size_ - 1, this->numbers_, this->numbers_[i] + this->numbers_[j], index)) {
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char **argv) {
	Lottery lottery;
	if (lottery.Win()) {
		std::cout << "YES" << std::endl;
	}
	else {
		std::cout << "NO" << std::endl;
	}
	return 0;
}
