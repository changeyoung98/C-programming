#include "std_lib_facilities.h"
using namespace std;

int main() {
	string operation;
	double operand1, operand2;
	cout << "Please enter an operation followed by two operands: " << endl;
	cin >> operation;
	cin >> operand1 >> operand2;

	if (operation == "+") { cout << operand1 << "+" << operand2 << "=" << operand1 + operand2; }
	else if (operation == "-") { cout << operand1 << "-" << operand2 << "=" << operand1 - operand2; }
	else if (operation == "*") { cout << operand1 << "*" << operand2 << "=" << operand1 * operand2; }
	else if (operation == "/") { cout << operand1 << "/" << operand2 << "=" << operand1 / operand2; }
	else cout << "wrong!" << endl;

	return 0;
}