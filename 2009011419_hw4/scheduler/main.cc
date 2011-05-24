#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <new>

using namespace std;

class Scheduler {
public:
	inline Scheduler();
	inline ~Scheduler();

private:
	int n, m;
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
