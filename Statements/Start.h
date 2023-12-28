#ifndef START_H
#define START_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Start : public Statement
{
private:
	Connector* Connectors[2];//put the connector in array
	Connector* pOutConn;	//Value Assignment Stat. has one Connector to next statement
	Connector* pInConn;	//Value Assignment Stat. has one Connector to next statement


	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point middletop; //the middle top point of the statement block.

	virtual void UpdateStatementText();

public:
	Start(Point middletop);
	Start(Start* start, Point position);

	virtual void Draw(Output* pOut) const;

	virtual bool IsPointInMe(Point clickedPoint);

	virtual void SetConnectorOut(Connector* cn);
	virtual void SetConnectorIn(Connector* cn);

	virtual Connector** returnConnectors();
	virtual int getConnCnt();

	virtual char returnPointIn(Point& pIn); //retrun the inlit Point
	virtual char returnPointOut(Point& pOut); // Return the Outlet Point location
	virtual bool IsOutletFull(); //Check if the Statment already have Outlet connetor
	virtual bool isThereInlet(); //Check if the Statment already have Outlet connetor

	~Start();
};

#endif