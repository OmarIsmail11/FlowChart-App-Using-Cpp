#include "Read.h"
#include <sstream>

using namespace std;

Read::Read(Point Lcorner, string Variable) :pOutConn(NULL),Statement(ITM_READ)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of Read
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

Read::Read(Read* read, Point point) : Statement(ITM_READ)
{
	this->Variable = read->Variable;

	for (int i = 0; i < 2; i++) {
		Connectors[i] = NULL;
	}
	connectedCnt = 2;
	UpdateStatementText();

	LeftCorner = point;
	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

string Read::GetVariable()
{
	return Variable;
}

void Read::SetVariable(const string& V)
{
	this->Variable = V;
	UpdateStatementText();
}




void Read::Draw(Output* pOut) const
{
	pOut->DrawInput(LeftCorner, UI.READ_WRITE_WIDTH, UI.READ_WRITE_HI, Text, Selected);

}

bool Read::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the the Read return true
	return (LeftCorner.x <= clickedPoint.x && LeftCorner.y <= clickedPoint.y &&
		clickedPoint.x <= LeftCorner.x + UI.READ_WRITE_WIDTH &&
		clickedPoint.y <= LeftCorner.y + UI.READ_WRITE_HI);
}
void Read::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void Read::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** Read::returnConnectors()
{
	return Connectors;
}

int Read::getConnCnt()
{
	return this->connectedCnt;
}

char Read::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char Read::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool Read::IsOutletFull()
{
	return pOutConn != NULL;
}
Read::~Read()
{

}
//This function should be called when LHS or RHS changes
void Read::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << Variable;
	Text = T.str();
}