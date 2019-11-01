/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <vector>

#include <iostream>
#include <string>
#include <map>


// Dean Library
#include "Trackable.h"

#include "Vector2D.h"
#include "Timer.h"
#include "Defines.h"


// Graphics Library
#include "System.h"

// Game Library
#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"
#include "GameMessage.h"
#include "SwitchPathfindingMessage.h"

#include "Game.h"
#include "Node.h"
#include "Graph.h"
#include "GridGraph.h"
#include "DebugDisplay.h"
#include "DebugContent.h"
#include "PathfindingDebugContent.h"
#include "DepthFirstPathfinder.h"
#include "DijkstraPathfinder.h"
#include "AStarPathfinder.h"


SwitchPathfindingMessage::SwitchPathfindingMessage(const PathfindingType type)
	:GameMessage(SWITCH_PATHFINDER_MESSAGE)
	, mType(type)
{
}

SwitchPathfindingMessage::~SwitchPathfindingMessage()
{
}

void SwitchPathfindingMessage::process()
{
	switch (mType)
	{
		case DEPTH_FIRST_SEARCH:
			gpGame->switchPathfinder(new DepthFirstPathfinder(gpGame->getGridGraph()));
			break;
		case DIJKSTRA:
			gpGame->switchPathfinder(new DijkstraPathfinder(gpGame->getGridGraph()));
			break;
		case A_STAR:
			gpGame->switchPathfinder(new AStarPathfinder(gpGame->getGridGraph()));
			break;
		default:
			break;	
	}

	gpGame->getDebugDisplay()->updateContent(new PathfindingDebugContent(gpGame->getPathfinder()));
}
