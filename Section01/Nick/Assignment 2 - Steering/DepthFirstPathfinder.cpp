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
#include <list>
#include <iostream>


// Dean Library
#include "Trackable.h"

#include "Timer.h"
#include "Defines.h"
#include "PerformanceTracker.h"
#include "Vector2D.h"


// Graphics Library

#include "System.h"


// Common Library

#include "Game.h"


// Game Library
#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"
#include "DepthFirstPathfinder.h"

#include "Node.h"
#include "Graph.h"
#include "Connection.h"
#include "GridGraph.h"


DepthFirstPathfinder::DepthFirstPathfinder( Graph* pGraph )
:GridPathfinder(dynamic_cast<GridGraph*>(pGraph) )
{
	mType = DEPTH_FIRST_SEARCH;
}

DepthFirstPathfinder::~DepthFirstPathfinder()
{
}

Path DepthFirstPathfinder::findPath( Node* pFrom, Node* pTo )
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it
	std::list<Node*> nodesToVisit;
	nodesToVisit.push_front( pFrom );

#ifdef VISUALIZE_PATH
	mPath.clear();
	mVisitedNodes.clear();
	mVisitedNodes.push_back( pFrom );
#endif
	
	Path path;

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while( pCurrentNode != pTo && nodesToVisit.size() > 0 )
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		path.addNode( pCurrentNode );

		//get the Connections for the current node
		std::vector<Connection*> connections = mpGraph->getConnections( pCurrentNode->getId() );

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for( unsigned int i=0; i<connections.size(); i++ )
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();
			if( !toNodeAdded && 
				!path.containsNode( pTempToNode ) && 
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode ) == nodesToVisit.end() )
			{
				nodesToVisit.push_front( pTempToNode );//uncomment me for depth-first search
				//nodesToVisit.push_back( pTempToNode );//uncomment me for breadth-first search
				if( pTempToNode == pTo )
				{
					toNodeAdded = true;
				}
#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back( pTempToNode );
#endif

			}
		}
	}
	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mPath = path;
#endif
	return path;

}

