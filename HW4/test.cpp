#include "stdafx.h"
#include "Book.h"
#include <iostream>
using namespace std;
using namespace chrono;


int main()
{
	try {
		Book b1("2-3-4-c", "P&P", "Jane", "2017-1-1", children);
		cout << b1.ISBN() << endl;
		cout << b1.bookName() << endl;
		cout << b1.date() << endl;
		cout << b1.authorName() << endl;
		cout << b1.is_lent() << endl;  //check whether b1 is lent
		b1.borrow();  //borrow b1
		cout << b1.is_lent() << endl;  //check again
		Book b2("1-1-1-c", "Lake", "Lily", "2015-1-1", nonfiction);
		cout << operator ==(b1, b2) << endl;
		cout << b2 ;  //overloaded <<
	}
	catch (Book::Invalid) {
		cout << "Invalid ISBN" << endl;
	}
	try {
		Book b3("c-3-34-9", "Gone", "Mike", "2016-1-1", fiction);
	}
	catch (Book::Invalid) {
		cout << "Invalid ISBN" << endl;
	}

	return 0;
}