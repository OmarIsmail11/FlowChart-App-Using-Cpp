#ifndef ADD_COND_H
#define ADD_COND_H

#include "Action.h"
#include "..\Statements\Condtion.h"


class AddCond : public Action
{
private:
	string LHS;
	string RHS;
	string CompOper;

	Point Position;	//Position where the user clicks to add the stat.

public:
	AddCond(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif