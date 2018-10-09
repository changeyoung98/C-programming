/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
//   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
		  string line = getLine();
		  if (line != "") {
			  processLine(line, program, state);
		  }
      } catch (ErrorException & ex) {
		  string er = ex.getMessage();
		  if (er != "DIVIDE BY ZERO"&&er != "INVALID NUMBER"&&er != "VARIABLE NOT DEFINED"&&er != "LINE NUMBER ERROR"&&er != "SYNTAX ERROR") {
			  cout << "SYNTAX ERROR" << endl;
		  }
		  else cout << er << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string first = scanner.nextToken();
	TokenType ty = scanner.getTokenType(first);
	if (ty == NUMBER) {  //if the first element is number
		int lineNumber = stringToInteger(first);
		int pos = scanner.getPosition();
		string command = scanner.nextToken();
		if (command.empty()){   //then it is a remove command
			program.removeSourceLine(lineNumber);
		}
		else {
			//build statements and set them to program
			string pline = line.substr(pos + 1, line.size() - pos - 1);
			if (command == "REM") {
				scanner.setInput("");
				Statement* stmt = new RemState(line);
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, stmt);
			}
			else if (command == "LET") {
				string var = scanner.nextToken();
				if (state.isCommand(var)) {
					error("SYNTAX ERROR");
				}
				string op = scanner.nextToken();
				if (op != "=") {
					error("SYNTAX ERROR");
				}
				Expression *exp = parseExp(scanner);
				Statement* stmt = new LetState(var, exp);
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, stmt);

			}
			else if (command == "PRINT") {
				Expression *exp = parseExp(scanner);
				Statement* stmt = new PrintState(exp);
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, stmt);
			}
			else if (command == "INPUT") {
				string var = scanner.nextToken();
				if (state.isCommand(var) || scanner.getTokenType(var) != WORD) {
					error("SYNTAX ERROR");
				}
				if (scanner.hasMoreTokens()) {
					error("SYNTAX ERROR");
				}
				Statement* stmt = new InputState(var);
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, stmt);
			}
			else if (command == "GOTO") {
				string num = scanner.nextToken();
				if (scanner.getTokenType(num) == WORD) {
					error("SYNTAX ERROR");
				}
				int n = stringToInteger(num);
				if (scanner.hasMoreTokens()) {
					error("SYNTAX ERROR");
				}
				GotoState* stmt = new GotoState(n);
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, stmt);
			}
			else if (command == "END") {
				EndState* stmt = new EndState();
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, stmt);
			}
			else if (command == "IF") {
				Expression * exp1 = readE(scanner);
				string ch = scanner.nextToken();
				if (ch != "<" &&ch != "="&&ch != ">") {
					error("SYNTAX ERROR");
				}
				Expression * exp2 = readE(scanner);
				string command = scanner.nextToken();
				if (command != "THEN") {
					error("SYNTAX ERROR");
				}
				string num = scanner.nextToken();
				if (scanner.getTokenType(num) == WORD) {
					error("SYNTAX ERROR");
				}
				int n = stringToInteger(num);
				if (scanner.hasMoreTokens()) {
					error("SYNTAX ERROR");
				}
				IfThenState* st = new IfThenState(exp1, ch, exp2, n);
				program.addSourceLine(lineNumber, pline);
				program.setParsedStatement(lineNumber, st);

			}
			else {
				error("SYNTAX ERROR");
			}
		}
	}
	else if (ty == WORD) {   //not a program line
		string command = first;
		if (state.isCommand(command) == false) {
			error("SYNTAX ERROR");
		}
		else if (command == "LET") {
			string var = scanner.nextToken();
			if (state.isCommand(var)) {
				error("SYNTAX ERROR");
			}
			string op = scanner.nextToken();
			if (op != "=") {
				error("SYNTAX ERROR");
			}
			Expression *exp = parseExp(scanner);
			LetState st(var, exp);
			st.execute(state);
		}
		else if (command == "PRINT") {
			Expression *exp = parseExp(scanner);
			PrintState st(exp);
			st.execute(state);
		}
		else if (command == "INPUT") {
			string var = scanner.nextToken();
			if (state.isCommand(var) || scanner.getTokenType(var) != WORD) {
				error("SYNTAX ERROR");
			}
			if (scanner.hasMoreTokens()) {
				error("SYNTAX ERROR");
			}
			InputState st(var);
			st.execute(state);
		}
		else if (command == "RUN") {
			int n = program.getFirstLineNumber();
			while (n != -1) {
				Statement *st = program.getParsedStatement(n);
				if (st != NULL) {
					st->execute(state);
					if (st->getType() == GOTO) {
						n = state.getValue("GOTO");     //get the set number for GOTO
						if (program.getSourceLine(n) == "") {
							error("LINE NUMBER ERROR");
						}
					}
					else if (st->getType() == THEN) {
						n = state.getValue("THEN");
						if (program.getSourceLine(n) == "") {
							error("LINE NUMBER ERROR");
						}
					}
					else if (st->getType() == END) {
						n = -1;
					}
				   else {
					   n = program.getNextLineNumber(n);
				   }
			   }
			   else {
				   n = program.getNextLineNumber(n);
			   }

		   }
	   }
		else if (command=="LIST"){
		   int n = program.getFirstLineNumber();
		   while (n != -1) {
			   cout << program.getSourceLine(n) << endl;
			   n = program.getNextLineNumber(n);
		   }
	   }
		else if (command == "QUIT"){
			state.clear();
		   program.clear();
		   exit(0);
	   }
		else if (command == "HELP") {
		   cout << "Yet another basic interpreter" << endl;
	   }
		else if (command == "CLEAR") {
			state.clear();
		   program.clear();
	   }
		else {
			error("SYNTAX ERROR");
		}
	   scanner.setInput("");
   }
	else {
		error("SYNTAX ERROR");
	}
}
