#include "Paste.h"

Paste::Paste(ApplicationManager* pManager) :Action(pManager) {}
void Paste::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Select Point to paste.");
	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();
	while (Position.y >= (UI.height - UI.ToolBarHeight) || Position.y <= UI.ToolBarHeight || Position.x >= UI.DrawingAreaWidth) {
		if (Position.y <= 50 && Position.x >= UI.MenuItemWidth * ADD_START && Position.x <= UI.MenuItemWidth * (1 + ADD_START)) //if the user want to cancel he can click on the toolbar
			return;
		Pause(100);//wait before show this mesage to make it not apearing as freezed give more dynamicaly
		pOut->PrintMessage("this region is not allowed put it in drwing area!!");
		pIn->GetPointClicked(Position);
		pOut->ClearStatusBar();
	}
}

void Paste::Execute()
{
	Statement* CopiedState = pManager->GetClipboard();
	Output* pOut = pManager->GetOutput();


	if (!CopiedState)
	{
		pOut->PrintMessage("You didn't select a statement to be copied!");
		return;
	}

	ReadActionParameters();
	int statTyp = CopiedState->GetStatementType();

	//According to ActioType, create the corresponding action object
	switch (statTyp)
	{
	case ITM_COND:
		pManager->AddStatement(new Condtion(dynamic_cast<Condtion*>(CopiedState), Position));
		break;
	case ITM_READ:
		pManager->AddStatement(new Read(dynamic_cast<Read*>(CopiedState), Position));
		break;
	case ITM_END:
		pManager->AddStatement(new End(dynamic_cast<End*>(CopiedState), Position));
		break;
	case ITM_OPER_ASSIGN:
		pManager->AddStatement(new OpAssign(dynamic_cast<OpAssign*>(CopiedState), Position));
		break;
	case ITM_START:
		pManager->AddStatement(new Start(dynamic_cast<Start*>(CopiedState), Position));
		break;
	case ITM_VALUE_ASSIGN:
		pManager->AddStatement(new ValueAssign(dynamic_cast<ValueAssign*>(CopiedState), Position));
		break;
	case ITM_VAR_ASSIGN:
		pManager->AddStatement(new VarAssign(dynamic_cast<VarAssign*>(CopiedState), Position));
		break;
	case ITM_WRITE:
		pManager->AddStatement(new Write(dynamic_cast<Write*>(CopiedState), Position));
		break;
	} 
}


