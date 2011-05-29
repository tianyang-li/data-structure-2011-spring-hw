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
		Node<Mate> *list;

		inline Label() : deg(0) {
			list = new (nothrow) Node<Mate>;
		}

		inline ~Label() {
			Node<Mate> *tmp1 = list, *tmp2;
			while (tmp1) {
				tmp2 = tmp1;
				tmp1 = tmp1->next;
				delete tmp2;
			}
		}
	};

	struct Piece {
		Tuple ll, ur;  // lower left, upper right
		int ind;  // index of this piece
		int page;  // page number on this piece, not determined until later
		Node<Mate> *list;

		inline Piece() {
			list = new (nothrow) Node<Mate>;
		}

		inline ~Piece() {
			Node<Mate> *tmp1 = list, *tmp2;
			while (tmp1) {
				tmp2 = tmp1;
				tmp1 = tmp1->next;
				delete tmp2;
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

	inline bool IdSlide(Node<Index> *const label) {  // identify the slide with this label
		Index pc_id = lab[label->data].list->next->data.mate_ind;
		pc[pc_id].ind = label->data;
		Node<Mate> *tmp = pc[pc_id].list->next;
		if (!tmp) {
			return false;
		}
		while (tmp) {
			Index tmp_ind = tmp->data.mate_ind;
			--lab[tmp_ind].deg;
			if (1 == lab[tmp_ind].deg) {
				InsertOne(tmp_ind);
			}
			else {
				if ((0 >= lab[tmp_ind].deg) && (label->data != tmp_ind)) {
					return false;
				}
			}
			Node<Mate> *tmp1 = tmp->data.mate_ptr;
			tmp1->prev->next = tmp1->next;
			if (tmp1->next) {
				tmp1->next->prev = tmp1->prev;
			}
			delete tmp1;
			Node<Mate> *tmp2 = tmp;
			tmp = tmp->next;
			delete tmp2;
		}
		return true;
	}
};

inline void Slides::Proc() {
	for (int i = 0; i != n; ++i) {
		if (0 == lab[i].deg) {
			cout << -1 << endl;
			return;
		}
		if (1 == lab[i].deg) {
			InsertOne(i);
		}
	}
	int unproc = n;  // # of unprocessed labels
	while ((0 != unproc) && (NULL != one->next)) {
		Node<Index> *tmp = GetOne();
		if (!IdSlide(tmp)) {
			cout << -1 << endl;
			return;
		}
		delete tmp;
		--unproc;
	}
	if (0 != unproc) {
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
				lab_node->prev = lab[i].list;
				lab_node->next = lab[i].list->next;
				if (lab[i].list->next) {
					lab[i].list->next->prev = lab_node;
				}
				lab[i].list->next = lab_node;
				pc_node->prev = pc[j].list;
				pc_node->next = pc[j].list->next;
				if (pc[j].list->next) {
					pc[j].list->next->prev = pc_node;
				}
				pc[j].list->next = pc_node;
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
	slides.Proc();
	return 0;
}
