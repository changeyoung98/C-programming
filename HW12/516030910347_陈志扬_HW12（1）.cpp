#include <iostream>
using namespace std;

int ladder(int n) {
	if (n == 1) {
		return 1;
	}
	else if (n == 2) {
		return 2;
	}
	else {
		return ladder(1)*ladder(n - 1) + ladder(1)*ladder(n - 2);
	}
}


int main() {
	int N;
	cout << "Please enter the number: " << endl;
	cin >> N;
	if (N <= 0) {
		cout << "Invalid input." << endl;
		return 0;
	}
	cout << "The number of ways: " << ladder(N) << endl;
	return 0;

}