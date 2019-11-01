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

#include "Unit.h"
#include "SteeringComponent.h"
#include "PositionComponent.h"
#include "UnitManager.h"

ArriveSteering::ArriveSteering(
	  const UnitID& ownerID
	, const Vector2D& targetLoc
	, const UnitID& targetID
	, bool shouldDistance /*= false*/
	, float targetRadius /*= MINIMUM_RADIUS*/
	, float slowRadius /*= MINIMUM_SLOW_RADIUS*/
	, float timeToTarget /*= MINIMUM_TIME*/)
		:SeekSteering(ownerID, targetLoc, targetID, shouldDistance)
{
	setTargetRadius(targetRadius);
	setSlowRadius(slowRadius);
	setTimeToTarget(timeToTarget);

	if (shouldDistance)
	{
		mType = Steering::DISTANCE;
	}
	else
	{
		mType = Steering::ARRIVE;
	}

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	return;
}

// Set the radius to the target location.
void ArriveSteering::setTargetRadius(float targetRadius)
{
	mTargetRadius = targetRadius > MINIMUM_RADIUS ? targetRadius : MINIMUM_RADIUS;

	return;
}

void ArriveSteering::setSlowRadius(float slowRadius)
{
	mSlowRadius = slowRadius > MINIMUM_SLOW_RADIUS ? slowRadius : MINIMUM_SLOW_RADIUS;

	return;
}

// Set the time multiplier to slow down the steering.
void ArriveSteering::setTimeToTarget(float timeToTarget)
{
	mTimeToTarget = timeToTarget > MINIMUM_TIME ? timeToTarget : MINIMUM_TIME;

	return;
}

Steering* ArriveSteering::getSteering()
{
	// Target speed for unit.
	float targetSpeed = 0.0f;
	// Direction vector for the difference between target and unit.
	Vector2D diff;
	// The owner of this steering component.
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	//are we seeking a location or a unit?
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);

		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	// Get a direction vector.
	if (mType == Steering::ARRIVE || mType == Steering::ARRIVE_AND_FACE || mType == Steering::WANDER_AND_CHASE)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	// Physics data for movement.
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	float distance = diff.getLength();

	if (mType == Steering::ARRIVE || mType == Steering::ARRIVE_AND_FACE || mType == Steering::WANDER_AND_CHASE)
	{
		// Inside radius. Stop.
		if (distance < mTargetRadius)
		{
			//return NULL;
			data.vel = ZERO_VECTOR2D;
			data.acc = ZERO_VECTOR2D;
		}
		else if (distance > mSlowRadius)
		{
			targetSpeed = data.maxSpeed;
			diff.normalize();
			diff *= targetSpeed;

			data.acc = diff;
		}
		else
		{
			targetSpeed = data.maxSpeed * distance / mSlowRadius;
			diff.normalize();
			diff *= targetSpeed;

			data.acc = diff - data.vel;
			data.acc /= mTimeToTarget;
		}
	}

	this->mData = data;
	return this;
}