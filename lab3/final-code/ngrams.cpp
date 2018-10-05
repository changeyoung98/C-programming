/*Extra features:
Function 1: write a whole paragraph
            see Function (1)
*/

#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;


int main() {
	map<string, vector<string>> col;
	vector<string> vec;
	string Num;
	string filename;
	cout << "Input file? ";
	cin >> filename;
	cin.get();
	ifstream infile;
	infile.open(filename);
	while (!infile) {   //check whether the file exists
		cout << "No such file.Please enter again. ";
		cin >> filename;
		cin.get();
		infile.open(filename);
	}
	string word;
	while (!infile.eof()) {
		infile >> word;
		vec.push_back(word);
	}  //vec is a container of all the words of the passage

	int length = vec.size();
	cout << "Value of N? ";
	cin >> Num;
	int N =0;
	while (true) {    //check whether the input N is valid
		stringstream nn;
		nn << Num;
		if (nn >> N) {
			stringstream mm;
			mm << N;
			string Nu;
			mm >> Nu;
			if (Nu.size() != Num.size()) {
				cout << "Invalid N format. Please enter again. ";
				cin >> Num;
			}
			else break;
		}
		else {
			cout << "Invalid N format. Please enter again. ";
			cin >> Num;
		}

	}
	while ((N >= length) || (N <= 1)) {   //check whether the input N is valid
		cout << "Invalid N. Please enter again: ";
		cin >> Num;
		stringstream nn;
		nn.clear();
		nn << Num;
		nn >> N;
	}
	int n = N - 1;
	vector<string> key_col;   
	clock_t t1 = clock();
	for (int i = 0; i < length; i++) {
		string key;
		for (int j = 0; j < n; j++) {
			if (i + j < length) {
				key = key + vec[i + j]+" ";
			}
			else {
				key = key + vec[i + j - length]+" ";
			}
		}
		key_col.push_back(key);
		if (i + n < length) {
			col[key].push_back(vec[i + n]);
		}
		else {
			col[key].push_back(vec[i + n - length]);
		}
	}     //build a collection of all the N-1 words and their suffixes
	clock_t t2 = clock();
	cout << t2 - t1 << "ms" << endl;
	while (true) {
		map<vector<string>, vector<string>>::iterator it;
		int num;
		string number;
		cout << "#of random words to generate(0 to quit)? ";
		cin >> number;
		while (true) {    //check whether the input num is valid
			stringstream ss;
			ss << number;
			if (ss >> num) {
				stringstream tt;
				tt << num;
				string check;
				tt >> check;
				if (check.size() != number.size()) {
					cout << "Invalid num format. Please enter again. ";
					cin >> number;
				}
				else break;
			}
			else {
				cout << "Invalid num format. Please enter again. ";
				cin >> number;
			}
		}
		if (num == 0) {
			cout << "Exciting." << endl;
			return 0;
		}   //0 to quit function
		if (num < N) {
			cout << "Must be at least " << N << " words." << endl;
			continue;
		}   //check the input num
		int x = col.size() - 1;
		int i = 0;

		string current;
		srand((int)time(NULL));
		int ran_num = rand() % x;    //produce a random word
		while (current.size() == 0) {
			string curr = key_col[ran_num];
			if (curr[0] >= 'A' && curr[0] <= 'Z') {
				current = curr;
			}                        //to find the uppercase to begin the passage     FUNCTION (1)
			else {
				srand((int)time(NULL));
				ran_num = rand() % x;
			}
		}


		cout << current;

		int k = 0;
		int sz = current.size();
		//check whether the ending is the ending of a sentence
		while ((k <= num - n) || (current[sz - 2] != '?'&& current[sz - 2] != '.'&& current[sz - 2] != '!'/*&& current[sz - 2] != ','*/)) {
			int y = col[current].size();
			srand((int)time(NULL));
			int ran = rand() % y;    //to choose the suffix randomly
			cout << col[current][ran] + " ";
			current = current + col[current][ran] + " ";
			int pos = current.find(" ");
			sz = current.size();
			current = current.substr(pos + 1, sz - pos - 1);  // change the current prefix
			sz = current.size();
			k++;
		}
		cout <<'\n'<< endl;
	}
	return 0;
}