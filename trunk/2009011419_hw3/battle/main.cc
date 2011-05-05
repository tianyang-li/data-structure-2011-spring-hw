#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <new>

#include "djset.h"

using namespace std;

class Battle {
public:
	inline Battle() {
		Init();
	}

	inline ~Battle() {
		delete [] ship;
	}

	inline void Proc();
	inline char Query(int s1, int s2);
	inline void Merge(int s1, int s2);

private:
	typedef DJSet<int> Ship;
	typedef DJSet<int> *ShipPtr;
	int n;  // # of ships
	int m;  // # of commands
	ShipPtr ship;

	inline void Init() {
		cin >> n >> m;
		ship = new (nothrow) Ship[n];
	}
};

inline char Battle::Query(int s1, int s2) {
	return 'Y';
}

inline void Battle::Merge(int s1, int s2) {
	Ship::Union(ship[s1], ship[s2]);
}

inline void Battle::Proc() {
	char op;  // current operation
	int s1, s2;  // ships
	for (int i = 0; i != m; ++i) {
		scanf("%c %d %d", &op, &s1, &s2);
		switch (op) {
		case 'Q':
			printf("%c\n", Query(s1, s2));
			break;
		case 'M':
			Merge(s1, s2);
		}
	}
}

int main(int argc, char **argv) {
	Battle battle;
	battle.Proc();
	return 0;
}
