#ifdef TRIE

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <new>

using namespace std;

class DirTree {
private:
	static int const kMaxCh = 65;
	static int const kMaxLen = 256;

	class Dir {
	public:
		class Trie {
		public:
			class Node {
			public:
				Dir *subdir;
				typedef Node *NodePtr;
				NodePtr ch[kMaxCh];
				char chr;  // char stored at this node

				inline Node(int const new_ch) : chr(new_ch), subdir(NULL) {
					for (int i = 0; i != kMaxCh; ++i) {
						ch[i] = NULL;
					}
				}

				inline ~Node() {
					for (int i = 0; i != kMaxCh; ++i) {
						if (!ch[i]) {
							delete ch[i];
						}
						if (!subdir) {
							delete subdir;
						}
					}
				}
			};
			Node *root;

			static char const char_set[];
			static int const char_map[];

			inline Trie() {
				root = new (nothrow) Node(-1);
			}
			inline ~Trie() {
				delete root;
			}

			Dir *AddStr(char const *str, Node::NodePtr const cur, Node::NodePtr const from = NULL) {
				if ('\0' != *str) {
					if (!cur->ch[char_map[*str]]) {
						cur->ch[char_map[*str]] = new (nothrow) Node(*str);
					}
					++str;
					return AddStr(str, cur->ch[char_map[*(str - 1)]], cur);
				}
				else {
					--str;
					if (!from->ch[char_map[*str]]->subdir) {
						from->ch[char_map[*str]]->subdir = new (nothrow) Dir;
					}
					return from->ch[char_map[*str]]->subdir;
				}
			}

		};

		Trie dir;

		inline Dir() {
		}

		inline ~Dir() {
		}

	private:

	};

public:
	Dir *root;

	inline DirTree() : indent(-1) {
		root = new (nothrow) Dir;
		int j;
		for (int i = 0; i != (kMaxLen >> 1); ++i) {
			j = 0;
			while (j != i) {
				space[i][j << 1] = ' ';
				space[i][(j << 1) + 1] = ' ';
				++j;
			}
			space[i][j << 1] = '\0';
		}
	}

	inline ~DirTree() {
		delete root;
	}

	inline void Init() {
		int n;
		cin >> n;
		char inp[kMaxLen];
		char dir[kMaxLen];
		Dir *cur;
		int a, b;
		for (int i = 0; i != n; ++i) {
			scanf("%s", inp);
			a = 0, b = 0;
			cur = root;
			while ('\0' != inp[a]) {
				if ('/' == inp[a]) {
					dir[b] = '\0';
					b = 0;
					cur = cur->dir.AddStr(dir, cur->dir.root);
				}
				else {
					dir[b] = inp[a];
					b++;
				}
				++a;
			}
			dir[b] = '\0';
			cur = cur->dir.AddStr(dir, cur->dir.root);
		}
	}

	inline void Proc(Dir *const cur) {
		++indent;
		--indent;
	}

private:
	char space[kMaxLen >> 1][kMaxLen];
	int indent;
};

char const DirTree::Dir::Trie::char_set[] = {'-', '.'
		,'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
		, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N'
		, 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
		,'_'
		, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'
		, 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int const DirTree::Dir::Trie::char_map[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		, 1, 1, 1, 1, 1, 0, 1, 1, 2, 3
		, 4, 5, 6, 7, 8, 9, 10, 11, 1, 1
		, 1, 1, 1, 1, 1, 12, 13, 14, 15, 16
		, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26
		, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36
		, 37, 1, 1, 1, 1, 38, 1, 39, 40, 41
		, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
		, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61
		, 62, 63, 64, 1, 1, 1, 1, 1};

int main() {
	DirTree dir;
	dir.Init();
	dir.Proc(dir.root);
	return 0;
}

#endif
