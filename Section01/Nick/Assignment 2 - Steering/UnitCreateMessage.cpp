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

// Project
#include "GameMessage.h"
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "UnitCreateMessage.h"

#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "UnitManager.h"

class Unit;

UnitCreateMessage::UnitCreateMessage(const Sprite& _sprite, Steering::SteeringType _steeringType, int _count /*= 1*/)
	:GameMessage(UNIT_CREATE_MESSAGE)
{
	mSprite = _sprite;
	mSteeringType = _steeringType;
	mCreateCount = _count >= 1 ? _count : 1;

	return;
}

UnitCreateMessage::~UnitCreateMessage()
{
	return;
}

// Process the message.
void UnitCreateMessage::process()
{
	for (int counter = 0; counter < mCreateCount; counter++)
	{
		Unit* pUnit = gpGame->getUnitManager()->createRandomUnit(mSprite, mSteeringType);
	}

	return;
}