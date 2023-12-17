#include "Delete.h"
#include "AddConnect.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Delete::Delete(ApplicationManager *pManager):Action(pManager),stat(NULL), slctedConn(NULL)
{}

void Delete::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	stat = pManager->GetSelectedStatement();
	slctedConn = pManager->GetSelectedConn();
	
	if (stat == NULL && slctedConn == NULL) {//if there is no slected stat or conn then stop
		Confirmation = "NO";
		pOut->PrintMessage("there is no selction.");
		return;
	}

	pOut->PrintMessage("Are you Sure you Want to delet that? Write \"CONFIRM\" to complete \"NO\" to discard");
	Confirmation = pIn->GetString(pOut);

	while (Confirmation != "NO" && Confirmation != "CONFIRM") {
		pOut->PrintMessage("Error!!( " + Confirmation + " ) isn't  \"CONFIRM\" or \"NO\" do it again: ");
			Confirmation = pIn->GetString(pOut);
	}
	pOut->ClearStatusBar();
}

//Execute the action
void Delete::Execute()
{
	ReadActionParameters();
	if (Confirmation == "NO")//if terminate if user entered no or no selction
		return;

	if (stat != NULL) {
		Connector** StatConnArr = stat->returnConnectors();
		pManager->SetSelectedStatement(NULL);
		for (int i = 0; i < stat->getConnCnt(); i++) {

			if (StatConnArr[i] != NULL) { //Checks if the Statment connected to anny Statment
				Connector* DelMe = StatConnArr[i]; //create tempraory pointer to connector to delete what inside it
				DelMe->getSrcStat()->SetConnectorOut(NULL);//makes the src free of connectors
				pManager->DeleteConn(DelMe); //delete the connected connectors "no free conn remeber?"
			}
		}
		pManager->DeleteStatement(stat); //delete the Statement
	}
	else {

		pManager->SetSelectedConn(NULL);//free the selection
		slctedConn->getSrcStat()->SetConnectorOut(NULL); //makes the src free of connectors
		pManager->DeleteConn(slctedConn); //delete the connecter

	}
	stat = NULL;//this line because to make the object capable of deletion
	slctedConn = NULL;
}
