/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// Dean Library
#include "Trackable.h"
#include "Vector2D.h"


// Game Library
#include "Node.h"

Node::Node()
:mId(BAD_NODE_ID)
{
}

Node::Node( const NODE_ID& id )
:mId(id)
{
}

Node::~Node()
{
}

void Node::setPosition(Vector2D& position)
{
	mPosition = position;

	return;
}
