#ifdef HEAP_TEST

#include <iostream>
#include <cstdio>

#include "priority-queue.h"

int main() {
	PrQue<int> test;
	while (true) {
		char a;
		int val;
		scanf("%c", &a);
		switch (a) {
		case 'a':
			scanf("%d", &val);
			break;
		case 'p':
			if (test.size) {
				printf("%d", test.data[0]);
				test.Pop();
			}
			break;
		}
	}
	return 0;
}

#endif
