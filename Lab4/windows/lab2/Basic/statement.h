/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"


enum StatementType { REM,LET,INPUT,PRINT,END,IF,THEN ,GOTO};
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;
   virtual StatementType getType() = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class RemState: public Statement {
public :
	RemState(string function);
	virtual void execute(EvalState & state);
	virtual StatementType getType();
private:
	string func;
};


class LetState :public Statement {
public:
	LetState(string vari, Expression *expr);
	virtual ~LetState();
	virtual void execute(EvalState & state);
	virtual StatementType getType();
private:
	string var;
	Expression *exp;
};
class PrintState :public Statement {
public:
	PrintState(Expression *expr);
	virtual ~PrintState();
	virtual void execute(EvalState & state);
	virtual StatementType getType();
private:
	Expression *exp;
};
class InputState :public Statement {
public:
	InputState(string vari);
	virtual void execute(EvalState & state);
	virtual StatementType getType();
private:
	string var;

};
class EndState :public Statement {
public:
	EndState();
	virtual void execute(EvalState & state);
	virtual StatementType getType();

};
class GotoState :public Statement {
public:
	GotoState(int n);
	virtual void execute(EvalState & state);
	int getLineNum();
	virtual StatementType getType();
private:
	int num;
};
class IfThenState :public Statement {
public:
	IfThenState(Expression *expr1, string cmp, Expression *expr2,int n);
	virtual ~IfThenState();
	virtual void execute(EvalState & state);
	bool check();
	virtual StatementType getType();
private:
	Expression *exp1;
	string comp;
	Expression *exp2;
	int val1;
	int val2;
	int num;
};

#endif
