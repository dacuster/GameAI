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
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "WanderAndChaseSteering.h"

#include "Unit.h"
#include "SteeringComponent.h"
#include "PositionComponent.h"
#include "UnitManager.h"
#include "GameMessage.h"
#include "UnitUpdateTargetMessage.h"
#include "GameMessageManager.h"

WanderAndChaseSteering::WanderAndChaseSteering(
	const UnitID& ownerID,
	const Vector2D& targetLoc,
	const UnitID& targetID /*= INVALID_UNIT_ID*/,
	float chaseRadius /*= MINIMUM_CHASE_RADIUS*/,
	float wanderRadius /*= MINIMUM_WANDER_RADIUS*/,
	float targetRadius /*= MINIMUM_RADIUS*/,
	float slowRadius /*= MINIMUM_SLOW_RADIUS*/,
	float timeToTarget /*= MINIMUM_TIME*/,
	float viewAngle /*= MINIMUM_VIEW_ANGLE*/,
	float outerViewAngle /*= MINIMUM_OUTER_ANGLE*/,
	float timeToView /*= MINIMUM_TIME_TO_VIEW*/)
	: ArriveSteering(), FaceSteering(), WanderSteering()
{
	setTargetRadius(targetRadius);
	setSlowRadius(slowRadius);
	setTimeToTarget(timeToTarget);

	setViewAngle(viewAngle);
	setOuterViewAngle(outerViewAngle);
	setTimeToView(timeToView);

	setMinimumWanderRadius(wanderRadius);

	mChaseRadius = chaseRadius;

	mType = Steering::WANDER_AND_CHASE;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	return;
}

Steering* WanderAndChaseSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	
	Vector2D diff = ZERO_VECTOR2D;
	Vector2D target = ZERO_VECTOR2D;

	// If target unit exists, set its position as target.
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		target = pTarget->getPositionComponent()->getPosition();
	}

	// Calculate the distance to the target.
	diff = target - pOwner->getPositionComponent()->getPosition();

	// Close enough to target to chase.
	if (diff.getLengthSquared() < mChaseRadius * mChaseRadius && diff != ZERO_VECTOR2D)
	{
		PhysicsData arriveData = ArriveSteering::getSteering()->getData();

		data.acc = arriveData.acc;
		data.vel = arriveData.vel;
	}
	// Wander
	else
	{
		PhysicsData wanderData = WanderSteering::getSteering()->getData();

		data.acc = wanderData.acc;
		data.vel = wanderData.vel;
	}

	PhysicsData faceData = FaceSteering::getSteering()->getData();
	data.rotAcc = faceData.rotAcc;
	data.rotVel = faceData.rotVel;

	this->mData = data;
	return this;
}
