/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once


const int BAD_NODE_ID = -1;
#define NODE_ID int

class Node : public Trackable
{
public:
	Node( const NODE_ID& id );
	Node();
	~Node();

	void setPosition(Vector2D& position);
	Vector2D getPosition() const { return mPosition; }
	float getPositionX() const { return mPosition.getX(); }
	float getPositionY() const { return mPosition.getY(); }

	const NODE_ID& getId() const {return mId;};

private:
	const NODE_ID mId;

	Vector2D mPosition = ZERO_VECTOR2D;
};