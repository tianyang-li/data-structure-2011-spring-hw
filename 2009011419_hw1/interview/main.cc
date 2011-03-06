#include <iostream>

#include "line_list.h"

class Interview {
public:
	Interview();
	~Interview();
private:
	void Init();

	LineList<int> people_;

	int N_;  // # of interviewees
	int m_;  // separation distance
};

Interview::Interview() {
	this->Init();
}

void Interview::Init() {
	cin >> this->N_ >> this->m_;
}

int main(int argc, char **argv) {
	return 0;
}
