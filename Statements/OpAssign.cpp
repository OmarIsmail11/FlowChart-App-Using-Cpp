#include "OpAssign.h"
#include <sstream>

using namespace std;



OpAssign::OpAssign(Point Lcorner, string LeftHS, string RHS1, string Op, string RHS2) :pOutConn(NULL), Statement(ITM_OPER_ASSIGN)
{
	this->LHS = LeftHS;
	this->RHS1 = RHS1;
	this->Operator = Op;
	this->RHS2 = RHS2;
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

OpAssign::OpAssign(OpAssign* opassign, Point position) :pOutConn(NULL) ,Statement(ITM_OPER_ASSIGN)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of VarAssign
	this->LHS = opassign->LHS;
	this->RHS1 = opassign->RHS1;
	this->Operator = opassign->Operator;
	this->RHS2 = opassign->RHS2;
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
	T << LHS << " = " << RHS1 <<Operator<< RHS2;
	Text = T.str();
}


string OpAssign::getLHS() {
	return LHS;
}
string OpAssign::getRHS1() {
	return RHS1;
}
string OpAssign::getRHS2() {
	return RHS2;
}