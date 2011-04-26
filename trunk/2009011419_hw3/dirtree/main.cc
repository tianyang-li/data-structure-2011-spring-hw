#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>

#include "red-black-tree.h"

using namespace std;

class DirTree {
private:
	static int const kMaxLen = 256;  // max len of path names

	class Dir;

	class Path {
	public:
		char path[kMaxLen];
		Dir *sub;  // sub dir

		inline ~Path() {
		}

		inline Path() : sub(NULL) {
		}

		inline Path(Path const &cur) : sub(cur.sub) {
			for (int i = 0; i != kMaxLen; ++i) {
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
				path[i] = cur.path[i];
			}
		}

		inline Path &operator=(Path const &cur) {
			for (int i = 0; i != kMaxLen; ++i) {
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
				path[i] = cur.path[i];
			}
			sub = cur.sub;
			return *this;
		}

		inline bool operator<(Path const &cur) const {  // *this < cur
			for (int i = 0; i != kMaxLen; ++i) {
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
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
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
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
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
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
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
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
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
				if (path[i] != cur.path[i]) {
					return false;
				}
			}
			return true;
		}

		inline bool operator!=(Path const &cur) const {
			for (int i = 0; i != kMaxLen; ++i) {
				if ((path[i] == '\0') || (cur.path[i] == '\0')) {
					break;
				}
				if (path[i] != cur.path[i]) {
					return true;
				}
			}
			return false;
		}

	private:
	};

	class Dir {
	public:
		inline Dir() {
		}

		inline ~Dir() {
		}

		RBTree<Path> dat;  // contents in dir

		inline void ls() {  // similar to Linux command ls. list dat in dir

		}
	private:
	};

public:
	inline DirTree() {
	}

	inline ~DirTree() {
	}

	inline void Init();
	inline void Proc();

private:
	inline void AddPath(char *path) {

	}
};

inline void DirTree::Proc() {

}

inline void DirTree::Init() {
	int n;
	cin >> n;
	char tmp_path[kMaxLen];
	for (int i = 0; i != n; ++i) {
		scanf("%s", tmp_path);
		AddPath(tmp_path);
	}
}

int main(int argc, char **argv) {
	DirTree dir_tree;
	dir_tree.Init();
	return 0;
}
