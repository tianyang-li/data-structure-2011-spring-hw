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
	int n_;  // # of numbers

	int64_t *numbers;

	void Init();
};

Lottery::Lottery() {
	this->Init();
}

Lottery::~Lottery() {
}

void Lottery::Init() {
	std::cin >> this->n_;
	this->numbers = new (std::nothrow) int64_t[this->n_];

	if (this->numbers == NULL) {
		std::cerr << "this->numbers = new (std::nothrow) std::int64_t[this->n_]";
		std::cerr << std::endl << "memory allocation error" << std::endl;
		return;
	}

	for (int i = 0; i != this->n_; ++i) {
		std::cin >> this->numbers[i];
	}

	QuickSort<int64_t>(this->numbers, 0, this->n_ - 1);
}

bool Lottery::Win() {
	for (int i = 0; i != this->n_; ++i) {
		for (int j = 0; j != this->n_ - 1; ++j) {
			if (BinSearch<int64_t>(0, this->n_ - 1, this->numbers, this->numbers[i] + this->numbers[j])) {
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
