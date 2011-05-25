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
		size_t ID;  // program's ID
		Prior pr;
	};

	static size_t const kMaxNameLen = 9;  // max length for program names

public:
	inline Scheduler();
	inline ~Scheduler();

	inline void Proc() {
		for (size_t i = 0; (i != m) && (0 != task_queue.size); ++i) {
			Task tmp0 = task_queue.data[0];
			printf("%s\n", task[tmp0.ID]);
			task_queue.Pop();
			if (!QuitSched(tmp0.pr)) {
				task_queue.Insert(tmp0);
			}
		}
	}

private:
	size_t n, m;
	PrQue<Task> task_queue;
	char **task;

	inline bool QuitSched(Prior &pr) {
		// determine if pr should quit scheduling or continue, pr is modified
		// true if should quit, else false
		if (0 != (0x8000000 & pr)) {
			return true;
		}
		pr = pr << 1;
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
		scanf("%d %s", &tmp0.pr, task[i]);
		tmp0.ID = i;

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
	return 0;
}
