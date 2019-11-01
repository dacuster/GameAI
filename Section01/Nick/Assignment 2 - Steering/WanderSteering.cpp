/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <cassert>
#include <unordered_map>
#include <map>
#include <string>

#include <stdlib.h>
#include <time.h>

// DeanLib
#include "Trackable.h"
#include "DeanLibDefines.h"
#include "Vector2D.h"
#include "DataRepository.h"
#include "Timer.h"

#include "PerformanceTracker.h"
#include "MemoryPool.h"

// GraphicsLib
#include "GraphicsSystem.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Defines.h"

// Project
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "SeekSteering.h"
#include "WanderSteering.h"

#include "Unit.h"
#include "SteeringComponent.h"
#include "PositionComponent.h"
#include "UnitManager.h"
#include "GameMessage.h"
#include "UnitUpdateTargetMessage.h"
#include "GameMessageManager.h"

WanderSteering::WanderSteering(
	const UnitID& ownerID
	, const Vector2D& targetLoc
	, const UnitID& targetID
	, float wanderRadius /*= MINIMUM_WANDER_RADIUS*/)
	:SeekSteering(ownerID, targetLoc, targetID)
{
	mType = Steering::WANDER;
	mMinimumWanderRadius = wanderRadius > MINIMUM_WANDER_RADIUS ? wanderRadius : MINIMUM_WANDER_RADIUS;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	return;
}

void WanderSteering::setMinimumWanderRadius(const float minimumWanderRadius)
{
	mMinimumWanderRadius = minimumWanderRadius > MINIMUM_WANDER_RADIUS ? minimumWanderRadius : MINIMUM_WANDER_RADIUS;

	return;
}

Vector2D WanderSteering::getRandomPosition()
{
	int displayHeight = GraphicsSystem::getDisplayHeight();
	int displayWidth = GraphicsSystem::getDisplayWidth();

	// Random seed.
	srand(time(NULL));

	// Generate random values between 0 and width/height
	int randomX = rand() % displayWidth;
	int randomY = rand() % displayHeight;

	return Vector2D(randomX, randomY);
}

Steering* WanderSteering::getSteering()
{
	// Direction vector for the difference between target and unit.
	Vector2D diff;

	// The owner of this steering component.
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	// Get a direction vector.
	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();

	float distance = diff.getLengthSquared();

	// Inside radius. Change target.
	if (distance < mMinimumWanderRadius * mMinimumWanderRadius)
	{
		// Create message to setup new target location for the steering.
		GameMessage* pMessage = new UnitUpdateTargetMessage(getRandomPosition(), mOwnerID);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	diff.normalize();
	diff *= pOwner->getMaxAcc();

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.acc = diff;

	this->mData = data;
	return this;
}