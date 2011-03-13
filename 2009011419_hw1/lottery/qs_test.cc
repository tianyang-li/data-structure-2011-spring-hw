#include <iostream>

#include "quick_sort.h"

int main() {
	int n;
	std::cin >> n;
	int *a = new int[n];
	for (int i = 0; i != n; ++i) {
		std::cin >> a[i];
	}
	QuickSort(a, 0, n - 1);
	for (int i = 0; i != n; ++i) {
		std::cout << a[i] << std::endl;
	}
}
