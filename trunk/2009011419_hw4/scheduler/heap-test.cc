#ifdef HEAP_TEST

#include <iostream>
#include <cstdio>

#include "priority-queue.h"

int main() {
	PrQue<int> test;
	test.SetSize(0x1000);
	while (true) {
		char a;
		int val;
		scanf("%c", &a);
		switch (a) {
		case 'a':
			scanf("%d", &val);
			test.Insert(val);
			break;
		case 'p':
			if (test.size) {
				printf("%d\n", test.data[0]);
				test.Pop();
			}
			break;
		}
	}
	return 0;
}

#endif
