#include "AddValueAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddValueAssign::AddValueAssign(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddValueAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	while (Position.y >= (UI.height - UI.ToolBarHeight) || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_VALUE_ASSIGN && Position.x <= UI.MenuItemWidth * (1 + ADD_VALUE_ASSIGN)) //if the user want to cancel he can click on the toolbar
			return;
		Pause(100);//wait before show this mesage to make it not apearing as freezed give more dynamicaly
		pManager->GetOutput()->PrintMessage("this region is not allowed put it in drwing area!!");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please Enter Variable Name then press Enter: ");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Please Enter the "+ LHS + " Value then press Enter : ");
	RHS = pIn->GetValue(pOut);
	
	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddValueAssign::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (pManager->GetStatement(Position)) {
		pOut->PrintMessage("Sorry it will overLab on another statment.");
		return;
	}
	if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_VALUE_ASSIGN && Position.x <= UI.MenuItemWidth * (1 + ADD_VALUE_ASSIGN)) //if the user want to cancel he can click on the toolbar
		return;
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH/2;
	Corner.y = Position.y ;

	pair<string, double>* var = new pair<string, double>(LHS,RHS);

	ValueAssign *pAssign = new ValueAssign(Corner, LHS, RHS);

	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
	pManager->AddVariable(pAssign);
}

