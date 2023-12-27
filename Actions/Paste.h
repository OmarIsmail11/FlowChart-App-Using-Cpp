#ifndef Paste_H
#define Paste_H
#include "..\Statements\Statement.h"
#include "Action.h"
#include "..\ApplicationManager.h"

//Add Paste Action class

class Paste: public Action
{
private:
	Point Position;
	Statement* CopiedStatement;
public:
	Paste(ApplicationManager* pManager);
	virtual void Execute();
	virtual void ReadActionParameters();
};

#endif