#include <iostream>

#include "circ_list.h"

class Interview {
public:
	typedef unsigned int ID;
	Interview();
	~Interview();

private:
	void Init();

	CircList<Interview::ID> people_;
};

Interview::Interview() {
	this->Init();
}

Interview::~Interview() {

}

void Interview::Init() {

}

int main(int argc, char **argv) {
	return 0;
}
