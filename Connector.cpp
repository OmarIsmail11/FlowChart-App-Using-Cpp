#include "Connector.h"
Connector::Connector(Statement* Src, Statement* Dst, Point start, Point end,char arrowDir ):Selected(false),Start(start),End(end), arrowDir(arrowDir), SrcStat(Src), DstStat(Dst)
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	Start = P;	}

Point Connector::getStartPoint()
{	return Start;	}

void Connector::setEndPoint(Point P)
{	End = P;	}

Point Connector::getEndPoint()
{	return End;	}

void Connector::Draw(Output* pOut) const
{
	pOut->DrawConnector(Start,End, arrowDir, Selected);
}

bool Connector::IsPointOnMe(Point p)
{
	int x2 = Start.x;

	if (arrowDir == 'L') {
		x2 = Start.x + 60;
	}
	else if (arrowDir == 'R') {
		x2 = Start.x - 60;
	}
	switch (Start.y < End.y) {
	case 1:
		return ((Start.x < p.x && p.x <= End.x) || (Start.x >= p.x && p.x >= End.x)) //this algrothim to follow the line and return if
			&& Start.y + ((End.y - Start.y) / 10) - 5 <= p.y && Start.y + ((End.y - Start.y) / 10) + 5 >= p.y//you clicked on it 
			||																			//or a region near it and retrun true
			(End.x - 5 <= p.x && p.x <= End.x + 5)
			&& Start.y + ((End.y - Start.y) / 10) <= p.y && End.y > p.y
			||
			(Start.x - 5 <= p.x && p.x <= Start.x + 5)
			&& Start.y + ((End.y - Start.y) / 10) >= p.y && Start.y < p.y;
	case 0:
		return ((Start.x < p.x && p.x <= x2) || (Start.x >= p.x && p.x >= x2)) //this algrothim to follow the line and return if
			&& Start.y - 5 >= p.y && Start.y + 5 <= p.y//you clicked on it 
			||																			//or a region near it and retrun true
			(x2 - 5 <= p.x && p.x <= x2 + 5)
			&& Start.y>= p.y && End.y <= p.y
			||
			(x2 <= p.x && p.x <= End.x)
			&& End.y-5 >= p.y && End.y-5 <= p.y;
	}
}

void Connector::SetSelected(bool s)
{
	Selected = s;
}

bool Connector::IsSelected() const
{
	return Selected;
}


