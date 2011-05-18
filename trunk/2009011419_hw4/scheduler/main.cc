#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

using namespace std;

class Scheduler {
public:
	inline Scheduler();
	inline ~Scheduler();

private:
	uint64_t n, m;
};

inline Scheduler::Scheduler() {
	cin >> n, m;
}

inline Scheduler::~Scheduler() {
}

int main() {
	Scheduler sched;
	return 0;
}
