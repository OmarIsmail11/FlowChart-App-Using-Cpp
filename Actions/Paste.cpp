#include "Paste.h"
#include "Action.h"

Paste::Paste(ApplicationManager* pManager) :Action(pManager) {};
void Paste::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetClipboard() == NULL)
	{
		pOut->PrintMessage("You didn't select a statement to be copied!");
		return;
	}


	ReadActionParameters();
	Output* pOut =pManager->GetOutput();

}

void Paste::ReadActionParameters()
{

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();


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
}
