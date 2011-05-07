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
	typedef RangeTree<int, Info>::Coord::Tuple Point;

public:
	inline Temp();
	inline ~Temp();
	inline void Init();
	inline void Proc();

private:
	RangeTree<int, Info> stat;  // stationss
	size_t m;

	inline float Query(Point const &LL, Point const &UR) const;
	inline void PreProc(RangeTree<int, Info>::CoordPtr const cur);
};

inline void Temp::PreProc(RangeTree<int, Info>::CoordPtr const cur) {
	if (NULL != cur->lc) {
		PreProc(cur->lc);
		cur->data.n = cur->lc->data.n;
		cur->data.temp = cur->lc->data.temp;
	}
	if (NULL != cur->rc) {
		PreProc(cur->rc);
		size_t tmp = cur->data.n + cur->rc->data.n;
		cur->data.temp = (float(cur->rc->data.n) * cur->rc->data.temp + float(cur->data.n) * cur->data.temp)
				/ (float(tmp));
		cur->data.n = tmp;
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
		scanf("%d %d %f", &(stat.points[i].tuple.x), &(stat.points[i].tuple.y), &(stat.points[i].data.temp));
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
