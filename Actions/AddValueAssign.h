#ifndef ADD_VALUE_ASSIGN_H
#define ADD_VALUE_ASSIGN_H

#include "Action.h"
#include "..\Statements\ValueAssign.h"

//Add Value Assignment Statement Action

class AddValueAssign : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.
	
	string LHS;
	double RHS;

public:
	AddValueAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif