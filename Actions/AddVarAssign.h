#ifndef ADD_VAR_ASSIGN_H
#define ADD_VAR_ASSIGN_H

#include "Action.h"
#include "..\Statements\VarAssign.h"

//Add Var Assignment Statement Action

class AddVarAssign : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.
	string LHS;//left hand side variable
	string RHS;//assigned variable

public:
	AddVarAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif