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

	int *cards_;  // numbers on the card

	void Init();
};

ScoreBoard::ScoreBoard() {
	Init();
}

ScoreBoard::~ScoreBoard() {
	delete [] this->cards_;
}

void ScoreBoard::Init() {
	std::cin >> this->m_;

	this->cards_ = new (std::nothrow) int[this->m_];

	if (this->cards_ == NULL) {
		std::cerr << "this->cards_ = new (std::nothrow) int[this->m_]";
		std::cerr << std::endl << "memory allocation error" << std::endl;
		return;
	}

	for (int i = 0; i != this->m_; ++i) {
		std::cin >> this->cards_[i];
	}

	std::cin >> this->X_;
}

int ScoreBoard::ActualScore() {
	int true_score;

	return true_score;
}

int main(int argc, char **argv) {
	ScoreBoard hw1;

	std::cout << hw1.ActualScore() << std::endl;

	return 0;
}
