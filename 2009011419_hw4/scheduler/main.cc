#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdint.h>
#include <cstddef>

#include "priority-queue.h"

using namespace std;

class Scheduler {
private:
	typedef uint32_t Prior;

	struct Task {
		char *ID;  // program's ID
		Prior pr;

		inline Task(Task const &x) : ID(x.ID), pr(x.pr) {
		}

		inline Task() {
		}

		inline ~Task() {
		}

		inline Task &operator=(Task const &x) {
			if (this != &x) {
				ID = x.ID;
				pr = x.pr;
			}
			return *this;
		}

		inline bool operator<(Task const &x) {
			if (pr < x.pr) {
				return true;
			}
			if (pr > x.pr) {
				return false;
			}
			size_t i = 0;
			while ((x.ID[i] != '\0') && (ID[i] != '\0')) {
				if (ID[i] < x.ID[i]) {
					return true;
				}
				if (ID[i] > x.ID[i]) {
					return false;
				}
				++i;
			}
			if (x.ID[i] > ID[i]) {
				return true;
			}
			return false;
		}
	};

	static size_t const kMaxNameLen = 9;  // max length for program names

public:
	inline Scheduler();
	inline ~Scheduler();

	inline void Proc() {
		for (size_t i = 0; (i != m) && (0 != task_queue.size); ++i) {
			Task tmp0 = task_queue.data[0];
			printf("%u#%s\n", tmp0.pr, tmp0.ID);
			task_queue.Pop();
			if (!QuitSched(tmp0)) {
				task_queue.Insert(tmp0);
			}
		}
	}

private:
	size_t n, m;
	PrQue<Task> task_queue;
	char **task;

	inline bool QuitSched(Task &p) {
		// determine if pr should quit scheduling or continue, pr is modified
		// true if should quit, else false
		if (0 != (0x80000000 & p.pr)) {
			return true;
		}
		p.pr = p.pr << 1;
		return false;
	}
};

inline Scheduler::Scheduler() {
	cin >> n >> m;
	task_queue.SetSize(n);
	task = new (nothrow) char *[n];
	Task tmp0;
	for (size_t i = 0; i != n; ++i) {
		task[i] = new (nothrow) char[kMaxNameLen];
		scanf("%u %s", &tmp0.pr, task[i]);
		tmp0.ID = task[i];
		task_queue.Insert(tmp0);
	}
}

inline Scheduler::~Scheduler() {
	for (size_t i = 0; i != n; ++i) {
		delete [] task[i];
	}
	delete [] task;
}

int main() {
	Scheduler sched;
	sched.Proc();
	return 0;
}
