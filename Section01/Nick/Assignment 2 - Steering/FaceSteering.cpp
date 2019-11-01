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

#include "PerformanceTracker.h"
#include "MemoryPool.h"
#include "Timer.h"

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
#include "FaceSteering.h"

#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "Unit.h"
#include "UnitManager.h"

FaceSteering::FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFace /*= true*/, float viewAngle /*= MINIMUM_VIEW_ANGLE*/, float outerViewAngle /*= MINIMUM_OUTER_ANGLE*/, float timeToView /*= MINIMUM_TIME_TO_VIEW*/)
	: Steering()
{
	if (shouldFace)
	{
		mType = Steering::FACE;
	}
	else
	{
		mType = Steering::NOT_FACE;
	}

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	setViewAngle(viewAngle);
	setOuterViewAngle(outerViewAngle);
	setTimeToView(timeToView);
}

void FaceSteering::setViewAngle(float viewAngle)
{
	mViewAngle = viewAngle > MINIMUM_VIEW_ANGLE ? viewAngle : MINIMUM_VIEW_ANGLE;

	return;
}

void FaceSteering::setOuterViewAngle(float outerViewAngle)
{
	mOuterViewAngle = outerViewAngle > MINIMUM_OUTER_ANGLE ? outerViewAngle : MINIMUM_OUTER_ANGLE;

	return;
}

void FaceSteering::setTimeToView(float timeToView)
{
	mTimeToView = timeToView > MINIMUM_TIME_TO_VIEW ? timeToView : MINIMUM_TIME_TO_VIEW;

	return;
}

Steering* FaceSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	//are we seeking a location or a unit?
	Vector2D target = mTargetLoc;

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		target = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::FACE || mType == Steering::ARRIVE_AND_FACE || mType == Steering::WANDER_AND_CHASE || mType == Steering::FOLLOW_PATH)
	{
		diff = target - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - target;
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	// Calculate the difference in angle between the owner and the destination vector.
	// Add PI/2 to the owner angle because of image orientation.
	float ownerAngle = atan2f(pOwner->getDirection().getY(), pOwner->getDirection().getX()) + 0.5f * (float)M_PI;
	float pointAngle = atan2f(-diff.getY(), diff.getX());

	// Prevent negative values.
	if (ownerAngle < 0.0f)
	{
		ownerAngle += 2.0f * (float)M_PI;
	}
	if (pointAngle < 0.0f)
	{
		pointAngle += 2.0f * (float)M_PI;
	}

	// Convert to degrees.
	radiansToDegrees(pointAngle);
	radiansToDegrees(ownerAngle);

	// Calculate the angle difference.
	float diffAngle = ownerAngle - pointAngle;

	float compareAngle = diffAngle;
	diffAngle = fmodf(diffAngle, 180.0f);

	float absAngle = abs(compareAngle);

	float velocity = diffAngle > 0.0f ? 1.0f : -1.0f;
	float targetSpeed = data.maxSpeed;

	// Stop
	if (absAngle < mViewAngle)
	{
		data.rotAcc = 0.0f;
		data.rotVel = 0.0f;
	}
	// Slow down.
	else if (absAngle < mOuterViewAngle)
	{
		targetSpeed *= diffAngle / mOuterViewAngle;
		velocity *= targetSpeed;

		data.rotAcc = velocity - data.rotVel;
		data.rotAcc /= mTimeToView;
	}
	// Rotate as fast as posible.
	else
	{
		velocity *= targetSpeed;
		data.rotAcc = velocity;
	}
	
	this->mData = data;
	return this;
}

