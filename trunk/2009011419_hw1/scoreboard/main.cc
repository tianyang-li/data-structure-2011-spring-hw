#include <iostream>

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

}

void ScoreBoard::Init() {
	std::cin >> this->m_;
}

int main(int argc, char **argv) {
	ScoreBoard hw1;

	std::cout << hw1.ActualScore() << std::endl;

	return 0;
}
