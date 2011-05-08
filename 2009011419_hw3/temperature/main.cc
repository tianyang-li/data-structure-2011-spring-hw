#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>

#include "range-tree.h"

using namespace std;

class Temp {
private:
	struct Info {
		size_t n;  // # of stations
		float temp; // temperature

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

	inline float Query(Point const &LL, Point const &UR) const;
	inline void PreProc(RangeTree<int, Info>::XNodePtr const root);
	inline void ProcY(RangeTree<int, Info>::YNodePtr const root);
	inline RangeTree<int, Info>::XNodePtr XFindSplit(int const x1, int const x2, RangeTree<int, Info>::XNodePtr const root) const;
	inline float Average(int const x1, int const x2, int const y1, int const y2, RangeTree<int, Info>::XNodePtr split) const;
};

inline float Temp::Average(int const x1, int const x2, int const y1, int const y2, RangeTree<int, Info>::XNodePtr split) const {
	Info info;
	return info.temp;
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
		size_t n = root->point->data.n + root->rc->point->data.n;
		root->point->data.temp = (float(root->point->data.n) * root->point->data.temp + float(root->rc->point->data.n) * root->rc->point->data.temp)
				/ (float(n));
		root->point->data.n = n;
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

inline float Temp::Query(Point const &LL, Point const &UR) const {
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
		scanf("%d %d %f", &(stat.points[i].coord.x), &(stat.points[i].coord.y), &(stat.points[i].data.temp));
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
		printf("%.2f\n", Query(LL, UR));
	}
}

int main(int argc,char **argv) {
	Temp temp;
	temp.Init();
	temp.Proc();
	return 0;
}
