#include "VarAssign.h"
#include <sstream>

using namespace std;

VarAssign::VarAssign(Point Lcorner, string LeftHS, string RightHS) :pOutConn(NULL)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of VarAssign
	LHS = LeftHS;
	RHS = RightHS;
	for (int i = 0; i < 2; i++) {
		Connectors[i] = NULL;
	}
	connectedCnt = 2;
	UpdateStatementText();

	LeftCorner = Lcorner;
	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VarAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VarAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void VarAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool VarAssign::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return (LeftCorner.x <= clickedPoint.x && LeftCorner.y <= clickedPoint.y &&
		clickedPoint.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		clickedPoint.y <= LeftCorner.y + UI.ASSGN_HI);
}
void VarAssign::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void VarAssign::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** VarAssign::returnConnectors()
{
	return Connectors;
}

int VarAssign::getConnCnt()
{
	return this->connectedCnt;
}

char VarAssign::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char VarAssign::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool VarAssign::IsOutletFull()
{
	return pOutConn != NULL;
}
VarAssign::~VarAssign()
{

}
//This function should be called when LHS or RHS changes
void VarAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}