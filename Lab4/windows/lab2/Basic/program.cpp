/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
	Program::clear();
   // Replace this stub with your own code
}

void Program::clear() {
	lines.clear();
	stmts.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
	if (stmts.containsKey(lineNumber)) {
		delete stmts.get(lineNumber);
	}
	lines.put(lineNumber, line);

}

void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
	if (lines.containsKey(lineNumber)) {
		lines.remove(lineNumber);
	}
	if (stmts.containsKey(lineNumber)) {
		delete stmts.get(lineNumber);
		stmts.remove(lineNumber);
	}
}

string Program::getSourceLine(int lineNumber) {
	if (lines.containsKey(lineNumber)) {
		stringstream ss;
		ss << lineNumber;
		string num;
		ss >> num;
		string SourceLine = num +" "+ lines[lineNumber];
		return SourceLine;
	}  // Replace this stub with your own code
	else return "";
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
	if (lines.containsKey(lineNumber)) {
		if (stmts.containsKey(lineNumber)) {
			stmts.remove(lineNumber);
	
		}
		stmts.put(lineNumber, stmt);
		
	}
	else error("");
}

Statement *Program::getParsedStatement(int lineNumber) {
	if (stmts.containsKey(lineNumber)) {
		return stmts[lineNumber];
	}
	else return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
	if (lines.isEmpty() == false) {
		Map<int, string>::iterator it;
		it = lines.begin();
		int n = *it.operator->();
		return n;
	}    // Replace this stub with your own code
	return -1;
}

int Program::getNextLineNumber(int lineNumber) {
	if (lines.containsKey(lineNumber) == false) {
		return -1;
	}
	Map<int, string>::iterator it;
	it = lines.begin();
	while (*it.operator->() != lineNumber) {
		&it.operator++();
	}
	&it.operator++();
	if (it==lines.end()) {
		return -1;
	}
	int m = *it.operator->();
    return m;     // Replace this stub with your own code
}
