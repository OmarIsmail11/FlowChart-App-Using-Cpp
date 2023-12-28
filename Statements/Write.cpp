#include "Write.h"
#include <sstream>

using namespace std;

Write::Write(Point Lcorner, string Variable) :pOutConn(NULL),Statement(ITM_WRITE)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of Write
	this->Variable = Variable;

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

string Write::GetVariable()
{
	return Variable;
}

Write::Write(Write* write, Point position) :pOutConn(NULL), Statement(ITM_WRITE)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of Write
	this->Variable = write->Variable;

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

void Write::SetVariable(const string& V)
{
	this->Variable = V;
	UpdateStatementText();
}




void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawInput(LeftCorner, UI.READ_WRITE_WIDTH, UI.READ_WRITE_HI, Text, Selected);

}

bool Write::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return (LeftCorner.x <= clickedPoint.x && LeftCorner.y <= clickedPoint.y &&
		clickedPoint.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		clickedPoint.y <= LeftCorner.y + UI.ASSGN_HI);
}
void Write::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void Write::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** Write::returnConnectors()
{
	return Connectors;
}

int Write::getConnCnt()
{
	return this->connectedCnt;
}

char Write::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char Write::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool Write::IsOutletFull()
{
	return pOutConn != NULL;
}
Write::~Write()
{

}
//This function should be called when LHS or RHS changes
void Write::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << Variable;
	Text = T.str();
}