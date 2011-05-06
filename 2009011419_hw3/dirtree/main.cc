#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <new>

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
	inline DirTree() : indent(0) {
	}

	inline ~DirTree() {
		delete root;
	}

	inline void Init();
	inline void Proc(Dir *dir);

private:
	Dir *root;
	int indent;  // # of spaces that need to be printed

	inline void AddPath(char const *path);
	inline Dir *AddEntry(Path const &path, Dir &cur_dir);
	inline void PrintSpace() {
		for (int i = 0; i != indent; ++i) {
			putchar(' ');
		}
	}
};

template <>
inline RBTree<DirTree::Path>::Node::~Node() {
	delete data.sub;
}

inline void DirTree::AddPath(char const *path) {
	Path tmp;
	int j = 0;
	Dir *dir = root;
	for (int i = 0; path[i] != '\0'; ++i) {
		if ((path[i] != '/') || (path[i] != '\0')) {
			tmp.path[j] = path[i];
			++j;
		}
		else {
			tmp.path[j] = '\0';
			j = 0;
			dir = AddEntry(tmp, *dir);
		}
	}
}

inline DirTree::Dir *DirTree::AddEntry(Path const &path, Dir &cur_dir) {
	RBTree<Path>::NodePtr rbt_node = cur_dir.dat.Insert(path);
	rbt_node->data.sub = new (nothrow) Dir;
	return rbt_node->data.sub;
}

inline void DirTree::Proc(Dir *dir) {
	indent += 2;
	indent -= 2;
}

inline void DirTree::Init() {
	root = new (nothrow) Dir;
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
