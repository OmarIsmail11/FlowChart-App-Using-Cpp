#include "AddEnd.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddEnd::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	while (Position.y >= (UI.height - UI.ToolBarHeight) || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_START && Position.x <= UI.MenuItemWidth * (1 + ADD_START)) //if the user want to cancel he can click on the toolbar
			return;
		Pause(100);//wait before show this mesage to make it not apearing as freezed give more dynamicaly
		pManager->GetOutput()->PrintMessage("this region is not allowed put it in drwing area!!");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddEnd::Execute()
{
	ReadActionParameters();
		
	if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_VAR_ASSIGN && Position.x <= UI.MenuItemWidth * (1 + ADD_VAR_ASSIGN)) //if the user want to cancel he can click on the toolbar
		return;

	//Calculating left corner of assignement statement block
	Point middletop;
	middletop.x = Position.x - UI.START_END_WIDTH/2;
	middletop.y = Position.y ;

	End*pstart= new End(middletop);

	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pstart); // Adds the created statement to application manger's statement list
}

