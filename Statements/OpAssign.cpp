#include "OpAssign.h"
#include <sstream>

using namespace std;

OpAssign::OpAssign(Point Lcorner, string LeftHS, string VarName, string Op,double nomb) :pOutConn(NULL),Statement(ITM_OPER_ASSIGN)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of VarAssign
	LHS = LeftHS;
	this->VarName = VarName;
	Operator = Op;
	nom = nomb;
	for (int i = 0; i < 2; i++) {
		Connectors[i] = NULL;
	}
	connectedCnt = 2;
	UpdateStatementText();

	LeftCorner = Lcorner;
	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

OpAssign::OpAssign(OpAssign* opassign, Point position) :Statement(ITM_OPER_ASSIGN)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of VarAssign
	this->LHS = opassign->LHS;
	this->VarName = opassign->VarName;
	this->Operator = opassign->Operator;
	this->nom = opassign->nom;
	for (int i = 0; i < 2; i++) {
		Connectors[i] = NULL;
	}
	connectedCnt = 2;
	UpdateStatementText();

	LeftCorner = position;
	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}


void OpAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool OpAssign::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return (LeftCorner.x <= clickedPoint.x && LeftCorner.y <= clickedPoint.y &&
		clickedPoint.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		clickedPoint.y <= LeftCorner.y + UI.ASSGN_HI);
}
void OpAssign::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void OpAssign::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** OpAssign::returnConnectors()
{
	return Connectors;
}

int OpAssign::getConnCnt()
{
	return this->connectedCnt;
}

char OpAssign::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char OpAssign::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool OpAssign::IsOutletFull()
{
	return pOutConn != NULL;
}
OpAssign::~OpAssign()
{

}
//This function should be called when LHS or RHS changes
void OpAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << VarName<<Operator<<nom;
	Text = T.str();
}