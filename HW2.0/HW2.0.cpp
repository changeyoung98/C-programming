// HW2.0.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int main()
{
	string expr;
	cout << "Please enter two integer values divided by an operation(format:operand operation operand). " << endl;
	cin >> expr;
	if (expr.find("+") < expr.size()) {
		int pos = expr.find("+");
		string left = expr.substr(0, pos);
		string right = expr.substr(pos + 1, expr.size());
		stringstream s,t;
		int operand1,operand2;
		s << left;
		t << right;
		if (s>>operand1 && t>>operand2) {
			cout << operand1 + operand2 << endl;
		}
		else {
			cout << "invalid input" << endl;
		}
		
	}
	else if (expr.find("-") < expr.size()) {
		int pos = expr.find("-");
		string left = expr.substr(0, pos);
		string right = expr.substr(pos + 1, expr.size());
		stringstream s, t;
		int operand1, operand2;
		s << left;
		t << right;
		if (s >> operand1 && t >> operand2) {
			cout << operand1 - operand2 << endl;
		}
		else {
			cout << "invalid input" << endl;
		}
	}
	else if (expr.find("*") < expr.size()) {
		int pos = expr.find("*");
		string left = expr.substr(0, pos);
		string right = expr.substr(pos + 1, expr.size());
		stringstream s, t;
		int operand1, operand2;
		s << left;
		t << right;
		if (s >> operand1 && t >> operand2) {
			cout << operand1 * operand2 << endl;
		}
		else {
			cout << "invalid input" << endl;
		}
	}
	else if (expr.find("/") < expr.size()) {
		int pos = expr.find("/");
		string left = expr.substr(0, pos);
		string right = expr.substr(pos + 1, expr.size());
		stringstream s, t;
		int operand1, operand2;
		s << left;
		t << right;
		if (s >> operand1 && t >> operand2)
			if (operand2 == 0) {
				cout << "division by 0" << endl;
			}
			else{
			cout << double(operand1) / operand2 << endl;
		}
		else {
			cout << "invalid input" << endl;
		}
	}
	else {
		cout << "invalid input" << endl;
	}
	
	return 0;
}

