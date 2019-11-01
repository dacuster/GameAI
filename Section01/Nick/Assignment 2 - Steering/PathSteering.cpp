// C++ Library
#include <vector>
#include <string>
#include <cassert>
#include <unordered_map>
#include <map>


// Dean Library
#include "Trackable.h"
#include "Vector2D.h"
#include "PerformanceTracker.h"
#include "DataRepository.h"
#include "DeanLibDefines.h"
#include "Timer.h"
#include "MemoryPool.h"


// Graphics Library
#include "GraphicsSystem.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Defines.h"


// Game Library
#include "Path.h"
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "PathSteering.h"


#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Node.h"









//#include "Game.h"
//#include "UnitManager.h"
//#include "Unit.h"
//#include "Node.h"
//
//#include "Trackable.h"
//#include "Steering.h"
//#include "Pathfinder.h"
//#include "GridPathfinder.h"
//#include "Graph.h"
//#include "GridGraph.h"
//#include "Path.h"

PathSteering::PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID)
	:Steering()
{
	mType = Steering::FOLLOW_PATH;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
	mpPath = Path();
	pathIndex = 0;
}

void PathSteering::setPath(Path path)
{
	pathIndex = 0;
	mpPath = path;
}

void PathSteering::newPath(Vector2D destination)
{
	//Replace path with new path calculated from gpGame->mpPathfinder
}

Steering* PathSteering::getSteering()
{

	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	float speed = 3.0f;
	float nextNodeDistance = 10.0f;
	Node* nextNode = mpPath.peekNode(pathIndex);

	diff = nextNode->getPosition() - pOwner->getPositionComponent()->getPosition();
	pOwner->getPositionComponent()->setFacing(float(diff.calcFacing()));

	if (mpPath.getNumNodes() >= 0) {
		if (diff.getLengthSquared() >= nextNodeDistance && mpPath.peekNode(pathIndex) != nullptr)
		{
			data.vel = diff.getNormalizedVector() * speed;
		}
		else
		{
			++pathIndex;
		}
		this->mData = data;
	}
	return this;
}