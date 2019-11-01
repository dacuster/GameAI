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

#include "PerformanceTracker.h"
#include "DeanLibDefines.h"
#include "MemoryPool.h"
#include "DataRepository.h"
#include "Vector2D.h"
#include "Timer.h"

// GraphicsLib

#include "Defines.h"
#include "GraphicsSystem.h"

// Project
#include "GameMessage.h"
#include "UnitDestroyMessage.h"

#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "UnitManager.h"

UnitDestroyMessage::UnitDestroyMessage()
	:GameMessage(UNIT_DESTROY_MESSAGE)
{
	return;
}

UnitDestroyMessage::~UnitDestroyMessage()
{
	return;
}

// Process the message.
void UnitDestroyMessage::process()
{
	gpGame->getUnitManager()->deleteAllUnits();

	return;
}