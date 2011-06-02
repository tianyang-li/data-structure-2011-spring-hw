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
};

class Navigator {
	struct Road {
		int to;  // index of the city int leads to
		int d;  // distance to that city
	};
	struct City {
		Node<Road> *adj;

		inline City() {
			adj = new (nothrow) Node<City>;
		}

		inline ~City() {
			Node<Road> *tmp1 = adj, *tmp2;
			while (tmp1) {
				tmp2 = tmp1;
				tmp1 = tmp1->next;
				delete tmp2;
			}
		}

		inline void AddRoad(int const to, int const d) {
			Node<Road> *tmp = new (nothrow) Road;
			tmp->data.d = d;
			tmp->data.to = to;
		}
	};

public:
	inline Navigator() {
		int n, m;
		cin >> n >> m;
		price = new (nothrow) int[n];
		for (int i = 0; i != n; ++i) {
			scanf("%d", &price[i]);
		}
		int c1, c2, d;
	}

	inline ~Navigator() {
		delete [] price;
	}

	inline void Proc() {
	}

private:
	int *price;
};

int main() {
	Navigator nav;
	nav.Proc();
	return 0;
}
