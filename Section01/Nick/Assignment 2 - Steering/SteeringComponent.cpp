/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <map>


// DeanLib
#include "Trackable.h"
#include "PerformanceTracker.h"
#include "Vector2D.h"
#include "DataRepository.h"
#include "DeanLibDefines.h"
#include "Timer.h"
#include "MemoryPool.h"

// GraphicsLib
#include "GraphicsSystem.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Defines.h"

// Project
#include "Path.h"
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "SteeringComponent.h"

#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "WanderSteering.h"
#include "ArriveAndFaceSteering.h"
#include "WanderAndChaseSteering.h"
#include "PathSteering.h"

//#include "ComponentManager.h"
//#include "Unit.h"

SteeringComponent::SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID) 
	:Component(id)
	, mPhysicsComponentID(physicsComponentID)
	, mpSteering(NULL)
{
}

SteeringComponent::~SteeringComponent()
{
	delete mpSteering;
}

void SteeringComponent::applySteering(PhysicsComponent& physicsComponent)
{
	if (mpSteering != NULL)
	{
		//allow Steering to run
		mpSteering->update();
		//set physics data to that of the Steering
		physicsComponent.setData(mpSteering->getData());
		//update component's data
		mData.targetLoc = mpSteering->getTargetLoc();
	}
}

void SteeringComponent::setData(const SteeringData& data)
{
	mData = data;

	switch (data.type)
	{
		case Steering::SEEK:
		{
			//cleanup old steering - todo: check for already existing steering and reuse if possible
			delete mpSteering;
			//create new steering
			mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, false);
			break;
		}
		case Steering::FLEE:
		{
			delete mpSteering;

			mpSteering = new SeekSteering(data.ownerID, data.targetLoc, data.targetID, true);
			break;
		}
		case Steering::ARRIVE:
		{
			delete mpSteering;

			mpSteering = new ArriveSteering(data.ownerID, data.targetLoc, data.targetID, false, data.arriveRadius, data.arriveSlowRadius, data.arriveTimeToTarget);
			break;
		}
		case Steering::FACE:
		{
			delete mpSteering;

			mpSteering = new FaceSteering(data.ownerID, data.targetLoc, data.targetID, true, data.viewAngle, data.outerViewAngle, data.timeToView);
			break;
		}
		case Steering::WANDER:
		{
			delete mpSteering;

			mpSteering = new WanderSteering(data.ownerID, data.targetLoc, data.targetID, data.wanderArriveRadius);
			break;
		}
		case Steering::ARRIVE_AND_FACE:
		{
			delete mpSteering;

			mpSteering = new ArriveAndFaceSteering(data.ownerID, data.targetLoc, data.targetID, data.arriveRadius, data.arriveSlowRadius, data.arriveTimeToTarget, data.viewAngle, data.outerViewAngle, data.timeToView);
			break;
		}
		case Steering::WANDER_AND_CHASE:
		{
			delete mpSteering;

			mpSteering = new WanderAndChaseSteering(data.ownerID, data.targetLoc, data.targetID, data.chaseRadius, data.wanderArriveRadius, data.arriveRadius, data.arriveSlowRadius, data.arriveTimeToTarget, data.viewAngle, data.outerViewAngle, data.timeToView);
			break;
		}
		case Steering::FOLLOW_PATH:
		{
			delete mpSteering;
			// TODO: Create Follow Path steering before creating here.
			mpSteering = new PathSteering(data.ownerID, data.targetLoc, data.targetID, data.arriveRadius, data.arriveSlowRadius, data.arriveTimeToTarget, data.viewAngle, data.outerViewAngle, data.timeToView);
			break;
		}
		default:
		{

		}
	};
}

