#include "AddOperatorAssign.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddOperatorAssign::AddOperatorAssign(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddOperatorAssign::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	while (Position.y >= (UI.height - UI.ToolBarHeight) || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_OPER_ASSIGN && Position.x <= UI.MenuItemWidth * (1 + ADD_OPER_ASSIGN)) //if the user want to cancel he can click on the toolbar
			return;
		Pause(100);//wait before show this mesage to make it not apearing as freezed give more dynamicaly
		pManager->GetOutput()->PrintMessage("this region is not allowed put it in drwing area!!");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please Enter Variable Name then press Enter: ");
	LHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Please Enter "+ LHS + "the other variable then press Enter : ");
	varName = pIn->GetVariable(pOut);
	pOut->PrintMessage("Please Enter "+ LHS + "the other arithmatic Op then press Enter : ");
	Operator = pIn->GetArithOperator(pOut);
	pOut->PrintMessage("Please Enter "+ LHS + "the other arithmatic Op then press Enter : ");
	nom = pIn->GetValue(pOut);
	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddOperatorAssign::Execute()
{
	ReadActionParameters();
		
	if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_VAR_ASSIGN && Position.x <= UI.MenuItemWidth * (1 + ADD_VAR_ASSIGN)) //if the user want to cancel he can click on the toolbar
		return;

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH/2;
	Corner.y = Position.y ;

	OpAssign*pAssign = new OpAssign(Corner, LHS, varName,Operator,nom);

	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

