#include "ApplicationManager.h"
#include "Actions\AddStart.h"
#include "Actions\AddRead.h"
#include "Actions\AddWrite.h"
#include "Actions\Validate.h"
#include "Actions\Cut.h"
#include "Actions\Copy.h"
#include "Actions\paste.h"
#include "Actions\AddValueAssign.h"
#include "Actions\AddVarAssign.h"
#include "Actions\AddOperatorAssign.h"
#include "Actions\AddCond.h"
#include "Actions\Select.h"
#include "Actions\AddConnect.h"
#include "Actions\Delete.h"
#include "Actions\AddEnd.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include <iostream>
//Constructor
ApplicationManager::ApplicationManager():varcnt(0)
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	
	pSelectedStat = NULL;
	pSelectedConn = NULL;	//no Statement is selected yet

	pClipboard = NULL;
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_START:
			pAct = new AddStart(this);
			break;
			case ADD_END:
			pAct = new AddEnd(this);
			break;
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;
		case ADD_VAR_ASSIGN:
			pAct = new AddVarAssign(this);
			break;
		case ADD_OPER_ASSIGN:
			pAct = new AddOperatorAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddCond(this);
			break;

		case DEL:
			pAct = new Delete(this);

			break;	
		case COPY:
			pAct = new Copy(this);

			break;	
		case CUT:
			pAct = new Cut(this);

			break;	
		case ADD_READ:
			pAct = new AddRead(this);

			break;
		case ADD_WRITE:
			pAct = new AddWrite(this);

			break;
		case ADD_CONNECTOR:
			pAct = new AddConnect(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;	
		case PASTE:
			pAct = new Paste(this);
			break;
		case VALIDATE:
			pAct = new Validate(this);
			break;

		case SWITCH_SIM_MODE:
			pOut->CreateSimulationToolBar();
			
			break;
		case SWITCH_DSN_MODE:
			pOut->CreateDesignToolBar();
			
			break;
		case EXIT:
			///create Exit Action here
			
			break;
		
		case STATUS:
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	for (int i = 0; i < StatCount; i++)
		if (StatList[i]->IsPointInMe(P))
			return StatList[i];

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities

	return NULL;
}
void ApplicationManager::DeleteStatement(Statement* pStat)
{
	int i = 0;
	for (; i < StatCount; i++)
		if (StatList[i] == pStat)
			break;
	delete StatList[i];
	StatList[i] = NULL;

	StatList[i] = StatList[StatCount-1];
	StatList[StatCount - 1] = NULL;
	StatCount--;
}
void ApplicationManager::DeleteConn(Connector* pStat)
{
	int i = 0;
	for (; i < ConnCount; i++)
		if (ConnList[i] == pStat)
			break;

	delete ConnList[i];
	ConnList[i] = NULL;

	ConnList[i] = ConnList[ConnCount - 1];
	ConnList[ConnCount - 1] = NULL;
	ConnCount--;
}
void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;
}
Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++) {
		if (ConnList[i]->IsPointOnMe(P)) {
			return ConnList[i];
		}
	}
	return nullptr;
}
void ApplicationManager::SetSelectedConn(Connector* pStat)
{
	pSelectedConn = pStat;
}
Connector* ApplicationManager::GetSelectedConn() const
{
	return pSelectedConn;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
////////////////////////////////////////////////////////////////////
////////

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////
////////validation
RetErrors ApplicationManager::Validation()
{
	RetErrors TheReturn = OK;
	//Case many Start Statement or Or no Start
		bool multOrNoStrt = true;
		for (int i = 0; i < StatCount; i++) {
			if (dynamic_cast<Start*>(StatList[i])) {
				if (multOrNoStrt) 
					multOrNoStrt = false;
				
				else if ((dynamic_cast<Start*>(StatList[i]))->isThereInlet() != NULL)
					return StartNoIn;
				else
					multOrNoStrt = true;

			}
		}
		if (multOrNoStrt)
			return MultiOrNoStart;

	//Case many END Statement or Or no END
		bool multOrNoEnd = true;
		for (int i = 0; i < StatCount; i++) {
			if (dynamic_cast<End*>(StatList[i])) {
				if (multOrNoEnd)
					multOrNoEnd = false;
				else
					multOrNoEnd = true;

			}
		}
		if (multOrNoEnd)
			return MultiOrNoEnd;
		
	//case free Statement without connectors
		for (int i = 0; i < StatCount; i++) {
			if (!StatList[i]->IsOutletFull()) {
				return  FreeState;
			}
		}

	//valdiation for variables
		{
			

			bool found = false, enteredCondtion = false;//checks wethet it found or not and if it is not entred or enter one of if statements
			for (int i = 0; i < StatCount; i++) {
				found = false;
				enteredCondtion = false;
				if (dynamic_cast<VarAssign*>(StatList[i])) {
					string RHS = (dynamic_cast<VarAssign*>(StatList[i]))->getRHS();
							enteredCondtion = true;
					for (int j = 0; j < varcnt; j++) {
						if (RHS == variables[j]) {
							found = true;
							break;
						}

					}
				}
				else if (dynamic_cast<OpAssign*>(StatList[i])) {
					enteredCondtion = true;
					string RHS1 = (dynamic_cast<OpAssign*>(StatList[i]))->getRHS1();
					string RHS2 = (dynamic_cast<OpAssign*>(StatList[i]))->getRHS2();
					if (IsValue(RHS1) && IsValue(RHS2)) {
						found = true;
						continue;
					}
					for (int j = 0; j < varcnt; j++) {
						enteredCondtion = true;
						if (RHS1 == variables[j] || RHS2 == variables[j]) {
							found = true;
						}

					}
				}
				else if (dynamic_cast<Write*>(StatList[i])) {
					enteredCondtion = true;
					string Var = (dynamic_cast<Write*>(StatList[i]))->GetVariable();
					
					for (int j = 0; j < varcnt; j++) {
						if (Var == variables[j]) {
							found = true;
							enteredCondtion = true;
						}

					}
				}
				else if (dynamic_cast<Condtion*>(StatList[i])) {
					enteredCondtion = true;
					string LHS = (dynamic_cast<Condtion*>(StatList[i]))->getLHS();
					string RHS = (dynamic_cast<Condtion*>(StatList[i]))->getRHS();
					if ((IsValue(LHS) && IsValue(RHS))) {
						found = true;
						break;
					}
					for (int j = 0; j < varcnt; j++) {
						if (LHS == variables[j] || RHS == variables[j]) {
							found = true;
							break;
						}

					}
				}
				if (!found && enteredCondtion) {
					return VarNotFound;
				}
			}
		}
	return TheReturn;
}

void ApplicationManager::DeleteVariable(Statement* Stat)
{
	if (dynamic_cast<ValueAssign*>(Stat)) {
		string LHS = (dynamic_cast<ValueAssign*>(Stat))->getLHS();
		for (int i = 0; i < StatCount; i++) {
			if (LHS == variables[i]) {
				variables[i] = "";
				variables[i] = variables[(varcnt - 1)];
				varcnt--;
				return;
			}
		}
	}
	else if (dynamic_cast<VarAssign*>(Stat)) {
		string LHS = (dynamic_cast<VarAssign*>(Stat))->getLHS();
		for (int i = 0; i < StatCount; i++) {
			if (LHS == variables[i]) {
				variables[i] = "";
				variables[i] = variables[(varcnt - 1)];
				varcnt--;
				return;
			}
		}
	}
	else if (dynamic_cast<OpAssign*>(Stat)) {
			string LHS = (dynamic_cast<OpAssign*>(Stat))->getLHS();
			for (int i = 0; i < StatCount; i++) {
				if (LHS == variables[i]) {
					variables[i] = "";
					variables[i] = variables[(varcnt - 1)];
					varcnt--;
					return;
				}
			}
		}
		else if (dynamic_cast<Read*>(Stat)) {
			string Var = (dynamic_cast<Read*>(Stat))->GetVariable();
			for (int i = 0; i < StatCount; i++) {
				if (Var == variables[i]) {
					variables[i] = "";
					variables[i] = variables[(varcnt - 1)];
					varcnt--;
					return;
				}
			}
		}
	return;
	}

void ApplicationManager::AddVariable(Statement* Stat)
{
	if (dynamic_cast<ValueAssign*>(Stat)) {
		variables[varcnt++] = (dynamic_cast<ValueAssign*>(Stat))->getLHS();
	}
	else if (dynamic_cast<VarAssign*>(Stat))
		variables[varcnt++] = (dynamic_cast<VarAssign*>(Stat))->getLHS();
	else if (dynamic_cast<OpAssign*>(Stat))
		variables[varcnt++] = (dynamic_cast<OpAssign*>(Stat))->getLHS();
	else if (dynamic_cast<Read*>(Stat))
		variables[varcnt++] = (dynamic_cast<Read*>(Stat))->GetVariable();
}


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}
