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
		
	if (Position.y >= UI.StatusBarHeight || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		pManager->GetOutput()->PrintMessage("YOU HAVE TO PUT IT IN THE DRAW AREA!!!");
		return;
	}
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH/2;
	Corner.y = Position.y ;

	ValueAssign *pAssign = new ValueAssign(Corner, LHS, RHS);

	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

