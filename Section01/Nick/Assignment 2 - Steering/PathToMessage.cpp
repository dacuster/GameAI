/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library

#include <iostream>
#include <vector>
#include <map>


// Dean Library
#include "Trackable.h"
#include "Vector2D.h"

#include "MultiDimensionalArray.h"
#include "Timer.h"
#include "Defines.h"


// Graphics Library

#include "System.h"


// Common Library

#include "Game.h"
#include "Grid.h"


// Game Library
#include "GameMessage.h"
#include "PathToMessage.h"

#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"
#include "Node.h"
#include "Graph.h"
#include "GridGraph.h"
#include "GameApp.h"

PathToMessage::PathToMessage( const Vector2D& from, const Vector2D& to )
:GameMessage(PATH_TO_MESSAGE)
,mFrom(from)
,mTo(to)
{
}

PathToMessage::~PathToMessage()
{
}

void PathToMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if( pGame != NULL ) 
	{
		GridPathfinder* pPathfinder = pGame->getPathfinder();
		GridGraph* pGridGraph = pGame->getGridGraph();
		Grid* pGrid = pGame->getGrid();
		int fromIndex = pGrid->getCellIndexFromPixelXY( (int)mFrom.getX(), (int)mFrom.getY() );
		int toIndex = pGrid->getCellIndexFromPixelXY( (int)mTo.getX(), (int)mTo.getY() );
		Node* pFromNode = pGridGraph->getNode( fromIndex );
		Node* pToNode = pGridGraph->getNode( toIndex );
		pPathfinder->findPath( pFromNode, pToNode );
	}
}