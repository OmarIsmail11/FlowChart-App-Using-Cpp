#ifndef OP_ASSIGN_H
#define OP_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class OpAssign : public Statement
{
private:

	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS1;	//Right Handside1 (Value)
	string RHS2;	//Right Handside2 (Value)


	string Operator;


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
	OpAssign(Point Lcorner, string LeftHS, string RHS1, string Op, string RHS2);
	OpAssign(OpAssign* opassign, Point position);

	void setLHS(const string& L);
	void setRHS(double R);
	
	string getLHS();
	string getRHS1();
	string getRHS2();

	virtual void Draw(Output* pOut) const;

	virtual bool IsPointInMe(Point clickedPoint);

	virtual void SetConnectorOut(Connector* cn);
	virtual void SetConnectorIn(Connector* cn);

	virtual Connector** returnConnectors();
	virtual int getConnCnt();

	virtual char returnPointIn(Point& pIn); //retrun the inlit Point
	virtual char returnPointOut(Point& pOut); // Return the Outlet Point location
	virtual bool IsOutletFull(); //Check if the Statment already have Outlet connetor

	~OpAssign();
};

#endif