#include "Validate.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Validate::Validate(ApplicationManager *pManager):Action(pManager){}

void Validate::ReadActionParameters()
{
}

void Validate::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("AY EBN KLB");
	switch (pManager->Validation()) {
	case MultiOrNoStart:
		pOut->PrintMessage("Error! FlowChart should have at least and at most one start statement.");
		return;
	case MultiOrNoEnd:
		pOut->PrintMessage("Error! FlowChart should have at least and at most one End statement.");
		return;
	case FreeState:
		pOut->PrintMessage("Error! All Statement should be connected from start to end");
		return;
	case StartNoIn:
		pOut->PrintMessage("Errror! Start can't Have Inlet Connector");
		return;
	case VarNotFound:
		pOut->PrintMessage("Errror! Missing variable");
		return;
	case OK:
		pOut->PrintMessage("There is No Errors.");
		return;
	}
}
