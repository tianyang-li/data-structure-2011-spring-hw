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

#include <cstddef>
#include <new>
#include <iostream>

#include "kmp.h"

class Repeat {
public:
	Repeat();
	~Repeat();

	inline bool Init();
	int RepFac();  // repetition factor

private:
	static int const kInitTabSize = 32;
	int n_;  // # of char in string
	char *str_;  // ptr to str, similar to a dynamic table (Section 17.4, CLRS)
	int tab_len_;  // size of memory allocated allocated by tab_len
	int *pf_;  // KMP prefix function for this->str_
	int *rep_fac_;

	bool InputStr();
};

inline int Repeat::RepFac() {
	this->rep_fac_ = new (std::nothrow) int[this->n_];
	if (NULL == this->rep_fac_) {
		std::cerr << "this->rep_fac_ = new (std::nothrow) int[this->n_];";
		std::cerr << std::endl << "Memory allocation error!" << std::endl;
		return -1;
	}
	this->rep_fac_[0] = 1;
	for (int i = 1; i != this->n_; ++i) {
		if (this->pf_[i] != -1) {
			if
		}
	}
	return (this->n_ / this->rep_fac_[this->n_ - 1]);
}

Repeat::Repeat() : n_(0), str_(NULL), tab_len_(0), pf_(NULL) {
}

Repeat::~Repeat() {
	delete [] this->str_;
	delete [] this->pf_;
	delete [] this->rep_fac_;
}

bool Repeat::InputStr() {
	this->tab_len_ = Repeat::kInitTabSize;
	this->str_ = new (std::nothrow) char[this->kInitTabSize];
	if (this->str_ == NULL) {
		std::cerr << "this->str_ = new (std::nothrow) char[this->kInitTabSize];" << std::endl;
		std::cerr << "Memory allocation error!" << std::endl;
		return false;
	}
	char inp_char;
	char *new_str;
	while (std::cin >> inp_char) {
		if (this->n_ + 1 == this->tab_len_) {
			this->tab_len_ <<= 1;
			new_str = new (std::nothrow) char[this->tab_len_];
			if (new_str == NULL) {
				std::cerr << "new_str = new (std::nothrow) char[this->tab_len_];" << std::endl;
				std::cerr << "Memory allocation error!" << std::endl;
				return false;
			}
			for (int i = 0; i != this->n_; ++i) {
				new_str[i] = this->str_[i];
			}
			delete [] this->str_;
			this->str_ = new_str;
		}
		this->str_[this->n_] = inp_char;
		++this->n_;
	}
	return true;
}

inline bool Repeat::Init() {
	if (!this->InputStr()) {
		return false;
	}
	this->pf_ = new (std::nothrow) int[this->n_];
	if (this->pf_ == NULL) {
		std::cerr << "this->pf = new (std::nothrow) int[this->n_];" << std::endl;
		std::cerr << "Memory allocation error!" << std::endl;
		return false;
	}
	KMPPrefixFunction(this->str_, this->n_, this->pf_);
	return true;
}

int main(int argc, char **argv) {
	Repeat repeat;
	if (!repeat.Init()) {
		return 0;
	}
	std::cout << repeat.RepFac() << std::endl;
	return 0;
}
