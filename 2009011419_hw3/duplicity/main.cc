#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>

#include "hash1.h"

using namespace std;

class Duplicity {
private:
	static size_t const kMaxLen = 40;

	class Word {
	public:
		char word[kMaxLen];

		inline bool operator==(Word const &cur) const {
			size_t i = 0;
			while ((cur.word[i] != '\0') || (word[i] != '\0')) {
				if (cur.word[i] != word[i]) {
					return false;
				}
				++i;
			}
			return true;
		}
	};

public:
	inline Duplicity();
	inline ~Duplicity();

	inline void Proc();

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

inline void Duplicity::Proc() {
	return;
}

int main(int argc, char **argv) {
	Duplicity dup;
	dup.Proc();
	return 0;
}
