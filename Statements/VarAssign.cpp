#include "ValueAssign.h"
#include <sstream>

using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS) :pOutConn(NULL)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
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

void ValueAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

bool ValueAssign::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return (LeftCorner.x <= clickedPoint.x && LeftCorner.y <= clickedPoint.y &&
		clickedPoint.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		clickedPoint.y <= LeftCorner.y + UI.ASSGN_HI);
}
void ValueAssign::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void ValueAssign::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** ValueAssign::returnConnectors()
{
	return Connectors;
}

int ValueAssign::getConnCnt()
{
	return this->connectedCnt;
}

char ValueAssign::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char ValueAssign::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool ValueAssign::IsOutletFull()
{
	return pOutConn != NULL;
}
ValueAssign::~ValueAssign()
{

}
//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}