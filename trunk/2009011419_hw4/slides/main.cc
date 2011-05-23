#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstddef>

using namespace std;

class Slides {
public:
	template <class T>
	struct Node {
		Node<T> *prev, *next;
		T data;

		inline Node() : prev(NULL), next(NULL) {
		}
	};

	typedef int Index;

	struct Mate {
		Index mate_ind;
		Node<Mate> *mate_ptr;
	};

	struct Tuple {
		float x, y;
	};

	struct Label {
		Tuple coord;
		int deg;  // "degree" of label -- number of pieces it lies on
		Node<Mate> *list, *tail;

		inline Label() : deg(0) {
			list = new (nothrow) Node<Mate>;
			tail = list;
		}

		inline ~Label() {
			Node<Mate> *tmp1 = list, *tmp2 = list->next;
			while (tmp1) {
				delete tmp1;
				tmp1 = tmp2;
				if (tmp1) {
					tmp2 = tmp1->next;
				}
			}
		}
	};

	struct Piece {
		Tuple ll, ur;  // lower left, upper right
		int ind;  // index of this piece
		int page;  // page number on this piece, not determined until later
		Node<Mate> *list, *tail;

		inline Piece() {
			list = new (nothrow) Node<Mate>;
			tail = list;
		}

		inline ~Piece() {
			Node<Mate> *tmp1 = list, *tmp2 = list->next;
			while (tmp1) {
				delete tmp1;
				tmp1 = tmp2;
				if (tmp1) {
					tmp2 = tmp1->next;
				}
			}
		}

		bool inline On(Tuple const &pt) {  // true if pt is on this piece
			return (pt.x >= ll.x && pt.x <= ur.x && pt.y >= ll.y && pt.y <= ur.y);
		}
	};

	inline Slides();
	inline ~Slides();

	inline void Proc();

private:
	int n;
	Label *lab;  // labels on slides
	Piece *pc;  // pieces of slides
	Node<Index> *one;  // list of Label on only one Piece

	inline Node<Index> *GetOne() {
		Node<Index> *tmp = one->next;
		one->next = tmp->next;
		if (tmp->next) {
			tmp->next->prev = one;
		}
		return tmp;
	}

	inline void InsertOne(Index const ind) {
		Node<Index> *tmp = new (nothrow) Node<Index>;
		tmp->data = ind;
		tmp->prev = one;
		tmp->next = one->next;
		one->next = tmp;
	}
};

inline void Slides::Proc() {
	for (int i = 0; i != n; ++i) {
		if (0 == lab[i].deg) {
			cout << -1 << endl;
			return;
		}
		InsertOne(i);
	}
	int unproc = n;  // # of unprocessed labels
	while ((0 != unproc) && (NULL != one->next)) {
		Node<Index> *tmp = GetOne();
		delete tmp;
	}
	if (NULL == one->next) {
		cout << -1 << endl;
		return;
	}
	for (int i = 0; i != n; ++i) {
		printf("%d %d\n", i + 1, pc[i].ind + 1);
	}
}

inline Slides::Slides() {
	cin >> n;
	lab = new (nothrow) Label[n];
	pc = new (nothrow) Piece[n];
	for (int i = 0; i != n; ++i) {
		scanf("%f %f %f %f", &pc[i].ll.x, &pc[i].ll.y, &pc[i].ur.x, &pc[i].ur.y);
		pc[i].ind = i;
	}
	for (int i = 0; i != n; ++i) {
		scanf("%f %f", &lab[i].coord.x, &lab[i].coord.y);
		for (int j = 0; j != n; ++j) {
			if (pc[j].On(lab[i].coord)) {
				++lab[i].deg;
				Node<Mate> *lab_node = new (nothrow) Node<Mate>, *pc_node = new (nothrow) Node<Mate>;
				lab_node->data.mate_ind = j;  // new node in Label point to Piece j
				pc_node->data.mate_ind = i;  // new node in Piece point to Label i
				lab_node->data.mate_ptr = pc_node;
				pc_node->data.mate_ptr = lab_node;
				lab[i].tail->next = lab_node;
				lab_node->prev = lab[i].tail;
				lab[i].tail = lab_node;
				pc[j].tail->next = pc_node;
				pc_node->prev = pc[j].tail;
				pc[j].tail = pc_node;
			}
		}
	}
	one = new (nothrow) Node<Index>;
}

inline Slides::~Slides() {
	delete [] lab;
	delete [] pc;
	Node<Index> *tmp1 = one, *tmp2 = one->next;
	while (tmp1) {
		delete tmp1;
		tmp1 = tmp2;
		if (tmp1) {
			tmp2 = tmp1->next;
		}
	}
}

int main() {
	Slides slides;
	return 0;
}
