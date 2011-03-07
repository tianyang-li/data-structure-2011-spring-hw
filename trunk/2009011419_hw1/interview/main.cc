#include <iostream>

class Interview {
public:
	typedef int ID;
	Interview();
	~Interview();
private:
	void Init();
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
