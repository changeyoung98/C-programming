#include <iostream>
#include<string>
using namespace std;
/*string n;
cout << "Please enter a spelled-out number between zero and nine(zero and nine included)." << endl;
cin >> n;
//enum NUMBER{zero,one,two,three,four,five,six,seven,eight,nine};
if (n == "zero")
cout << "zero corresponds to value 0, it is an even number.";
else if (n == "one")
cout << "one corresponds to value 1, it is an odd number.";
else if (n == "two")
cout << "two corresponds to value 2, it is an even number.";
else if (n == "three")
cout << "three corresponds to value 3, it is an odd number.";
else if (n == "four")
cout << "four corresponds to value 4, it is an even number.";
else if (n == "five")
cout << "five corresponds to value 5, it is an odd number.";
else if (n == "six")
cout << "six corresponds to value 6, it is an even number.";
else if (n == "seven")
cout << "seven corresponds to value 7, it is an odd number.";
else if (n == "eight")
cout << "eight corresponds to value 8, it is an even number.";
else if (n == "nine")
cout << "nine corresponds to value 9, it is an odd number.";
else cout << "not a number." << endl;*/



int getSpelledOutNumber(string sptNumber) {
	string Number[]= { "zero", "one", "two", "three", 
		"four", "five", "six", "seven", "eight", "nine" };
	for (int i = 0; i < 10; i++) {
		if (Number[i] == sptNumber) return i;
	}
	return -1;
}
string numberKind(int num) {
	int remainder = num % 2;
	if (remainder == 0) return "even number.";
	else return "odd number.";
}
int main()
{
	string spelledOutNumber;
	cout << "Please enter a spelled-out number between zero and nine(zero and nine included)." << endl;
	getline(cin, spelledOutNumber);
	int number = getSpelledOutNumber(spelledOutNumber);
	if (number == -1) {
		cout << "not a number." << endl;
		return 0;
	}
	else {
		cout << spelledOutNumber << " corresponds to value " << number
			<< ", it is an " << numberKind(number) << endl;
	}

	return 0;
}