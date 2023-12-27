#ifndef Cut_H
#define Cut_H
#include "..\Statements\Statement.h"
#include "Action.h"
#include "..\ApplicationManager.h"

//Add Cut Action class

class Cut: public Action
{
private:
	Statement* SelectedStatetment;
	string Confirmation;
	Statement* stat;
	Connector* slctedConn;
public:
	Cut(ApplicationManager* pManager);
	virtual void Execute();
	virtual void ReadActionParameters();
};

#endif