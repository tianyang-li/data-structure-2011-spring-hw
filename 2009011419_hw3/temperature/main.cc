#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>

#include "range-tree.h"

using namespace std;

class Temp {
private:
	struct Point {
		int x, y;
	};

public:
	inline Temp();
	inline ~Temp();
	inline void Init();
	inline void Proc();

private:
	RangeTree<int, float> stat;  // stationss
	size_t m;

	inline float Query(Point const &LL, Point const &UR) const;
};

inline float Temp::Query(Point const &LL, Point const &UR) const {
}

inline Temp::~Temp() {
}

inline void Temp::Init() {
	size_t n;
	scanf("%d %d", &n, &m);
	stat.SetSize(n);
	for (size_t i = 0; i != n; ++i) {
		scanf("%d %d %f", &(stat.points[i].x), &(stat.points[i].y), &(stat.points[i].data));
	}
	stat.BuildTree();
}

inline Temp::Temp() {
}

inline void Temp::Proc() {
	Point LL;  // lower left corner
	Point UR;  // upper right corner
	for (size_t i = 0; i != m; ++i) {
		scanf("%d %d %d %d", &(LL.x), &(LL.y), &(UR.x), &(UR.y));  // inclusive (for stations)
		printf("%.2f", Query(LL, UR));
	}
}

int main(int argc,char **argv) {
	Temp temp;
	temp.Init();
	temp.Proc();
	return 0;
}
