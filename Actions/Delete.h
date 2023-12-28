#ifndef Delete_H
#define Delete_H
#include "..\Statements\Statement.h"
#include "Action.h"


//Delete selected statement or connector

class Delete: public Action
{
private:
	string Confirmation;
	Statement* stat;
	Connector* slctedConn;

public:

	Delete(ApplicationManager *pManager);

	//Reads statement location
	virtual void ReadActionParameters();
	
	//Delete it from appamanger
	virtual void Execute() ;
	
};

#endif