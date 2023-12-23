#include "End.h"
#include <sstream>

using namespace std;

End::End(Point middletop):pOutConn(NULL)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of VarAssign
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


void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawEnd(middletop, UI.START_END_WIDTH, UI.START_END_HI, Selected);

}

bool End::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return (middletop.x <= clickedPoint.x && middletop.y <= clickedPoint.y &&
		clickedPoint.x <= middletop.x + UI.ASSGN_WDTH &&
		clickedPoint.y <= middletop.y + UI.ASSGN_HI);
}
void End::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void End::SetConnectorOut(Connector* cn)
{
	pOutConn = cn;
	Connectors[0] = pOutConn;
}

Connector** End::returnConnectors()
{
	return Connectors;
}

int End::getConnCnt()
{
	return this->connectedCnt;
}

char End::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char End::returnPointOut(Point& pOut)
{
	pOut = Outlet;
	return 'D';
}
bool End::IsOutletFull()
{
	return pOutConn != NULL;
}
End::~End()
{

}
//This function should be called when LHS or RHS changes
void End::UpdateStatementText()
{

}