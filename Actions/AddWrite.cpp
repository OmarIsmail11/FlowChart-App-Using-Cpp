#include "AddWrite.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddWrite::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();

	Output* pOut = pManager->GetOutput();
	if (pManager->GetStatement(Position)) {
		pOut->PrintMessage("Sorry it will overLab on another statment.");
		return;
	}
	
	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	while (Position.y >= (UI.height - UI.ToolBarHeight) || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_WRITE && Position.x <= UI.MenuItemWidth * (1 + ADD_WRITE)) //if the user want to cancel he can click on the toolbar
			return;
		Pause(100);//wait before show this mesage to make it not apearing as freezed give more dynamicaly
		pManager->GetOutput()->PrintMessage("this region is not allowed put it in drwing area!!");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please Enter Variable Name then press Enter");
	this->variable = pIn->GetVariable(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddWrite::Execute()
{
	ReadActionParameters();
		
	if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_WRITE && Position.x <= UI.MenuItemWidth * (1 + ADD_WRITE)) //if the user want to cancel he can click on the toolbar
		return;

	//Calculating left corner of assignement statement block


	Write*pAssign = new Write(Position, variable);

	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

