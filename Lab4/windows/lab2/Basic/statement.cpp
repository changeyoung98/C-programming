/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}


RemState::RemState(string function)
{
	this->func = function;
}

void RemState::execute(EvalState & state)
{
	state.getCommand("REM");
}

StatementType RemState::getType()
{
	return REM;
}

LetState::LetState(string vari, Expression * expr)
{
	this->var = vari;
	this->exp = expr;
}
LetState::~LetState() {
	delete exp;
}
void LetState::execute(EvalState & state)
{
	int val = exp->eval(state);
	state.setValue(var, val);
	state.isDefined(var);
	state.getCommand("LET");
}

StatementType LetState::getType()
{
	return LET;
}

PrintState::PrintState(Expression * expr)
{
	this->exp = expr;
}

PrintState::~PrintState()
{
	delete exp;
}

void PrintState::execute(EvalState & state)
{
	int val = exp->eval(state);
	cout << val << endl;
	
}

StatementType PrintState::getType()
{
	return PRINT;
}

InputState::InputState(string vari)
{
	this->var = vari;
}

void InputState::execute(EvalState & state)
{    //deal with the input element
	cout << " ? ";
	double value;
	string line;
	getline(cin, line);
	TokenScanner scan;
	scan.ignoreWhitespace();
	scan.scanNumbers();
	scan.setInput(line);
	string get = scan.nextToken();
	TokenType type = scan.getTokenType(get);
	string op = "";
	if (type == OPERATOR) {
		if (get == "-" || get == "+") {
			op = get;
			get = scan.nextToken();
			type = scan.getTokenType(get);
		}
		else {
			cout << "INVALID NUMBER" << endl;
			InputState::execute(state);
		}
	}
	if (type == NUMBER ){
		value = stringToReal(get);
		int val = int(value);
		if (val != value) {
			cout << "INVALID NUMBER" << endl;
			InputState::execute(state);
		}
		else if (scan.hasMoreTokens()) {
			cout << "INVALID NUMBER" << endl;
			InputState::execute(state);
		}
		else {
			if (op == "-") {
				val = -val;
			}
			state.setValue(var, val);
		}
	}
	else {
		cout << "INVALID NUMBER" << endl;
		InputState::execute(state);
		
	}
	
}

StatementType InputState::getType()
{
	return INPUT;
}

EndState::EndState()
{
}

void EndState::execute(EvalState & state)
{
	state.getCommand("END");
}

StatementType EndState::getType()
{
	return END;
}

GotoState::GotoState(int n)
{
	this->num = n;
}

void GotoState::execute(EvalState & state)
{   //set GOTO with its number
	state.setValue("GOTO", num);
	state.isDefined("GOTO");
}

int GotoState::getLineNum()
{
	return num;
}

StatementType GotoState::getType()
{
	return GOTO;
}

IfThenState::IfThenState(Expression * expr1, string cmp, Expression * expr2,int n)
{
	this->exp1 = expr1;
	this->comp = cmp;
	this->exp2 = expr2;
	this->num = n;
}

IfThenState::~IfThenState()
{
	delete exp1;
	delete exp2;
}

void IfThenState::execute(EvalState & state)
{
	val1 = exp1->eval(state);
	val2 = exp2->eval(state);
	if (IfThenState::check()) {
		state.setValue("THEN", num);
		state.isDefined("THEN");
	}
}

bool IfThenState::check()   //check the condition
{
	if (comp == "<") {
		return val1 < val2;
	}
	else if (comp == "=") {
		return val1 == val2;
	}
	else if (comp == ">") {
		return val1 > val2;
	}
	else {
		error("SYNTAX ERROR");
	}
}

StatementType IfThenState::getType()
{
	if (IfThenState::check()) {
		return THEN;
	}
	else return IF;
}

