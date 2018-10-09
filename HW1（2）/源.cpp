#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	string s = "1+2-3";
	stringstream ss(s);
	char ch;
	ss >> ch;
	cout << ch << endl;
	ss.putback(ch);
	ss >> ch;
	cout << ch;
	

}
