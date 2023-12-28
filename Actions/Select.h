#ifndef Select_H
#define Select_H
#include "..\Statements\Statement.h"
#include "Action.h"

//Slecet Statement or Connector

class Select: public Action
{
private:
	Point Postion;
public:
	Select(ApplicationManager *pManager);

	//read point of statement 
	virtual void ReadActionParameters();
	
	//Select it or unslect it if not selected
	virtual void Execute() ;
	
};

#endif