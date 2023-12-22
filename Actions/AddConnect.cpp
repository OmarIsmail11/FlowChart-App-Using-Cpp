#include "AddConnect.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddConnect::AddConnect(ApplicationManager *pManager):Action(pManager){}

void AddConnect::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click on the start Point");
	pIn->GetPointClicked(pointOut);
	Statement* StOut = pManager->GetStatement(pointOut); // get the statement did the user clicked on

	while (StOut == NULL) {//If the User didn't click on any statment he have to choose or to cancel

		if (pointOut.y <= 50 && pointOut.x >= UI.MenuItemWidth * ADD_CONNECTOR && pointOut.x <= UI.MenuItemWidth * (1 + ADD_CONNECTOR)) //if the user want to cancel he can click on the toolbar
			return;
		
		pOut->PrintMessage("Error you have to choose a statment try again or click on the Icon again to cancel.");
		pIn->GetPointClicked(pointOut);
		StOut = pManager->GetStatement(pointOut);
		pOut->ClearStatusBar();
	}

	pOut->PrintMessage("Click on the End Point");
	pIn->GetPointClicked(pointIn);
	pOut->ClearStatusBar();
	Statement*  StIn = pManager->GetStatement(pointIn);// get the statement did the user clicked on

	while (StIn == NULL) {//If the User didn't click on any statment he have to choose or to cancel

		if (pointIn.y <= 50 && pointIn.x >= UI.MenuItemWidth * ADD_CONNECTOR && pointIn.x <= UI.MenuItemWidth * (1 + ADD_CONNECTOR)) //if the user want to cancel he can click on the toolbar
			return;

		pOut->PrintMessage("Error you have to choose a statment try again or click on the Icon again to cancel.");
		pIn->GetPointClicked(pointIn);
		StIn = pManager->GetStatement(pointIn);
		pOut->ClearStatusBar();
	}
}

//Execute the action
void AddConnect::Execute()
{
	ReadActionParameters();

	Output* pOut = pManager->GetOutput();
	Statement* StOut = pManager->GetStatement(pointOut); // get outlet Statement 
	Statement* StIn = pManager->GetStatement(pointIn);// get the inlet Statement

	if (pointIn.y < 50 || pointOut.y < 50)
		return;

	if (StOut == StIn) {
		pOut->PrintMessage("Sorry you can't connect to self statement");
		return;
	}
	if (StOut->IsOutletFull()){
		pOut->PrintMessage("Error!! this Statment Already \
			Have outlet connector.");//checksif the Statment not already have outlet
		return;																		
	}
	
	 //update the location where the connector will out from.
	char outletDir = StOut->returnPointOut(pointOut);//update the location where the connector will in to. and return the arrow direction
	pointIn = pointOut;

	char arrowDir = StIn->returnPointIn(pointIn);//update the location where the connector will in to. and return the arrow direction
	
	Connector* Cadd = new Connector(StOut, StIn, pointOut, pointIn, arrowDir, outletDir);
	pManager->AddConnector(Cadd);

	StOut->SetConnectorOut(Cadd); //make the statment point to connector out from it
	StIn->SetConnectorIn(Cadd); //make the statment point to connector enter to it
}
