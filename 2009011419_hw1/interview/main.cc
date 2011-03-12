#include <iostream>

#include "circ_list.h"
#include "list_node.h"

class Interview {
public:
	Interview();

	void PrintOrder();  // print interview order

private:
	// ListNode<int> next_ counter clockwise
	// ListNode<int> prev_ clockwise
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

void Interview::MoveByM() {
	int to_move = (this->m_ - 1) % int(this->people_.GetLen());
	for (int i = 0; i != to_move; ++i) {
		this->cur_node_ = this->cur_node_->next_;
	}
}

void Interview::Init() {
	std::cin >> this->N_ >> this->m_;

	int temp_ID;

	std::cin >> temp_ID;
	this->cur_node_ = this->people_.InsertAfter(temp_ID, 0);

	for (int i = 1; i != this->N_; ++i) {
		std::cin >> temp_ID;
		this->MoveByM();
		this->cur_node_ = CircList<int>::InsertAfter(this->people_, this->cur_node_, temp_ID);
	}
}

void Interview::PrintOrder() {
	ListNode<int> *print_person = this->cur_node_;
	do {
		std::cout << print_person->data_;
		print_person = print_person->prev_;
		if (print_person != this->cur_node_) {
			std::cout << " ";
		}
	} while (print_person != this->cur_node_);
	std::cout << std::endl;
}

int main(int argc, char **argv) {
	Interview interview;
	interview.PrintOrder();
	return 0;
}
