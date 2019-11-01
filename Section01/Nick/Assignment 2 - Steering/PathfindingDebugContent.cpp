/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library

#include <sstream>
#include <vector>


// Dean Library
#include "Trackable.h"


// Game Library
#include "DebugContent.h"
#include "PathfindingDebugContent.h"

#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"

PathfindingDebugContent::PathfindingDebugContent( GridPathfinder* pPathfinder )
	:mpPathfinder(pPathfinder)
{
}

std::string PathfindingDebugContent::getDebugString()
{
	std::stringstream theStream;

#ifdef VISUALIZE_PATH
	if( mpPathfinder->mPath.getNumNodes() > 0 )
	{
		theStream << "Pathlength:"<< mpPathfinder->mPath.getNumNodes();
	}
	
	theStream << "  Num Nodes Processed:" << mpPathfinder->mVisitedNodes.size();
#endif
	theStream << "  Elapsed Time:" << mpPathfinder->mTimeElapsed;


	std::string type;

	switch (mpPathfinder->getType())
	{
		case DEPTH_FIRST_SEARCH:
			type = "DFS";
			break;
		case DIJKSTRA:
			type = "Dijkstra";
			break;
		case A_STAR:
			type = "A*";
			break;
		default:
			break;
	}

	theStream << " Pathfinder: " << type;
	return theStream.str();
}

