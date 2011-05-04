#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>

#include "hash1.h"

using namespace std;

class Duplicity {
private:
	static size_t const kMaxLen = 42;

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

		Word() {
		}

		~Word() {
		}

		Word(Word const &cur) {
			size_t i = 0;
			while (cur.word[i] != '\0') {
				word[i] = cur.word[i];
				++i;
			}
			word[i] = '\0';
		}

		Word &operator=(Word const &cur) {
			size_t i = 0;
			while (cur.word[i] != '\0') {
				word[i] = cur.word[i];
				++i;
			}
			word[i] = '\0';
			return *this;
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
	int n;
	cin >> n;
	Word tmp;
	for (int i = 0; i != n; ++i) {
		scanf("%s", tmp.word);
	}
}

inline void Duplicity::Proc() {
	return;
}

int main(int argc, char **argv) {
	Duplicity dup;
	dup.Proc();
	return 0;
}
