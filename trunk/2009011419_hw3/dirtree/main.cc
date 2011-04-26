#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "red-black-tree.h"

using namespace std;

class DirTree {
private:
	static int const kMaxLen = 256;  // max len of path names

	class Path {
	public:
		inline ~Path() {
		}

		inline Path(Path const &cur) {
			for (int i = 0; i != kMaxLen; ++i) {
				path[i] = cur.path[i];
			}
		}

		inline Path &operator=(Path const &cur) {
			for (int i = 0; i != kMaxLen; ++i) {
				path[i] = cur.path[i];
			}
			return *this;
		}

		inline bool operator<(Path const &cur) const {  // *this < cur
			for (int i = 0; i != kMaxLen; ++i) {
				if (cur.path[i] > path[i]) {
					return true;
				}
				if (cur.path[i] < path[i]) {
					return false;
				}
			}
			return false;
		}

		inline bool operator<=(Path const &cur) const {  // *this <= cur
			for (int i = 0; i != kMaxLen; ++i) {
				if (cur.path[i] > path[i]) {
					return true;
				}
				if (cur.path[i] < path[i]) {
					return false;
				}
			}
			return true;
		}

		inline bool operator>(Path const &cur) const {  // *this > cur
			for (int i = 0; i != kMaxLen; ++i) {
				if (cur.path[i] < path[i]) {
					return true;
				}
				if (cur.path[i] > path[i]) {
					return false;
				}
			}
			return false;
		}

		inline bool operator>=(Path const &cur) const {  // *this >= cur
			for (int i = 0; i != kMaxLen; ++i) {
				if (cur.path[i] < path[i]) {
					return true;
				}
				if (cur.path[i] > path[i]) {
					return false;
				}
			}
			return true;
		}

		inline bool operator==(Path const &cur) const {
			for (int i = 0; i != kMaxLen; ++i) {
				if (path[i] != cur.path[i]) {
					return false;
				}
			}
		}

		inline bool operator!=(Path const &cur) const {
			for (int i = 0; i != kMaxLen; ++i) {
				if (path[i] != cur.path[i]) {
					return true;
				}
			}
		}

		char path[kMaxLen];

	private:
	};

	class Dir {
	public:
		inline Dir() {
		}

		inline ~Dir() {
		}

		RBTree<Path> dat;  // contents in dir
	private:
	};

public:
	inline DirTree() {
	}

	inline ~DirTree() {
	}

	inline void Init();

private:
};

inline void DirTree::Init() {
	int n;
	cin >> n;
	char tmp_path[kMaxLen];
	for (int i = 0; i != n; ++i) {
		scanf("%s", tmp_path);
	}
}

int main(int argc, char **argv) {
	DirTree dir_tree;
	dir_tree.Init();
	return 0;
}
