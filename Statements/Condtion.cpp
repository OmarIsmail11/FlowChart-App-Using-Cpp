#include "Condtion.h"
#include <sstream>

using namespace std;

Condtion::Condtion(Point TVertix, string LeftHS, string Oper, string RightHS):Statement(ITM_COND)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of Condtion
	LHS = LeftHS;
	CompOperator = Oper;
	RHS = RightHS;

	R.pOutConn = NULL;
	L.pOutConn = NULL;
	pInConn = NULL;
	connectedCnt = 3;
	counter = 0;
	for (int i = 0; i < 3; i++) {
		Connectors[i] = NULL;
	}
	this->
	UpdateStatementText();

	TopVertix = TVertix;
	//No connectors yet

	Inlet.x = TVertix.x;
	Inlet.y = TVertix.y;

	OutletR.x = TVertix.x + UI.COND_WDTH/2;
	OutletR.y = TVertix.y + UI.COND_HI/2;

	OutletL.x = TVertix.x - UI.COND_WDTH / 2;
	OutletL.y = TVertix.y + UI.COND_HI / 2;
	
}

Condtion::Condtion(Condtion* CopiedCond, Point TVertix) :Statement(ITM_COND)
{
	LHS = CopiedCond->LHS;
	CompOperator = CopiedCond->CompOperator;
	RHS = CopiedCond->RHS;
	R.pOutConn = NULL;
	L.pOutConn = NULL;
	pInConn = NULL;
	connectedCnt = 3;
	counter = 0;

	for (int i = 0; i < 3; i++) {
		Connectors[i] = NULL;
	}
	this->UpdateStatementText();

	TopVertix = TVertix;
	//No connectors yet

	Inlet.x = TVertix.x;
	Inlet.y = TVertix.y;
	OutletR.x = TVertix.x + UI.COND_WDTH / 2;
	OutletR.y = TVertix.y + UI.COND_HI / 2;
	OutletL.x = TVertix.x - UI.COND_WDTH / 2;
	OutletL.y = TVertix.y + UI.COND_HI / 2;
}

void Condtion::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void Condtion::setCompOper(const string& Oper)
{
	this->CompOperator = Oper;
	UpdateStatementText();
}

void Condtion::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}


void Condtion::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement
	pOut->DrawCondtionalStat(TopVertix, UI.COND_WDTH, UI.COND_HI, Text, Selected);
	
}

bool Condtion::IsPointInMe(Point clickedPoint)
{
	//if the point in the area of the assign return true
	return ((TopVertix.x - 0.5*UI.COND_WDTH) <= clickedPoint.x && TopVertix.y <= clickedPoint.y &&
		clickedPoint.x <= (TopVertix.x + 0.5 * UI.COND_WDTH) &&
		clickedPoint.y <= TopVertix.y + UI.COND_HI);
}
void Condtion::SetConnectorIn(Connector* cn)
{
	pInConn = cn;
	Connectors[1] = pInConn;
}

void Condtion::SetConnectorOut(Connector* cn)
{
	if (cn == NULL) {
		if (Connectors[0])
			 {
			L.pOutConn == cn;
			Connectors[2] = L.pOutConn;
		}
		else
		{
			R.pOutConn == cn;
			Connectors[0] = R.pOutConn;
		}
		return;
	}
	if (TopVertix.x > WhichConnectorOut.x) {
		L.pOutConn = cn;
		return;
		Connectors[2] = cn;
	}
	R.pOutConn = cn;
		Connectors[0] = cn;
}

Connector** Condtion::returnConnectors()
{
	return Connectors;
	}

int Condtion::getConnCnt()
{
	return this->connectedCnt;
}

char Condtion::returnPointIn(Point& pIn)
{
	pIn = Inlet;
	return 'U';
}
char Condtion::returnPointOut(Point& pOut)
{
	if (TopVertix.x > pOut.x) {
		pOut = OutletL;
		WhichConnectorOut = OutletL;
		return 'L';
	}
	pOut = OutletR;
	WhichConnectorOut = OutletR;
	return 'R';
}
bool Condtion::IsOutletFull()
{
	if (R.pOutConn &&  L.pOutConn)
		return true;

	return false;
}
Condtion::~Condtion()
{
	R.pOutConn = NULL;
	L.pOutConn = NULL;
}
//This function should be called when LHS or RHS changes
void Condtion::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" "<< this->CompOperator<<" "<< RHS;
	Text = T.str();	 
}

string Condtion::getLHS() {
	return LHS;
}
string Condtion::getRHS() {
	return RHS;
}