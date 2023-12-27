#include "Start.h"
#include <sstream>

using namespace std;

Start::Start(Point middletop):pOutConn(NULL),Statement(ITM_START)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of VarAssign
	this->ID = 0;
	for (int i = 0; i < 2; i++) {
		Connectors[i] = NULL;
	}
	connectedCnt = 2;
	UpdateStatementText();

	this->middletop = middletop;
	Inlet.x = middletop.x+ UI.START_END_WIDTH/2;
	Inlet.y = middletop.y;

	Outlet.x = Inlet.x;
	Outlet.y = middletop.y + UI.START_END_HI;
	//No connectors yet
}


void Start::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawStart(middletop, UI.START_END_WIDTH, UI.START_END_HI, Selected);

}

bool Start::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return (middletop.x <= clickedPoint.x && middletop.y <= clickedPoint.y &&
		clickedPoint.x <= middletop.x + UI.ASSGN_WDTH &&
		clickedPoint.y <= middletop.y + UI.ASSGN_HI);
}
void Start::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void Start::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** Start::returnConnectors()
{
	return Connectors;
}

int Start::getConnCnt()
{
	return this->connectedCnt;
}

char Start::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char Start::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool Start::IsOutletFull()
{
	return pOutConn != NULL;
}
Start::~Start()
{

}
//This function should be called when LHS or RHS changes
void Start::UpdateStatementText()
{

}