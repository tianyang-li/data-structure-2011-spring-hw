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
};

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
