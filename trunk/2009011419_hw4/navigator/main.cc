#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <new>

#include "priority-queue.h"

using namespace std;

template <class T>
struct Node {
	Node *next;
	T data;

	inline Node() : next(NULL) {
	}

	inline Node(T const &new_data) : next(NULL), data(new_data) {
	}
};

class Navigator {
	typedef int Cost;

public:
	inline Navigator() {
	}

	inline ~Navigator() {
	}

	inline void Proc() {
		int q;
		cin >> q;
		int c, s, t;
		for (int i = 0; i != 1; ++i) {
			scanf("%d %d %d", &c, &s, &t);
		}
	}

private:
	int n;  // # of cities
	int m;  // # of roads

	inline Cost Query(int const c, int const s, int const t) {
		return -1;
	}
};

int main() {
	Navigator nav;
	nav.Proc();
	return 0;
}
