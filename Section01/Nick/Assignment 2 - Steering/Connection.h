/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Node;

class Connection : public Trackable
{
public:
	Connection( Node* pFrom, Node* pTo, float cost );
	~Connection();

	inline Node* getFromNode() const { return mpFrom; };
	inline Node* getToNode() const { return mpTo; };
	inline float getCost() const { return mCost; };

private:
	Node* mpFrom;
	Node* mpTo;
	float mCost;
};