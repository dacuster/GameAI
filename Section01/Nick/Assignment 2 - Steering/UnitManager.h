/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Unit;
class Sprite;
struct PositionData;
struct PhysicsData;

const UnitID PLAYER_UNIT_ID = 0;

class UnitManager : public Trackable
{
public:
	UnitManager(Uint32 maxSize);
	~UnitManager(){};

	Unit* createUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = PositionComponent::getZeroPositionData(), const PhysicsData& physicsData = PhysicsComponent::getZeroPhysicsData(), const UnitID& id = INVALID_UNIT_ID);
	Unit* createPlayerUnit(const Sprite& sprite, bool shouldWrap = true, const PositionData& posData = PositionComponent::getZeroPositionData(), const PhysicsData& physicsData = PhysicsComponent::getZeroPhysicsData());
	Unit* createRandomUnit(const Sprite& sprite, Steering::SteeringType steeringType);

	Unit* getUnit(const UnitID& id) const;
	void deleteUnit(const UnitID& id);
	void deleteAllUnits();
	void deleteRandomUnit();

	std::unordered_map<UnitID, Unit*> getAllUnits() const;

	void drawAll() const;
	void updateAll(float elapsedTime);

	Unit* getPlayerUnit() const { return getUnit(PLAYER_UNIT_ID); };

	Uint32 getNumUnits() const { return mUnitMap.size(); };

private:
	static UnitID msNextUnitID;
	MemoryPool mPool;
	std::unordered_map<UnitID, Unit*> mUnitMap;
};