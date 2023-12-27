#ifndef VALIDATE_H
#define VALIDATE_H
#include "..\Statements\Statement.h"
#include "..\Statements\Start.h"
#include "..\Statements\Read.h"
#include "..\Statements\Write.h"
#include "..\Statements\ValueAssign.h"
#include "..\Statements\VarAssign.h"
#include "..\Statements\OpAssign.h"
#include "..\Statements\Condtion.h"
#include "..\Connector.h"
#include "..\Statements\End.h"
#include "Action.h"

//Add Rectangle Action class

class Validate: public Action
{
private:

public:
	Validate(ApplicationManager *pManager);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	
};

#endif