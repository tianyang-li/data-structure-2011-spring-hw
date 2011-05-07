#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>

#include "range-tree.h"

using namespace std;

class Temp {
public:
	inline Temp();
	inline ~Temp();

private:
	RangeTree<int> stat;  // stationss
	size_t m;
};

inline Temp::Temp() {
	size_t n;
	scanf("%d %d", &n, &m);
	stat.SetSize(n);
}

int main(int argc,char **argv) {
	return 0;
}
