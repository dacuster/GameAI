/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <vector>
#include <map>


// Dean Library
#include "Trackable.h"
#include "Vector2D.h"


// Game Library
#include "Node.h"
#include "Graph.h"

#include "Connection.h"


Graph::Graph()
{
}

Graph::~Graph()
{
	for( unsigned int i=0; i<mNodes.size(); i++ )
	{
		delete mNodes[i];
	}

	for( unsigned int i=0; i<mConnections.size(); i++ )
	{
		delete mConnections[i];
	}
}

void Graph::init()
{
}

std::vector<Connection*> Graph::getConnections( const Node& from )
{
	return getConnections( from.getId() );
}

std::vector<Connection*> Graph::getConnections( const NODE_ID& fromId )
{
	static std::vector<Connection*> sEmpty;
	
	std::map< NODE_ID, std::vector<Connection*> >::iterator iter = mConnectionMap.find( fromId );
	if( iter == mConnectionMap.end() )
	{
		return sEmpty;
	}
	else
	{
		return iter->second;
	}
}

Node* Graph::getNode( int index )
{
	if( index < (int)mNodes.size() )
	{
		return mNodes[index];
	}
	else
	{
		return NULL;
	}
}