#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"

//Base class for all Statements
class Statement
{
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	int connectedCnt;
	const int StateType;

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement(int Type);
	void SetSelected(bool s);
	bool IsSelected() const;

	void SetStatementID(int id);
	int GetStatementID();

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	
	virtual bool IsPointInMe(Point clickedPoint) = 0; //this function checks if the entered point is in it's area

	virtual void SetConnectorOut(Connector* cn) = 0; //set the outlet connector to be traked
	virtual void SetConnectorIn(Connector* cn) = 0;

	virtual Connector** returnConnectors() = 0; // return all connected connectors for deletion
	virtual int getConnCnt()= 0;//the coun of connected connectors
	
	virtual char returnPointIn(Point &pIn) = 0;//retrun the inlit Point and the connectors arrow direction
	virtual char returnPointOut(Point& pOut) = 0; // Return the Outlet Point location and the way to go out (ex : from right down or left)

	
	virtual bool IsOutletFull() = 0; //Add connector to the Statment

	int GetStatementType();//return the statement type froms it's item enum




};

#endif