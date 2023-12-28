#include "AddCond.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddCond::AddCond(ApplicationManager *pAppManager):Action(pAppManager)
{}

void AddCond::ReadActionParameters()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	
	//Read the (Position) parameter
	pOut->PrintMessage("End Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();		
	while (Position.y >= (UI.height - UI.ToolBarHeight) || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_CONDITION && Position.x <= UI.MenuItemWidth * (1 + ADD_CONDITION)) //if the user want to cancel he can click on the toolbar
			return;
		Pause(100);//wait before show this mesage to make it not apearing as freezed give more dynamicaly
		pManager->GetOutput()->PrintMessage("this region is not allowed put it in drwing area!!");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
	pOut->PrintMessage("Enter the Left Hand side Comparsion");
	LHS = pIn->GetString(pOut);
	while (ValueOrVariable(LHS) == 2) {
		pOut->PrintMessage(" Error! Enter valid Varible or value");
		LHS = pIn->GetString(pOut);
	}
	pOut->PrintMessage("Enter the Comparsion Operator");
	CompOper = pIn->GetCompOperator(pOut);

	pOut->PrintMessage("Enter the right Hand side Comparsion");
	RHS = pIn->GetString(pOut);
	while (ValueOrVariable(RHS) == 2) {
		pOut->PrintMessage(" Error! Enter valid Varible or value");
		RHS = pIn->GetString(pOut);
	}


	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddCond::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (pManager->GetStatement(Position)) {
		pOut->PrintMessage("Sorry it will overLab on another statment.");
		return;
	}
		
	if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_CONDITION && Position.x <= UI.MenuItemWidth * (1 + ADD_CONDITION)) //if the user want to cancel he can click on the toolbar
		return;

	//Calculating left corner of assignement statement block
	Point TopVertix;
	TopVertix.x = Position.x - UI.START_END_WIDTH/2;
	TopVertix.y = Position.y ;

	Condtion* pstart = new Condtion(TopVertix, LHS, CompOper, RHS);

	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pstart); // Adds the created statement to application manger's statement list
}

