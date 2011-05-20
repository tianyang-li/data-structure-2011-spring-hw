#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Slides {
public:
	struct Tuple {
		float x, y;
	};

	typedef Tuple Label;

	struct Piece {
		Tuple ll, ur;  // lower left, upper right
	};

	inline Slides();
	inline ~Slides();

private:
	int n;
	Label *lab;
	Piece *sld;
};

inline Slides::Slides() {
	cin >> n;
	lab = new (nothrow) Label[n];
	sld = new (nothrow) Piece[n];
}

inline Slides::~Slides() {
	delete [] lab;
	delete [] sld;
}

int main() {
	Slides slides;
	return 0;
}
