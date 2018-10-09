#include "stdafx.h"
#include "Book.h"
#include<iostream>
#include <string>
using namespace std;

namespace chrono {
	//member function definatioans:
	Book::Book(string bnum , string bna, string ana, string dt, Genre type)
		:bnum(bnum), bna(bna), ana(ana), dt(dt), lent(false), type(type)
	{
		if (!check(bnum)) throw Invalid();
	}

	bool Book::borrow()
	{
		if (!lent)
		{
			lent = true;
			return true;
		}
		return false;
	}  //assume that the book is not lent out
	void Book::_return()
	{
		lent = true;
	}
	bool check(string bnum) {
		int nSymbol = 0; // the number of '-'
		int nLen = bnum.size();  //the length of ISBN
		if (nLen <= 0)
		{
			return false;
		}

		for (int i = 0; i < nLen; i++)
		{
			// if it is '-':
			if ('-' == bnum[i])
			{
				nSymbol++;
				continue;
			}

			// if it is a number or a letter:
			if (nSymbol < 3)
			{
				// the first three elements should be numbers
				if (bnum[i] < '0' || bnum[i] > '9')
				{
					return false;
				}
			}
			else
			{
				// the fourth should be a number or a letter
				if (i != (nLen - 1))
				{
					return false;
				}

				if (!(
					(bnum[i] >= '0' && bnum[i] <= '9') ||
					(bnum[i] >= 'a' && bnum[i] <= 'z') ||
					(bnum[i] >= 'A' && bnum[i] <= 'Z')))
				{
					return false;
				}
			}
		}

		if (nSymbol != 3)
		{
			return false;
		}

		return true;
	}
	bool operator == (const Book& b1, const Book& b2)
	{
		return b1.ISBN() == b2.ISBN();
	}

	bool operator != (const Book& b1, const Book& b2)
	{
		return !(b1.ISBN() == b2.ISBN());
	}

	void operator << (ostream& os, const Book& b)
	{
		os << b.bookName() << endl;
		os << b.authorName() << endl;
		os << b.ISBN() << endl;
	}
}
