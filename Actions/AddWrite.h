#ifndef ADD_WRITE_H
#define ADD_WRITE_H

#include "Action.h"
#include "..\Statements\Write.h"

//Add Write Assignment Statement Action
class AddWrite : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.
	string variable;

public:
	AddWrite(ApplicationManager *pAppManager);

	//Read Write statements position
	virtual void ReadActionParameters();
	
	//Create and add an Write statement to the list of statements
	virtual void Execute() ;
	
};

#endif