#include "Statement.h"

Statement::Statement(int Type):StateType(Type)
{ 
	
	Text = "";
	Selected = false;		
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

void Statement::SetStatementID(int id)
{
	ID = id;
}

int Statement::GetStatementID()
{
	return ID;
}


int Statement::GetStatementType()
{
	return StateType;
}
