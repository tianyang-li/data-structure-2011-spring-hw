#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <new>
#include <stdint.h>

#include "hash1.h"

using namespace std;

class Duplicity {
private:
	static size_t const kMaxLen = 42;

	class Word {
	public:
		char word[kMaxLen];
		bool printed;  // true if already printed

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

		inline Word() : printed(false) {
		}

		inline ~Word() {
		}

		inline Word(Word const &cur) : printed(false) {
			size_t i = 0;
			while (cur.word[i] != '\0') {
				word[i] = cur.word[i];
				++i;
			}
			word[i] = '\0';
		}

		inline Word &operator=(Word const &cur) {
			size_t i = 0;
			while (cur.word[i] != '\0') {
				word[i] = cur.word[i];
				++i;
			}
			word[i] = '\0';
			return *this;
		}
	};

	class HT {  // hash table
	public:
		static size_t const kTabSize = 0x10002u;
		static uint32_t const kShiftRight = 16u;  // right shift needed when using hash table

		class Entry {
		public:
			inline Entry(Word const &new_word) : next(NULL), word(new_word) {
			}
			inline Entry() : next(NULL) {
			}

			Entry *next;
			Word word;
		};
		typedef Entry *EntryPtr;

		inline HT() {
			tab = new (nothrow) EntryPtr[kTabSize];  // XXX: need one more storage??
			for (size_t i = 0; i != kTabSize; ++i) {
				tab[i] = new (nothrow) Entry;
			}
		}
		inline ~HT() {
			HT::EntryPtr tmp1, tmp2;
			for (size_t i = 0; i != kTabSize; ++i) {
				tmp1 = tab[i];
				while (NULL != tmp1) {
					tmp2 = tmp1->next;
					delete tmp1;
					tmp1 = tmp2;
				}
			}
			delete [] tab;
		}

		EntryPtr *tab;

	private:
	};

public:
	inline Duplicity();
	inline ~Duplicity();

	inline void Proc();

private:
	HT ht;  // hash table

	inline void ProcEntry(Word const &word);  // return true if word needs to be printed
};

inline void Duplicity::ProcEntry(Word const &word) {
	uint32_t hash = Hash1(word.word);
	hash >>= HT::kShiftRight;
	HT::EntryPtr tmp1 = ht.tab[hash]->next, tmp2 = ht.tab[hash];
	while ((tmp1 != NULL) && (!(tmp1->word == word))) {
		tmp2 = tmp1;
		tmp1 = tmp1->next;
	}
	if (NULL != tmp1) {
		if (tmp1->word.printed) {
			return;
		}
		tmp1->word.printed = true;
		printf("%s\n", word.word);
		return;
	}
	tmp2->next = new (nothrow) HT::Entry(word);
}

inline Duplicity::Duplicity() {
}

inline Duplicity::~Duplicity() {
}

inline void Duplicity::Proc() {
	int n;
	cin >> n;
	Word tmp;
	for (int i = 0; i != n; ++i) {
		scanf("%s", tmp.word);
		ProcEntry(tmp);
	}
}

int main(int argc, char **argv) {
	Duplicity dup;
	dup.Proc();
	return 0;
}
