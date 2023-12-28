#ifndef CONDTION_H
#define CONDTION_H

#include "Statement.h"

//Condtion statement class
//The Condtion statement cmpare between 2 variables of values or both
class Condtion : public Statement
{
private:


	struct pOutConn {
	public:
		Connector* pOutConn;
	};
	Point WhichConnectorOut;

	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Value)
	string CompOperator;	//Right Handside (Value)
	int counter;
	Connector* Connectors[3];//put the connector in array


	pOutConn R;
	pOutConn L;
	
	Connector *pInConn;	//Value Assignment Stat. has one Connector to next statement
	                      

	Point Inlet;	//A point where connections enters this statement 
	                //It's used as the (End) point of the (Input) connectors
	Point OutletR;	//A point a connection leaves this statement right
	Point OutletL;	//A point a connection leaves this statement left
	                //It's used as the (Start) point of the (Output) connector
	Point TopVertix;	// to vertix of the statement block.

	virtual void UpdateStatementText();
	
public:
	Condtion(Point TVertix, string LeftHS, string Oper, string RightHS);
	Condtion(Condtion* CopiedCond, Point TVertix);

	void setLHS(const string &L);
	void setCompOper(const string &Oper);
	void setRHS(const string &R);

	virtual void Draw(Output* pOut) const;

	virtual bool IsPointInMe(Point clickedPoint);

	virtual void SetConnectorOut(Connector* cn);
	virtual void SetConnectorIn(Connector* cn);

	virtual Connector** returnConnectors();
	virtual int getConnCnt();

	virtual char returnPointIn(Point& pIn); //retrun the inlit Point
	virtual char returnPointOut(Point& pOut); // Return the Outlet Point location
	virtual bool IsOutletFull(); //Check if the Statment already have Outlet connetor


	string getLHS();
	string getRHS();

	~Condtion();
};

#endif