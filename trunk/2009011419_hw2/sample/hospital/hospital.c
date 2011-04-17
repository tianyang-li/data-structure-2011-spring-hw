#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define MAX_CITY 1000000

int n;  /* # of cities */

struct Adj {
	int vert;
	struct Adj *next;
};

typedef struct Adj Adj;

#define VIS 1  /* city visited */
#define NO_VIS 0  /* city not visited */

struct City {
	int64_t cost;
	int64_t subtree;
	int64_t pop;
	int visited;
	Adj adj, *end;
};

typedef struct City City;

City city[MAX_CITY];

void InitDFS() {
	int i;
	for (i = 0; i != n; i++) {
		city[i].visited = NO_VIS;
	}
}

void Bridge(int city1, int city2) {
	Adj *br;
	br = (Adj *) malloc(sizeof(Adj));
	br->vert = city2;
	city[city1].end->next = br;
	city[city1].end = br;
	br = (Adj *) malloc(sizeof(Adj));
	br->vert = city1;
	city[city2].end->next = br;
	city[city2].end = br;
}

int Min() {
	int min = 0, i = 1;
	while (i != n) {
		if (city[i].cost < city[min].cost) {
			min = i;
		}
	}
	return min;
}

void DFS1(int cur_city) {
	static int64_t tmp1;
	city[cur_city].visited = VIS;
	Adj *nb = city[cur_city].adj.next;
	do {
		if (city[nb->vert].visited == NO_VIS) {
			DFS1(nb->vert);
			tmp1 = city[nb->vert].subtree + city[nb->vert].pop;
			city[cur_city].subtree += tmp1;
			city[cur_city].cost += (tmp1 + city[nb->vert].cost);
		}
		nb = nb->next;
	} while (nb != city[cur_city].end->next);
}

void DFS2(int cur_city) {
	static int64_t tmp2;
	city[cur_city].visited = VIS;
	Adj *nb = city[cur_city].adj.next;
	do {
		if (city[nb->vert].visited == NO_VIS) {
			DFS2(nb->vert);
		}
		nb = nb->next;
	} while (nb != city[cur_city].end->next);
}

int main(int argc, char **argv) {
	scanf("%d", &n);
	int i;
	for (i = 0; i != n; ++i) {
		scanf("%lld", &city[i].pop);
		city[i].end = &city[i].adj;
		city[i].cost = city[i].subtree = 0;
	}
	int edge = n - 1;
	int tmp_city1, tmp_city2;
	for (i = 0; i != edge; ++i) {
		scanf("%d %d", &tmp_city1, &tmp_city2);
		--tmp_city1;
		--tmp_city2;
		Bridge(tmp_city1, tmp_city2);
	}
	srand(time(NULL));
	int root = rand() % n;
	InitDFS();
	DFS1(root);
	InitDFS();
	DFS2(root);
	printf("%d\n", Min() + 1);
	return 0;
}

