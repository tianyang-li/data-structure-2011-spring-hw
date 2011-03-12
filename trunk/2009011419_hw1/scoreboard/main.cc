#include <iostream>
#include <new>

class ScoreBoard {
public:
	ScoreBoard();
	~ScoreBoard();

	int ActualScore();

private:
	int m_;  // # of cards used
	int X_;  // score as observed

	int m_power_;  // used to add up score

	int *cards_;  // numbers on the card

	int true_score_;  // true score in decimal

	void Init();
};

ScoreBoard::ScoreBoard() : m_power_(1), true_score_(0) {
	Init();
}

ScoreBoard::~ScoreBoard() {
	delete [] this->cards_;
}

void ScoreBoard::Init() {
	std::cin >> this->m_;

	this->cards_ = new (std::nothrow) int[10];

	if (this->cards_ == NULL) {
		std::cerr << "this->cards_ = new (std::nothrow) int[this->m_]";
		std::cerr << std::endl << "memory allocation error" << std::endl;
		return;
	}

	int temp_card;
	for (int i = 0; i != this->m_; ++i) {
		std::cin >> temp_card;
		this->cards_[temp_card] = i;
	}

	std::cin >> this->X_;
}

int ScoreBoard::ActualScore() {
	int cur_card;  // # on current card
	while (this->X_ != 0) {
		cur_card =  this->X_ % 10;
		this->true_score_ += (this->m_power_ * this->cards_[cur_card]);

		this->X_ /= 10;
		this->m_power_ *= this->m_;
	}

	return this->true_score_;
}

int main(int argc, char **argv) {
	ScoreBoard hw1;

	std::cout << hw1.ActualScore() << std::endl;

	return 0;
}
