#include "Statement.h"

Statement::Statement(int Type):StateType(Type)
{ 
	//TODO: set the ID with a unique value
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

