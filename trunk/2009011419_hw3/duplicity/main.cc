#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "hash1.h"

using namespace std;

class Duplicity {
public:
	inline Duplicity();
	inline ~Duplicity();

private:
	inline void Init();
};

inline Duplicity::Duplicity() {
	Init();
}

inline Duplicity::~Duplicity() {
}

inline void Duplicity::Init() {
}

int main(int argc, char **argv) {
	Duplicity dup;

	return 0;
}
