#ifndef ADD_Operator_ASSIGN_H
#define ADD_Operator_ASSIGN_H

#include "Action.h"
#include "..\Statements\OpAssign.h"

//Add Operator Assignment Statement Action

class AddOperatorAssign : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.
	string LHS;
	string RHS1;
	string Operator;
	string RHS2;

public:
	AddOperatorAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif