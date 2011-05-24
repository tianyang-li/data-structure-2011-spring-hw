#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdint.h>

#include "priority-queue.h"

using namespace std;

class Scheduler {
	typedef uint32_t Prior;

public:
	inline Scheduler();
	inline ~Scheduler();

private:
	uint32_t n, m;
	PrQue<Prior> task;
};

inline Scheduler::Scheduler() {
	cin >> n >> m;
}

inline Scheduler::~Scheduler() {
}

int main() {
	Scheduler sched;
	return 0;
}
