#ifndef END_H
#define END_H

#include "Statement.h"

//END statement class
//The END statement
class End : public Statement
{
private:

	Connector* Connectors[2];//put the connector in array
	Connector* pOutConn;	//the connector goes out it
	Connector* pInConn;	//the connector goes out in it
	

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (End) point of the (Output) connector

	Point middletop;	//the middle top point of the statement block.

	virtual void UpdateStatementText();

public:
	End(Point middletop);
	End(End* end, Point position);


	virtual void Draw(Output* pOut) const;

	virtual bool IsPointInMe(Point clickedPoint);

	virtual void SetConnectorOut(Connector* cn);
	virtual void SetConnectorIn(Connector* cn);

	virtual Connector** returnConnectors();
	virtual int getConnCnt();

	virtual char returnPointIn(Point& pIn); //retrun the inlit Point
	virtual char returnPointOut(Point& pOut); // Return the Outlet Point location
	virtual bool IsOutletFull(); //Check if the Statment already have Outlet connetor

	~End();
};

#endif