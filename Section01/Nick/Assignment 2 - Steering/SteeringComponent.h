/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class PhysicsComponent;

struct SteeringData : public Trackable
{
	SteeringData()
		:type(Steering::INVALID_TYPE)
		, targetLoc(ZERO_VECTOR2D)
		, ownerID(INVALID_UNIT_ID)
		, targetID(INVALID_UNIT_ID){};

	SteeringData(
		Steering::SteeringType theType
		, const Vector2D& theTargetLoc = ZERO_VECTOR2D
		, UnitID theOwner = INVALID_UNIT_ID
		, UnitID theTarget = INVALID_UNIT_ID)
			:type(theType)
			, targetLoc(theTargetLoc)
			, ownerID(theOwner)
			, targetID(theTarget){};

	Steering::SteeringType type;
	Vector2D targetLoc;
	UnitID ownerID;
	UnitID targetID;

	// Arrive steering data.
	float arriveRadius = gpGame->getDataRepository()->getEntry(DataKeyEnum::ARRIVE_RADIUS).getFloatVal();
	float arriveSlowRadius = gpGame->getDataRepository()->getEntry(DataKeyEnum::ARRIVE_SLOW_RADIUS).getFloatVal();
	float arriveTimeToTarget = gpGame->getDataRepository()->getEntry(DataKeyEnum::ARRIVE_TIME).getFloatVal();

	// Face steering data.
	float viewAngle = gpGame->getDataRepository()->getEntry(DataKeyEnum::VIEW_ANGLE).getFloatVal();
	float outerViewAngle = gpGame->getDataRepository()->getEntry(DataKeyEnum::OUTER_VIEW_ANGLE).getFloatVal();
	float timeToView = gpGame->getDataRepository()->getEntry(DataKeyEnum::TIME_TO_VIEW).getFloatVal();

	// Wander steering data
	float wanderArriveRadius = gpGame->getDataRepository()->getEntry(DataKeyEnum::WANDER_ARRIVE_RADIUS).getFloatVal();

	// Chase steering data
	float chaseRadius = gpGame->getDataRepository()->getEntry(DataKeyEnum::CHASE_RADIUS).getFloatVal();
};

class SteeringComponent : public Component
{
public:
	//getters and setters
	Steering::SteeringType getType() const { return mData.type; };

	const Vector2D& getTargetLoc() const { return mData.targetLoc; };
	void setTargetLoc(const Vector2D& pos) { mData.targetLoc = pos; };
	
	UnitID getOwnerID() const { return mData.ownerID; };
	
	UnitID getTargetID() const { return mData.targetID; };
	void setTargetUnitID(const UnitID& id) { mData.targetID = id; };
	
	ComponentID getPhysicsComponentID() const { return mPhysicsComponentID; };
	
	const SteeringData& getData() const { return mData; };
	void setData(const SteeringData& data);
	
	void applySteering(PhysicsComponent& physicsComponent);

	static const SteeringData& getZeroSteeringData() { static SteeringData data; return data; }

	float getArriveRadius() const { return mData.arriveRadius; };
	void setArriveRadius(float radius) { mData.arriveRadius = radius; };

	float getArriveSlowRadius() const { return mData.arriveSlowRadius; };
	void setArriveSlowRadius(float radius) { mData.arriveSlowRadius = radius; };

	float getArriveTimeToTarget() const { return mData.arriveTimeToTarget; };
	void setArriveTimeToTarget(float timeToTarget) { mData.arriveTimeToTarget = timeToTarget; };

private:
	ComponentID mPhysicsComponentID;
	SteeringData mData;
	Steering* mpSteering;
	PhysicsComponent* mpPhysicsComponent=NULL;

	SteeringComponent(const ComponentID& id, const ComponentID& physicsComponentID);
	~SteeringComponent();
	void setPhysicsComponent(PhysicsComponent* pComp) { mpPhysicsComponent = pComp; };

	friend class ComponentManager;
};