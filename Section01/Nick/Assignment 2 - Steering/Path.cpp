/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <vector>


// Dean Library
#include "Trackable.h"


// Game Library
#include "Path.h"


Path::Path()
{
}

Path::~Path()
{
}

Node* Path::peekNode( int index ) const
{
	if( (unsigned int)index < mNodes.size() )
	{
		return mNodes[index];
	}
	else
	{
		return NULL;
	}
}

Node* Path::peekNextNode() const
{
	if( mNodes.size() > 0 )
	{
		return mNodes.back();
	}
	else
	{
		return NULL;
	}
}

Node* Path::getAndRemoveNextNode()
{
	if( mNodes.size() > 0 )
	{
		Node* pNode = mNodes.back();
		mNodes.pop_back();
		return pNode;
	}
	else
	{
		return NULL;
	}
}

void Path::addNode( Node* pNode )
{
	mNodes.push_back( pNode );
}

void Path::setPath(std::vector<Node*>* pPath)
{
	mNodes = *pPath;

	return;
}

void Path::clear()
{
	mNodes.clear();
}

bool Path::containsNode( Node* pNode )
{
	bool retVal = false;

	for( unsigned int i=0; i<mNodes.size(); i++ )
	{
		if( mNodes[i] == pNode )
		{
			retVal = true;
			break;
		}
	}
	return retVal;
}
