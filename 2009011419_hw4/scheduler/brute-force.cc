#ifdef BRUTE_FORCE

#include <cstdio>
#include <iostream>
#include <stdint.h>
#include <new>
#include <cstddef>

using namespace std;

template <class T>
struct Node {
	Node *next;
	T data;

	inline Node() : next(NULL) {
	}
};

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
		Task tmp0;
		for (size_t i = 0; (i != m) && sched->next; ++i) {
			tmp0 = GetMin();
			printf("%s\n", tmp0.ID);
			if (!QuitSched(tmp0)) {
				PutIn(tmp0);
			}
		}
	}

private:
	size_t n, m;
	char **task;
	Node<Task> *sched;

	inline bool QuitSched(Task &p) {
		// determine if pr should quit scheduling or continue, pr is modified
		// true if should quit, else false
		if (0 != (0x80000000 & p.pr)) {
			return true;
		}
		p.pr = p.pr << 1;
		return false;
	}

	inline Task GetMin() {
		Task tmp = sched->next->data;
		Node<Task> *tmp0 = sched->next;
		sched->next = sched->next->next;
		delete tmp0;
		return tmp;
	}

	inline void PutIn(Task const &t) {
		Node<Task> *tmp = new (nothrow) Node<Task>;
		Node<Task> *tmp1 = sched;
		Node<Task> *tmp2 = sched->next;
		while (tmp2 && (tmp2->data < t)) {
			tmp1 = tmp2;
			tmp2 = tmp2->next;
		}
		tmp1->next = tmp;
		tmp->next = tmp2;
		tmp->data = t;
	}
};

inline Scheduler::Scheduler() {
	sched = new (nothrow) Node<Task>;
	cin >> n >> m;
	task = new (nothrow) char *[n];
	Task tmp0;
	for (size_t i = 0; i != n; ++i) {
		task[i] = new (nothrow) char[kMaxNameLen];
		scanf("%u %s", &tmp0.pr, task[i]);
		tmp0.ID = task[i];
		PutIn(tmp0);
	}
}

inline Scheduler::~Scheduler() {
	for (size_t i = 0; i != n; ++i) {
		delete [] task[i];
	}
	delete [] task;
	Node<Task> *tmp1 = sched;
	while (tmp1) {
		Node<Task> *tmp2 = tmp1;
		tmp1 = tmp1->next;
		delete tmp2;
	}
}

int main() {
	Scheduler sched;
	sched.Proc();
	return 0;
}

#endif
