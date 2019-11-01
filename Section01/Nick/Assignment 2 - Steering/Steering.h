/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
*/

class Steering: public Trackable
{
public:
	enum SteeringType
	{
		INVALID_TYPE = -1,
		SEEK,
		FLEE,
		ARRIVE,
		DISTANCE,
		FACE,
		NOT_FACE,
		WANDER,
		ARRIVE_AND_FACE,
		WANDER_AND_CHASE,
		FOLLOW_PATH
	};

	//constructors and destructors
	Steering( SteeringType type = INVALID_TYPE ):mType(type), mTargetLoc(ZERO_VECTOR2D), mTargetID(INVALID_UNIT_ID), mOwnerID(INVALID_UNIT_ID), mData(PhysicsComponent::getZeroPhysicsData()) {};
	virtual ~Steering(){};

	//accessors
	void setTargetLoc(const Vector2D& loc) { mTargetLoc = loc; };
	const Vector2D& getTargetLoc() const { return mTargetLoc; };
	void setTargetID(const UnitID& id) { mTargetID = id; };
	const UnitID& getTargetID() const { return mTargetID; };
	void setOwnerID(const UnitID& id) { mOwnerID = id; };
	const PhysicsData& getData() const { return mData; };
	void update();

protected:
	SteeringType mType;
	Vector2D mTargetLoc;
	UnitID mTargetID;
	UnitID mOwnerID;
	PhysicsData mData;

	virtual Steering* getSteering() { return this; };//overridden by sub-classes
};