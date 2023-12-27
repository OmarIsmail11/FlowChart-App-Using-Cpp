#include "Cut.h"
#include "Delete.h"

Cut::Cut(ApplicationManager* pManager) : Action(pManager) {};
void Cut::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (SelectedStatetment == NULL)
	{
		return;
	}
	pManager->SetClipboard(SelectedStatetment);
	pOut->PrintMessage("You selected a statement to be cut!");
	pManager->DeleteStatement(stat); //delete the Statement
}

void Cut::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	this->SelectedStatetment = this->pManager->GetSelectedStatement();
	if (SelectedStatetment == NULL)
	{
		pOut->PrintMessage("You didn't select a statement to be cut!");
		return;
	}
	stat = pManager->GetSelectedStatement();
	slctedConn = pManager->GetSelectedConn();
	if (stat == NULL && slctedConn == NULL) //if there is no slected stat or conn then stop
	{ 
		return;
	}
	pOut->ClearStatusBar();
}
