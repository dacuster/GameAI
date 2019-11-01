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
#include <cassert>

// DeanLib
#include "Trackable.h"
#include "DeanLibDefines.h"
#include "MemoryPool.h"
#include "DataRepository.h"
#include "Vector2D.h"
#include "PerformanceTracker.h"
#include "Timer.h"

// GraphicsLib
#include "Defines.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "SpriteManager.h"

// Project
#include "Game.h"
#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "SeekSteering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "UnitManager.h"

#include "Unit.h"
#include "ComponentManager.h"

UnitID UnitManager::msNextUnitID = PLAYER_UNIT_ID + 1;

UnitManager::UnitManager(Uint32 maxSize)
	:mPool(maxSize, sizeof(Unit))
{
}

Unit* UnitManager::createUnit(const Sprite& sprite, bool shouldWrap, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/, const UnitID& id)
{
	Unit* pUnit = NULL;

	Byte* ptr = mPool.allocateObject();

	if (ptr != NULL)
	{
		//create unit
		pUnit = new (ptr)Unit(sprite);//placement new

		UnitID theID = id;
		if (theID == INVALID_UNIT_ID)
		{
			theID = msNextUnitID;
			msNextUnitID++;
		}

		//place in map
		mUnitMap[theID] = pUnit;

		//assign id and increment nextID counter
		pUnit->mID = theID;

		//create some components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		ComponentID id = pComponentManager->allocatePositionComponent(posData,shouldWrap);
		pUnit->mPositionComponentID = id;
		pUnit->mpPositionComponent = pComponentManager->getPositionComponent(id);
		pUnit->mPhysicsComponentID = pComponentManager->allocatePhysicsComponent(pUnit->mPositionComponentID, physicsData);
		pUnit->mpPhysicsComponent = pComponentManager->getPhysicsComponent(id);
		pUnit->mSteeringComponentID = pComponentManager->allocateSteeringComponent(pUnit->mPhysicsComponentID);
		pUnit->mpSteeringComponent = pComponentManager->getSteeringComponent(id);

		//set max's
		pUnit->mMaxSpeed = gpGame->getDataRepository()->getEntry(DataKeyEnum::MAX_SPEED).getFloatVal();
		pUnit->mMaxAcc = gpGame->getDataRepository()->getEntry(DataKeyEnum::MAX_ACC).getFloatVal();
		pUnit->mMaxRotAcc = gpGame->getDataRepository()->getEntry(DataKeyEnum::MAX_ROT_ACC).getFloatVal();
		pUnit->mMaxRotVel = gpGame->getDataRepository()->getEntry(DataKeyEnum::MAX_ROT_VEL).getFloatVal();
	}

	return pUnit;
}

Unit* UnitManager::createPlayerUnit(const Sprite& sprite, bool shouldWrap /*= true*/, const PositionData& posData /*= ZERO_POSITION_DATA*/, const PhysicsData& physicsData /*= ZERO_PHYSICS_DATA*/)
{
	return createUnit(sprite, shouldWrap, posData, physicsData, PLAYER_UNIT_ID);
}

Unit* UnitManager::createRandomUnit(const Sprite& sprite, Steering::SteeringType steeringType)
{
	int posX = rand() % GraphicsSystem::getDisplayWidth();
	int posY = rand() % GraphicsSystem::getDisplayHeight();
	int velX = rand() % 50 - 25;
	int velY = rand() % 40 - 20;

	// Set the wrapping based on the steering type.
	bool shouldWrap = (steeringType == Steering::FLEE || steeringType == Steering::DISTANCE);

	Unit* pUnit = createUnit(sprite, shouldWrap, PositionData(Vector2D(posX,posY),0), PhysicsData(Vector2D(velX,velY),Vector2D(0.1f,0.1f), 0.1f, 0.05f));

	if (pUnit != NULL)
	{
		pUnit->setSteering(steeringType, Vector2D((int)(GraphicsSystem::getDisplayWidth() / 2), (int)(GraphicsSystem::getDisplayHeight() / 2)), PLAYER_UNIT_ID);
		pUnit->setShowTarget(!shouldWrap);
	}

	return pUnit;
}

Unit* UnitManager::getUnit(const UnitID& id) const
{
	auto it = mUnitMap.find(id);

	if (it != mUnitMap.end())//found?
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

void UnitManager::deleteUnit(const UnitID& id)
{
	auto it = mUnitMap.find(id);

	if (it != mUnitMap.end())//found?
	{
		Unit* pUnit = it->second;//hold for later

		//remove from map
		mUnitMap.erase(it);

		//remove components
		ComponentManager* pComponentManager = gpGame->getComponentManager();
		pComponentManager->deallocatePhysicsComponent(pUnit->mPhysicsComponentID);
		pComponentManager->deallocatePositionComponent(pUnit->mPositionComponentID);
		pComponentManager->deallocateSteeringComponent(pUnit->mSteeringComponentID);

		//call destructor
		pUnit->~Unit();

		//free the object in the pool
		mPool.freeObject((Byte*)pUnit);
	}
}

void UnitManager::deleteAllUnits()
{
	int counter = 0;

	while (!mUnitMap.empty())
	{
		deleteUnit(0);
	}

	return;
}

void UnitManager::deleteRandomUnit()
{
	if (mUnitMap.size() >= 1)
	{
		Uint32 target = rand() % mUnitMap.size();

		if (target == 0)//don't allow the 0th element to be deleted as it is the player unit
		{
			target = 1;
		}

		Uint32 cnt = 0;

		for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it, cnt++)
		{
			if (cnt == target)
			{
				//failsafe against deleting player unit
				if (getPlayerUnit() != it->second)
				{
					deleteUnit(it->first);
				}

				break;
			}
		}
	}
}

void UnitManager::drawAll() const
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->draw();
	}
}

void UnitManager::updateAll(float elapsedTime)
{
	for (auto it = mUnitMap.begin(); it != mUnitMap.end(); ++it)
	{
		it->second->update(elapsedTime);
	}
}