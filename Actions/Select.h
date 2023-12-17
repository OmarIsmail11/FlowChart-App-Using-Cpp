#ifndef Select_H
#define Select_H
#include "..\Statements\Statement.h"
#include "Action.h"

//Add Rectangle Action class

class Select: public Action
{
private:
	Point Postion;
public:
	Select(ApplicationManager *pManager);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif