#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <new>

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
	typedef int Dist;

	struct Road {
		Dist d;
		int to;  // index of the city it goes to
	};

	typedef int Cost;

	static Cost const kInfCost = 10000000;

	struct City {
		Cost cost;
		int gas_price;
		Node<Road> *road;
		bool visited;

		inline City() {
			road = new (nothrow) Node<Road>;
		}

		inline ~City() {
			Node<Road> *tmp1 = road, *tmp2;
			while (tmp1) {
				tmp2 = tmp1;
				tmp1 = tmp1->next;
				delete tmp2;
			}
		}

		inline bool operator<(City const &x) const {
			return (cost < x.cost);
		}

		inline void InitCost() {
			cost = kInfCost;
			visited = false;
		}

		inline void AddRoad(int const to, Dist const d) {
			Node<Road> *tmp = new (nothrow) Node<Road>;
			tmp->data.d = d;
			tmp->data.to = to;
			tmp->next = road->next;
			road->next = tmp;
		}
	};

public:
	inline Navigator() {
		int m;
		cin >> n >> m;
		cities = new (nothrow) City[n];
		for (int i = 0; i != n; ++i) {
			scanf("%d", &cities[i].gas_price);
		}
		int c1, c2, d;
		for (int i = 0; i != m; ++i) {
			scanf("%d %d %d", &c1, &c2, &d);
			cities[c1].AddRoad(c2, d);
			cities[c2].AddRoad(c1, d);
		}
	}

	inline ~Navigator() {
		delete [] cities;
	}

	inline void Proc() {
		int q;
		cin >> q;
		int c, s, t;
		for (int i = 0; i != q; ++i) {
			scanf("%d %d %d", &c, &s, &t);
			printf("%d\n", Query(c, s, t));
		}
	}

private:
	int n;  // # of cities
	City *cities;

	inline Cost Query(int const c, int const s, int const t) {
		for (int i = 0; i != n; ++i) {
			cities[i].InitCost();
		}
		cities[s].cost = 0;
		DFS(c, s, t, 0, s);
		return ((kInfCost == cities[t].cost) ? -1 : cities[t].cost);
	}

	inline void DFS(int const c, int const s, int const t
			, int const d /* distance from s to the nearest and cheapest city */
			, int const pc /* corresponding previous city of d */) {
		if (s == t) {
			return;
		}
		if (cities[s].visited) {
			return;
		}
		cities[s].visited = true;
		Node<Road> *adj = cities[s].road->next;
		int cur_cost;
		while (adj) {
			cur_cost = cities[s].cost;
			if ((!cities[adj->data.to].visited) && (c >= adj->data.d)) {
				if (cities[pc].gas_price >= cities[s].gas_price) {
					cur_cost += (cities[s].gas_price * adj->data.d);
					if (cur_cost < cities[t].cost) {
						cities[adj->data.to].cost = cur_cost;
						DFS(c, adj->data.to, t, adj->data.d, s);
					}
				}
				else {
					if (c > (adj->data.d + d)) {
						cur_cost += (cities[pc].gas_price * adj->data.d);
						if (cur_cost < cities[t].cost) {
							cities[adj->data.to].cost = cur_cost;
							DFS(c, adj->data.to, t, adj->data.d + d, pc);
						}
					}
					else {
						cur_cost += (cities[pc].gas_price * (c - d)
								+ cities[s].gas_price * (adj->data.d + d - c));
						if (cur_cost < cities[t].cost) {
							cities[adj->data.to].cost = cur_cost;
							DFS(c, adj->data.to, t, adj->data.d, s);
						}
					}
				}
			}
			adj = adj->next;
		}
		cities[s].visited = false;
	}
};

int main() {
	Navigator nav;
	nav.Proc();
	return 0;
}
