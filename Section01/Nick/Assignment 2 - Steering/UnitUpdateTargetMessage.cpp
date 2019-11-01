/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <unordered_map>
#include <map>
#include <string>

#include <assert.h>

// DeanLib
#include "Trackable.h"
#include "Vector2D.h"
#include "DataRepository.h"
#include "PerformanceTracker.h"
#include "Timer.h"

#include "DeanLibDefines.h"
#include "MemoryPool.h"

// GraphicsLib
#include "Sprite.h"
#include "Defines.h"

#include "GraphicsSystem.h"
#include "SpriteManager.h"

// Project
#include "GameMessage.h"
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "UnitUpdateTargetMessage.h"

#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "UnitManager.h"
#include "Unit.h"

UnitUpdateTargetMessage::UnitUpdateTargetMessage(const Vector2D& _position, const UnitID& _id)
	:GameMessage(UNIT_UPDATE_TARGET_MESSAGE)
{
	mPosition = _position;
	mId = _id;

	return;
}

UnitUpdateTargetMessage::~UnitUpdateTargetMessage()
{
	return;
}

// Process the message.
void UnitUpdateTargetMessage::process()
{
	// Get the unit to change the target location for.
	Unit* pUnit = gpGame->getUnitManager()->getUnit(mId);
	// Update the steering target location of the unit.
	pUnit->setSteering(pUnit->getSteeringComponent()->getType(), mPosition, pUnit->getSteeringComponent()->getTargetID());

	return;
}