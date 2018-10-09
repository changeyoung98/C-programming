//file:Book.h
#include<iostream>
#include <string>
using namespace std;

namespace chrono {
	enum Genre {
		fiction = 1, nonfiction, periodical, biography, children
	};  //the type of books
	class Book {
	public:
		class Invalid { };  //to throw as exception
		Book(string bnum, string bna, string ana, string dt, Genre type);  //check for valid ISBN and initialize
		string ISBN()
			const {
			return bnum;
		}
		string bookName()
			const {
			return bna;
		}
		string authorName()
			const {
			return ana;
		}
		string date()
			const {
			return dt;
		}
		bool is_lent()
			const {
			return lent;
		}  //ckeck whether the book has been borrowed
		//modofying operations:
		bool borrow();  //borrow books
		void _return();  //return books
		friend void operator << (ostream& os, const Book& b);
	private:
		string bnum;  //ISBN
		string bna = "bookName";  //book name
		string ana = "authorName";  //author name
		string dt = "date";  //copyright date
		bool lent;
		Genre type;
	};
	bool check(string a);  //check whether the ISBN is valid
	bool operator==(const Book&b1, const Book&b2);
	bool operator!=(const Book&b1, const Book&b2);
	void operator << (ostream& os, const Book& b);

}  //chrono
