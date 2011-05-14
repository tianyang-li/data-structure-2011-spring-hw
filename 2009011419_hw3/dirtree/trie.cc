#ifdef TRIE

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <new>

class DirTree {
private:
	class Dir {
	public:
		class Trie {
		public:
			static const char char_set[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
					, 'a', 'b', 'c', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'
					, 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
					,};
			Dir *subdir;

			inline Trie() : subdir(NULL) {
			}
			inline ~Trie() {
				delete subdir;
			}

		private:

		};

		Trie dir;

		inline Dir() {
		}

		inline ~Dir() {
		}

	private:

	};

public:
	inline DirTree() : root(NULL) {
	}

	inline ~DirTree() {
		delete root;
	}

	inline void Init() {
	}

	inline void Proc() {
	}

private:
	Dir *root;
};

int main() {
	DirTree dir;
	dir.Init();
	dir.Proc();
	return 0;
}

#endif
