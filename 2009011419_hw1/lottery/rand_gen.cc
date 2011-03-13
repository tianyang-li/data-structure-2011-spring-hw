#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	int n;
	cin >> n;
	cout << n << endl;
	srand(int(time(NULL)));
	for (int i = 0; i != n; ++i) {
		cout << rand() << " ";
	}
	cout << endl;
}
