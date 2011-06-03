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
};

class Navigator {
	static int const kInfCost = 100000000;
	static int const kMaxFuel = 1000;

	struct CostHandle;
	friend class PrQue<CostHandle>;

	struct Cost {
		int cost;
		int pq_index;  // index in priority queue

		inline bool operator<(Cost const &x) const {
			return (cost < x.cost);
		}
	};

	struct CostHandle {
		Cost *cost_ptr;
		int city;
		int cap;  // capacity

		inline bool operator<(CostHandle const &x) const {
			return (*cost_ptr < *x.cost_ptr);
		}
	};

	struct Road {
		int to;  // index of the city int leads to
		int d;  // distance to that city
	};

	struct City {
		Node<Road> *adj;

		inline City() {
			adj = new (nothrow) Node<Road>;
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
			Node<Road> *tmp = new (nothrow) Node<Road>;
			tmp->data.d = d;
			tmp->data.to = to;
			tmp->next = adj->next;
			adj->next = tmp;
		}
	};

public:
	inline Navigator() {
		int m;
		cin >> n >> m;
		price = new (nothrow) int[n];
		city = new (nothrow) City[n];
		for (int i = 0; i != n; ++i) {
			scanf("%d", &price[i]);
		}
		int c1, c2, d;
		for (int i = 0; i != m; ++i) {
			scanf("%d %d %d", &c1, &c2, &d);
			city[c1].AddRoad(c2, d);
			city[c2].AddRoad(c1, d);
		}
		cost = new (nothrow) Cost *[n];
		for (int i = 0; i != n; ++i) {
			cost[i] = new (nothrow) Cost[kMaxFuel];
		}
		min_que.SetSize(n * kMaxFuel);
	}

	inline ~Navigator() {
		delete [] price;
		delete [] city;
		for (int i = 0; i != n; ++i) {
			delete [] cost[i];
		}
		delete [] cost;
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
	int n;
	int *price;
	City *city;
	Cost **cost;
	PrQue<CostHandle> min_que;

	inline int Query(int const c, int const s, int const t);

	inline void InitCost() {
		for (int i = 0; i != n; ++i) {
			for (int j = 0; j != kMaxFuel; ++j) {
				cost[i][j].cost = kInfCost;
			}
		}
	}

	inline void RelaxEdges(CostHandle const &ch, int const c);
	inline void ReduceCost(int const city, int const cap);
};

template <>
inline void PrQue<Navigator::CostHandle>::PQSwap(Navigator::CostHandle &x, Navigator::CostHandle &y) {
	int tmp = x.cost_ptr->pq_index;
	x.cost_ptr->pq_index = y.cost_ptr->pq_index;
	y.cost_ptr->pq_index = tmp;
	Navigator::Cost *tmp_cost = x.cost_ptr;
	x.cost_ptr = y.cost_ptr;
	y.cost_ptr = tmp_cost;
	tmp = x.city;
	x.city = y.city;
	y.city = tmp;
	tmp = x.cap;
	x.cap = y.cap;
	y.cap = tmp;
}

inline int Navigator::Query(int const c, int const s, int const t) {
	InitCost();
	min_que.size = 0;
	cost[s][0].cost = 0;
	int pq_ind = 0;
	CostHandle ch;
	for (int i = 0; i != n; ++i) {
		for (int j = 0; j != c; ++j) {
			ch.cost_ptr = &cost[i][j];
			ch.cost_ptr->pq_index = pq_ind;
			ch.cap = j;
			ch.city = i;
			min_que.Insert(ch);
			pq_ind++;
		}
	}
	while (0 != min_que.size) {
		ch = min_que.data[0];
		min_que.Pop();
		if (ch.city == t) {
			return (ch.cost_ptr->cost == kInfCost) ? -1 : ch.cost_ptr->cost;
		}
		RelaxEdges(ch, c);
	}
}

inline void Navigator::RelaxEdges(Navigator::CostHandle const &ch, int const c) {
	int cur_cost;
	if (ch.cap < c) {
		cur_cost = cost[ch.city][ch.cap].cost + price[ch.city];
		if (cur_cost < cost[ch.city][ch.cap + 1].cost) {
			cost[ch.city][ch.cap + 1].cost = cur_cost;
			ReduceCost(ch.city, ch.cap + 1);
		}
	}
	Node<Road> *adj = city[ch.city].adj->next;
	int rem;  // remaining fuel
	while (adj) {
		rem = ch.cap - adj->data.d;
		if (rem >= 0) {
			if (cost[ch.city][ch.cap].cost < cost[adj->data.to][rem].cost) {
				cost[adj->data.to][rem].cost = cost[ch.city][ch.cap].cost;
				ReduceCost(adj->data.to, rem);
			}
		}
		adj = adj->next;
	}
}

inline void Navigator::ReduceCost(int const city, int const cap) {
	int cur = cost[city][cap].pq_index;
	while ((cur > 0) && (min_que.data[cur] < min_que.data[((cur + 1) >> 1) - 1])) {
		PrQue<CostHandle>::PQSwap(min_que.data[cur], min_que.data[((cur + 1) >> 1) - 1]);
		cur = ((cur + 1) >> 1) - 1;
	}
}

int main() {
	Navigator nav;
	nav.Proc();
	return 0;
}
