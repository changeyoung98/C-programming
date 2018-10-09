// HW2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


int main() {
	string operation;
	int operand1;
	int operand2;
	cout << "Please enter an operation between two integer operands(format:operand operation operand): " << endl;
	cin >> operand1 >> operation;
	cin >> operand2;
	if (!cin)
	{
		cout << "invalid input" << endl;
	}
	else {
		if (operation == "+") { cout << operand1 << "+" << operand2 << "=" << operand1 + operand2; }
		else if (operation == "-") { cout << operand1 << "-" << operand2 << "=" << operand1 - operand2; }
		else if (operation == "*") { cout << operand1 << "*" << operand2 << "=" << operand1 * operand2; }
		else if (operation == "/"&&operand2 != 0) { cout << operand1 << "/" << operand2 << "=" << double(operand1) / operand2; }
		else if (operation == "/"&&operand2 == 0) { cout << "division by 0"; }
		else cout << "invalid input" << endl;
	}
	
	

	return 0;
}
	