#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Slides {
public:
	struct Node {
		Node *prev, *next;
		int ind;  // index of mate
		Node *mate;

		inline Node() : prev(NULL), next(NULL), mate(NULL) {
		}
	};

	struct Tuple {
		float x, y;
	};

	struct Label {
		Tuple coord;
		int deg;  // "degree" of label -- number of pieces it lies on
		Node *list;

		inline Label() : deg(0) {
			list = new (nothrow) Node;
		}

		inline ~Label() {
			Node *tmp1 = list, *tmp2 = list->next;
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
		Node *list;

		inline Piece() {
			list = new (nothrow) Node;
		}

		inline ~Piece() {
			Node *tmp1 = list, *tmp2 = list->next;
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

private:
	int n;
	Label *lab;  // labels on slides
	Piece *pc;  // pieces of slides
};

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
				Node *lab_node = new (nothrow) Node, *pc_node = new (nothrow) Node;
				lab_node->ind = j;  // new node in Label point to Piece j
				pc_node->ind = i;  // new node in Piece point to Label i
				lab_node->mate = pc_node;
				pc_node->mate = lab_node;
			}
		}
	}
}

inline Slides::~Slides() {
	delete [] lab;
	delete [] pc;
}

int main() {
	Slides slides;
	return 0;
}
