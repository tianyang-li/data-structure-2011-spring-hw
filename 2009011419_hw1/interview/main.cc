#include <iostream>

#include "line_list.h"

class Interview {
public:
	typedef int ID;
	Interview();
	~Interview();
private:
	LineList<Interview::ID> people_;
	ListNode<Interview::ID> *insert_after_;

	int N_;  // # of interviewees
	int m_;  // separation distance

	void Init();

	// move cur_person_ past m people so new ID can be inserted after cur_person_
	void MovePastM();
};

Interview::Interview() : insert_after_(NULL) {
	this->Init();
}

void Interview::MovePastM() {
}

void Interview::Init() {
	this->insert_after_ = this->people_.GetSentryHead();

	std::cin >> this->N_ >> this->m_;

	Interview::ID temp_ID;
	for (int i = 0; i != this->N_; ++i) {
		std::cin >> temp_ID;

		this->MovePastM();
	}
}

int main(int argc, char **argv) {
	return 0;
}
