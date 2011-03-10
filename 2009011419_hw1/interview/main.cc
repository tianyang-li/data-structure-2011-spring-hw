#include <iostream>

#include "circ_list.h"
#include "list_node.h"

class Interview {
public:
	Interview();
	~Interview();

private:
	CircList<int> people_;

	int N_;  // # of interviewee
	int m_;  // # to skip each time

	ListNode<int> *cur_node_;  // current node to insert after;

	void Init();

	void MoveByM();  // move cur_node_ through the list as stated
};

Interview::Interview() {
	this->Init();
}

Interview::~Interview() {
}

void Interview::MoveByM() {
}

void Interview::Init() {
	std::cin >> this->N_ >> this->m_;

	int temp_ID;

	std::cin >> temp_ID;
	this->cur_node_ = this->people_.InsertAfter(temp_ID, 0);

	for (int i = 1; i != this->N_; ++i) {
		std::cin >> temp_ID;
		this->MoveByM();
		CircList<int>::InsertAfter(*this, this->cur_node_, temp_ID);
	}
}

int main(int argc, char **argv) {
	return 0;
}
