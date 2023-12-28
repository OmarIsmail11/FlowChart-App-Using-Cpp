#ifndef READ_H
#define READ_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Read : public Statement
{
private:
	string Variable;	//Left Handside of the assignment (name of a variable)
	
	Connector* Connectors[2];//put the connector in array
	Connector* pOutConn;	//Value Assignment Stat. has one Connector to next statement
	Connector* pInConn;	//Value Assignment Stat. has one Connector to next statement

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Read(Point Lcorner, string Variable);
	Read(Read* read, Point point);

	string GetVariable();
	void SetVariable(const string& V);

	virtual void Draw(Output* pOut) const;

	virtual bool IsPointInMe(Point clickedPoint);

	virtual void SetConnectorOut(Connector* cn);
	virtual void SetConnectorIn(Connector* cn);

	virtual Connector** returnConnectors();
	virtual int getConnCnt();

	virtual char returnPointIn(Point& pIn); //retrun the inlit Point
	virtual char returnPointOut(Point& pOut); // Return the Outlet Point location
	virtual bool IsOutletFull(); //Check if the Statment already have Outlet connetor

	~Read();
};

#endif