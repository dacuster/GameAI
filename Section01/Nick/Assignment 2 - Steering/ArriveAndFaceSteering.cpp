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
#include "FaceSteering.h"
#include "ArriveAndFaceSteering.h"

#include "Unit.h"
#include "SteeringComponent.h"
#include "PositionComponent.h"
#include "UnitManager.h"

ArriveAndFaceSteering::ArriveAndFaceSteering(
	const UnitID& ownerID,
	const Vector2D& targetLoc,
	const UnitID& targetID /*= INVALID_UNIT_ID*/,
	float targetRadius /*= MINIMUM_RADIUS*/,
	float slowRadius /*= MINIMUM_SLOW_RADIUS*/,
	float timeToTarget /*= MINIMUM_TIME*/,
	float viewAngle /*= MINIMUM_VIEW_ANGLE*/,
	float outerViewAngle /*= MINIMUM_OUTER_ANGLE*/,
	float timeToView /*= MINIMUM_TIME_TO_VIEW*/)
	:ArriveSteering(),FaceSteering()
{
	setTargetRadius(targetRadius);
	setSlowRadius(slowRadius);
	setTimeToTarget(timeToTarget);

	setViewAngle(viewAngle);
	setOuterViewAngle(outerViewAngle);
	setTimeToView(timeToView);

	mType = Steering::ARRIVE_AND_FACE;

	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	return;
}

Steering* ArriveAndFaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	PhysicsData arriveData = ArriveSteering::getSteering()->getData();
	PhysicsData faceData = FaceSteering::getSteering()->getData();

	data.acc = arriveData.acc;
	data.vel = arriveData.vel;
	data.rotAcc = faceData.rotAcc;
	data.rotVel = faceData.rotVel;

	this->mData = data;
	return this;
}
