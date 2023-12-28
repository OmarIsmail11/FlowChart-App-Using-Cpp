#ifndef ADD_READ_H
#define ADD_READ_H

#include "Action.h"
#include "..\Statements\Read.h"

//Read Assignment Statement Action

class AddRead : public Action
{
private:
	
	Point Position;	//Position where the user clicks to add the stat.
	string variable;

public:
	AddRead(ApplicationManager *pAppManager);

	//Read Read statements position
	virtual void ReadActionParameters();
	
	//Create and add an Read statement to the list of statements
	virtual void Execute() ;
	
};

#endif