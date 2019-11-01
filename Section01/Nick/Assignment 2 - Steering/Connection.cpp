/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// Dean Library
#include "Trackable.h"

// Game Library
#include "Connection.h"

Connection::Connection( Node* pFrom, Node* pTo, float cost )
:mpFrom(pFrom)
,mpTo(pTo)
,mCost(cost)
{
}

Connection::~Connection()
{
}