#ifndef ADD_START_H
#define ADD_START_H

#include "Action.h"
#include "..\Statements\Start.h"

//Add Start Assignment Statement Action

class AddStart : public Action
{
private:


	Point Position;	//Position where the user clicks to add the stat.

public:
	AddStart(ApplicationManager *pAppManager);

	//Read Start statements position
	virtual void ReadActionParameters();
	
	//Create and add an Start statement to the list of statements
	virtual void Execute() ;
	
};

#endif