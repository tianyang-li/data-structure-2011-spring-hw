#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "dict-tree.h"

using namespace std;

class DirTree {
private:
	static int const kMaxLen = 256;  // max len of path names

public:
	typedef char Path[kMaxLen];

	inline DirTree() {
	}

	inline ~DirTree() {
	}

	inline void Init();

private:
	DictTree<Path> dir;
};

inline void DirTree::Init() {
	int n;
	cin >> n;
	Path tmp_path;
	for (int i = 0; i != n; ++i) {
		scanf("%s", tmp_path);
	}
}

int main(int argc, char **argv) {
	DirTree dir_tree;
	dir_tree.Init();
	return 0;
}
