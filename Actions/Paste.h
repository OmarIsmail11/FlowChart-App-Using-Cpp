#ifndef Paste_H
#define Paste_H
#include "..\Statements\Statement.h"
#include "..\Statements\Condtion.h"
#include "..\Statements\Read.h"
#include "..\Statements\End.h"
#include "..\Statements\Write.h"
#include "..\Statements\Start.h"
#include "..\Statements\OpAssign.h"
#include "..\Statements\ValueAssign.h"
#include "..\Statements\VarAssign.h"
#include "Action.h"
#include "..\ApplicationManager.h"

//Add Paste Action class

class Paste: public Action
{
private:
	Point Position;
	
public:
	Paste(ApplicationManager* pManager);
	virtual void ReadActionParameters();

	virtual void Execute();
};

#endif