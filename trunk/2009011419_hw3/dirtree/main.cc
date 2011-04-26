#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "dict-tree.h"

using namespace std;

class DirTree {
private:
	static int const kMaxLen = 256;  // max len of path names

public:
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

	inline DirTree() {
	}

	inline ~DirTree() {
	}

	inline void Init();

private:
	DictTree<Path> dir;
};

template <>
inline bool RBTree<DirTree::Path>::Compare(DirTree::Path const &t1, DirTree::Path const &t2) {
	return (t1 < t2);
}

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
