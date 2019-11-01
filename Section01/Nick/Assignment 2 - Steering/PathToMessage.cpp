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
#include <unordered_map>
#include <string>
#include <cassert>


// Dean Library
#include "Trackable.h"
#include "Vector2D.h"

#include "DeanLibDefines.h"
#include "PerformanceTracker.h"
#include "MemoryPool.h"
#include "DataRepository.h"
#include "MultiDimensionalArray.h"
#include "Timer.h"
#include "Defines.h"


// Graphics Library
#include "Defines.h"

#include "System.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "SpriteManager.h"


// Common Library

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
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "UnitManager.h"
#include "Unit.h"
#include "PathSteering.h"


PathToMessage::PathToMessage( const Vector2D& from, const Vector2D& to, const UnitID id)
:GameMessage(PATH_TO_MESSAGE)
,mFrom(from)
,mTo(to)
,mId(id)
{
}

PathToMessage::~PathToMessage()
{
}

void PathToMessage::process()
{
	GridPathfinder* pPathfinder = gpGame->getPathfinder();
	GridGraph* pGridGraph = gpGame->getGridGraph();
	Grid* pGrid = gpGame->getGrid();
	int fromIndex = pGrid->getCellIndexFromPixelXY( (int)mFrom.getX(), (int)mFrom.getY() );
	int toIndex = pGrid->getCellIndexFromPixelXY( (int)mTo.getX(), (int)mTo.getY() );
	Node* pFromNode = pGridGraph->getNode( fromIndex );
	Node* pToNode = pGridGraph->getNode( toIndex );
	Path newPath = pPathfinder->findPath( pFromNode, pToNode );

	Unit* pUnit = gpGame->getUnitManager()->getUnit(mId);

	if (pUnit == nullptr)
	{
		return;
	}
	SteeringComponent* pSteering = pUnit->getSteeringComponent();

	if (pSteering->getType() == Steering::FOLLOW_PATH)
	{
		PathSteering* pPathSteering = dynamic_cast<PathSteering*>(pSteering->getSteering());

		if (pPathSteering != nullptr)
		{
			pPathSteering->setPath(newPath);
		}
	}
}