#include <iostream>
using namespace std;

int main() {
	int a, b, c;
	cout << "Please enter three integer values: " << endl;
	cin >> a >> b >> c;

	if (a >= b)
		if (b >= c) cout << c << "," << b << "," << a;
		else if (c >= a) cout << b << "," << a << "," << c;
		else cout << b << "," << c << "," << a;
	else
		if (a >= c) cout << c << "," << a << "," << b;
		else if (c >= b) cout << a << "," << b << "," << c;
		else cout << a << "," << c << "," << b << endl;

		return 0;

}