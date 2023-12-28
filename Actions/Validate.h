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

//Make VAlidation before running

class Validate: public Action
{
private:

public:
	Validate(ApplicationManager *pManager);

	
	virtual void ReadActionParameters();
	
	
	virtual void Execute() ;
	
};

#endif