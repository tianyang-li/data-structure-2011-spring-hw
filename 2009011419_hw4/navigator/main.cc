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
	class CityHandle;
	friend class PrQue<CityHandle>;

	typedef int Dist;

	struct Road {
		Dist d;
		int to;  // index of the city it goes to
	};

	typedef int Cost;

	static Cost const kInfCost = 10000000;

	struct City {
		Cost cost;
		int cap_rem;  // remaining capacity
		int prev_price;
		int gas_price;
		Node<Road> *road;
		int index;  // index of CityHandle

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
		}

		inline void AddRoad(int const to, Dist const d) {
			Node<Road> *tmp = new (nothrow) Node<Road>;
			tmp->data.d = d;
			tmp->data.to = to;
			tmp->next = road->next;
			road->next = tmp;
		}
	};

	struct CityHandle {
		City *city;
		int index;

		inline CityHandle() {
		}

		inline ~CityHandle() {
		}

		inline CityHandle &operator=(CityHandle const &x) {
			if (this != &x) {
				city = x.city;
			}
			return *this;
		}

		inline CityHandle(CityHandle const &x) : city(x.city) {
		}

		inline bool operator<(CityHandle const &x) const {
			return (*city < *x.city);
		}
	};

public:
	inline Navigator() {
		int m;
		cin >> n >> m;
		min_que.SetSize(n);
		cities = new (nothrow) City[n];
		for (int i = 0; i != n; ++i) {
			scanf("%d", &cities[i].gas_price);
			min_que.data[i].index = i;
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
	PrQue<CityHandle> min_que;

	inline Cost Query(int const c, int const s, int const t) {
		for (int i = 0; i != n; ++i) {
			cities[i].InitCost();
		}
		cities[s].cost = 0;
		cities[s].cap_rem = 0;
		cities[s].prev_price = kInfCost;
		CityHandle ct_hdl;
		for (int i = 0; i != n; ++i) {
			ct_hdl.city = &cities[i];
			min_que.Insert(ct_hdl);
		}
		while (0 != min_que.size) {
			ct_hdl = min_que.data[0];
			min_que.Pop();
			Node<Road> *adj = ct_hdl.city->road->next;
			Cost new_cost;
			while (adj) {
				if (c >= adj->data.d) {
					new_cost = ct_hdl.city->cost;
					if ((0 != ct_hdl.city->cap_rem) && (ct_hdl.city->gas_price > ct_hdl.city->prev_price)) {
						if (ct_hdl.city->cap_rem >= adj->data.d) {
							new_cost += (adj->data.d * ct_hdl.city->prev_price);
							if (new_cost < cities[adj->data.to].cost) {
								cities[adj->data.to].cap_rem = ct_hdl.city->cap_rem - adj->data.d;
								cities[adj->data.to].prev_price = ct_hdl.city->prev_price;
								cities[adj->data.to].cost = new_cost;
							}
						}
						else {
							new_cost += ((adj->data.d - ct_hdl.city->cap_rem) * ct_hdl.city->gas_price
									+ ct_hdl.city->cap_rem * ct_hdl.city->prev_price);
							if (new_cost < cities[adj->data.to].cost) {
								cities[adj->data.to].cap_rem = c - (adj->data.d - ct_hdl.city->cap_rem);
								cities[adj->data.to].prev_price = ct_hdl.city->gas_price;
								cities[adj->data.to].cost = new_cost;
							}
						}
					}
					else {
						new_cost += (adj->data.d * ct_hdl.city->gas_price);
						if (new_cost < cities[adj->data.to].cost) {
							cities[adj->data.to].prev_price = ct_hdl.city->gas_price;
							cities[adj->data.to].cap_rem = c - adj->data.d;
							cities[adj->data.to].cost = new_cost;
						}
					}
				}
				adj = adj->next;
			}
		}
		return ((kInfCost == cities[t].cost) ? -1 : cities[t].cost);
	}

	inline void DecCost(int const cur) {  // adjust heap after decreasing cities[cur].cost
	}
};

template <>
void PrQue<Navigator::CityHandle>::PQSwap(Navigator::CityHandle &x, Navigator::CityHandle &y) {
	Navigator::City *tmp = x.city;
	x.city = y.city;
	y.city = tmp;
	x.city->index = x.index;
	y.city->index = y.index;
}

int main() {
	Navigator nav;
	nav.Proc();
	return 0;
}
