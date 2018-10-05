/*This is the original version of word ladder
The code of some extra features are still kept, but can be ignored
The renew version can be found in wordladder_extra.cpp
*/

#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include<algorithm>
#include<time.h>
using namespace std;

unordered_map<string,int> dic;   // contains all the words in the dictionary with original value 1

string sta;

int wla(string start,queue<stack<string>> q, string end) {
	while (!q.empty() ){
		string start = q.front().top();  
		stack<string> s = q.front();
		// find the neighbour word of the top word of the first stack
		for (int i = 0; i<start.size(); i++) {
			for (char ch = 'a'; ch <= 'z'; ch++) {
				if (ch != start[i]) {
					string new_word = start;
					new_word[i] = ch;   //change characters
					stack<string> st = s;
					if (new_word == end) {
						cout << "A ladder from " << end << " back to " << sta << ": " << endl;
						s.push(new_word);
						int alength = s.size();
						for (int j = 0; j < alength; j++) {
							cout << s.top() << "\t";
							s.pop();
						}
						cout << '\n';
						cin.get();
						return 0;
					}
			
					if (dic[new_word]>0){
						st.push(new_word);
						dic[new_word] = 0;
						q.push(st);
					}
				}
			}
		}
		q.pop();   //delete the previous stack 
	}
	if (q.empty()) {   //shows that the stack has all been deleted, but no ladder has been found
		cout << "No word ladder found from "<<end<<" back to "<<sta<<"." << endl;
		cin.get();
		return 0;
	}
  
	return 0;
}


int main() {
	string filename;
	cout << "Dictionary file name? ";
	cin >> filename;
	cin.get();
	ifstream infile;
	infile.open(filename);
	while (!infile) {  //check whether the file exists
		cout << "Unable to open that file. Try again." << endl;
		cout << "Dictionary file name? ";
		cin >> filename;
		cin.get();
		infile.open(filename);
	}
	string line;
	while (!infile.eof()) {
		getline(infile, line);
		dic[line]++;
	}  //store the words
	unordered_map<string, int> dict=dic;  //a dic to renew the dic that has been changed in previous search
	while (true) {
		dic = dict;
		cout << "Word #1(or Enter to quit): ";
		string word1;
		char ch = cin.get();
		if (ch == '\n') {
			cout << "Have a nice day." << endl;  //enter to quit function
			return 0;
		}
		cin.putback(ch);
		cin >> word1;
		for (int i = 0; i < word1.length(); i++) {
			if (word1[i] >= 'A'&&word1[i] <= 'Z') {
				word1[i] += 32;
			}
		}    //the function to ignore uppercase
		cin.get();
		cout << "Word #2(or Enter to quit): ";
		string word2;
		char chr = cin.get();
		if (chr =='\n') {
			cout << "Have a nice day." << endl;
			return 0;
		}
		cin.putback(chr);
		cin >> word2;
		for (int i = 0; i < word2.length(); i++) {
			if (word2[i] >= 'A'&&word2[i] <= 'Z') {
				word2[i] += 32;
			}
		}
		if (dic[word1] == 0||dic[word2]==0) {
			cout << "The two words must be found in the dictionary." << endl;
			cin.get();
			continue;
		}                        //check 1
		if (word1.size() != word2.size()) {
			cout << "The two words must be the same length." << endl;
			cin.get();
			continue;
		}                      //check 2
		if (word1 == word2) {
			cout << "The two words must be different." << endl;
			cin.get();
			continue;

		}                          //check 3
		sta = word1;
		stack<string> s;
		s.push(word1);
		queue<stack<string>> q;
		q.push(s);
		dic[word1] = 0;   //set word1 as used 
		wla(word1,q, word2);
	}
	
	
	return 0;
}
