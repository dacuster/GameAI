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
#include "DeanLibDefines.h"
#include "MemoryPool.h"
#include "Timer.h"

// GraphicsLib
#include "Defines.h"

#include "GraphicsSystem.h"
#include "SpriteManager.h"
#include "Sprite.h"

// Project
#include "GameMessage.h"
#include "PlayerMoveToMessage.h"

#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "Unit.h"
#include "UnitManager.h"

//#include "GameMessageManager.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
	:GameMessage(PLAYER_MOVETO_MESSAGE)
	,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	Unit* pPlayer = gpGame->getUnitManager()->getPlayerUnit();
	pPlayer->setSteering(pPlayer->getSteeringComponent()->getType(), mPos);
	//pPlayer->setSteering(Steering::SEEK, mPos);
}