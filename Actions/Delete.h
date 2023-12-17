#ifndef Delete_H
#define Delete_H
#include "..\Statements\Statement.h"
#include "Action.h"


//Add Rectangle Action class

class Delete: public Action
{
private:
	string Confirmation;
	Statement* stat;
	Connector* slctedConn;

public:
	Delete(ApplicationManager *pManager);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif