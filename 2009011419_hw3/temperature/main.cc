#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <stdint.h>

#include "range-tree.h"

using namespace std;

class Temp {
private:
	struct Info {
		size_t n;  // # of stations
		int64_t temp; // temperature

		inline int Average() {
			if (0 == n) {
				return 0;
			}
			return int((temp/int64_t(n)));
		}

		inline Info() : n(0), temp(0) {
		}
	};
	typedef RangeTree<int, Info>::Tuple Point;

public:
	inline Temp();
	inline ~Temp();
	inline void Init();
	inline void Proc();

private:
	RangeTree<int, Info> stat;  // stationss
	size_t m;

	inline int Query(Point const &LL, Point const &UR) const;
	inline void PreProc(RangeTree<int, Info>::XNodePtr const root);
	inline void ProcY(RangeTree<int, Info>::YNodePtr const root);
	inline RangeTree<int, Info>::XNodePtr XFindSplit(int const x1, int const x2, RangeTree<int, Info>::XNodePtr const root) const;
	inline int Average(int const x1, int const x2, int const y1, int const y2, RangeTree<int, Info>::XNodePtr const split) const;
	inline Info YRangeInfo(int const x1, int const x2, int const y1, int const y2, RangeTree<int, Info>::XNodePtr const split) const;
	inline RangeTree<int, Info>::YNodePtr YFindSplit(int const y1, int const y2, RangeTree<int, Info>::YNodePtr const root) const;
};

inline RangeTree<int, Temp::Info>::YNodePtr Temp::YFindSplit(int const y1, int const y2, RangeTree<int, Info>::YNodePtr const root) const {
	RangeTree<int, Info>::YNodePtr node = root;
	while (node && ((y2 < node->point->coord.y) || (y1 >= node->point->coord.y)) && (node->lc || node->rc)) {
		if (y2 < node->point->coord.x) {
			node = node->lc;
		}
		else {
			node = node->rc;
		}
	}
	return node;
}

inline Temp::Info Temp::YRangeInfo(int const x1, int const x2, int const y1, int const y2, RangeTree<int, Info>::XNodePtr const split) const {
	RangeTree<int, Info>::YNodePtr node = YFindSplit(y1, y2, split->root);
	Info info;
	if (!node) {
		return info;
	}
	if (!node->lc && !node->rc) {
		return node->point->data;
	}
	RangeTree<int, Info>::YNodePtr node1 = node->lc;
	while (node1 && (node1->lc || node1->rc)) {
		if (y1 <= node1->point->coord.y) {
			if (node1->rc) {
				info.n += node1->rc->point->data.n;
				info.temp += node1->rc->point->data.temp;
				node1 = node1->lc;
			}
			else {
				node1 = node1->rc;
			}
		}
	}
	return info;
}

inline int Temp::Average(int const x1, int const x2, int const y1, int const y2, RangeTree<int, Info>::XNodePtr const split) const {
	Info info;
	if (!split->lc && !split->rc) {
		info = YRangeInfo(x1, x2, y1, y2, split);
		return info.Average();
	}
	return info.Average();
}

inline RangeTree<int, Temp::Info>::XNodePtr Temp::XFindSplit(int const x1, int const x2, RangeTree<int, Info>::XNodePtr const root) const {
	RangeTree<int, Info>::XNodePtr node = root;
	while (node && ((x2 < node->coord.x) || (x1 >= node->coord.x)) && (node->lc || node->rc)) {
		if (x2 < node->coord.x) {
			node = node->lc;
		}
		else {
			node = node->rc;
		}
	}
	return node;
}

inline void Temp::ProcY(RangeTree<int, Info>::YNodePtr const root) {
	if (root->lc) {
		ProcY(root->lc);
		root->point->data.n = root->lc->point->data.n;
		root->point->data.temp = root->lc->point->data.temp;
	}
	if (root->rc) {
		ProcY(root->rc);
		root->point->data.n = root->point->data.n + root->rc->point->data.n;
		root->point->data.temp = root->point->data.temp + root->rc->point->data.temp;
	}
}

inline void Temp::PreProc(RangeTree<int, Info>::XNodePtr const root) {
	ProcY(root->root);
	if (root->lc) {
		PreProc(root->lc);
	}
	if (root->rc) {
		PreProc(root->rc);
	}
}

inline int Temp::Query(Point const &LL, Point const &UR) const {
	// query range (x1, x2) X (y1, y2) is now
	// ((x1|-inf),(x2|+inf)) X ((y1|-inf), ((y2|+inf)))
	RangeTree<int, Info>::XNode *node = XFindSplit(LL.x, UR.x, stat.root);
	if (!node) {
		return 0;
	}
	return Average(LL.x, UR.x, LL.y, UR.y, node);
}

inline Temp::~Temp() {
}

inline void Temp::Init() {
	size_t n;
	scanf("%d %d", &n, &m);
	stat.SetSize(n);
	for (size_t i = 0; i != n; ++i) {
		scanf("%d %d %lld", &(stat.points[i].coord.x), &(stat.points[i].coord.y), &(stat.points[i].data.temp));
		stat.points[i].data.n = 1;
	}
	stat.BuildTree();
	PreProc(stat.root);
}

inline Temp::Temp() {
}

inline void Temp::Proc() {
	Point LL;  // lower left corner
	Point UR;  // upper right corner
	for (size_t i = 0; i != m; ++i) {
		scanf("%d %d %d %d", &(LL.x), &(LL.y), &(UR.x), &(UR.y));  // inclusive (for stations)
		printf("%d\n", Query(LL, UR));
	}
}

int main(int argc,char **argv) {
	Temp temp;
	temp.Init();
	temp.Proc();
	return 0;
}
