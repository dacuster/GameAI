/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

const float MINIMUM_WANDER_RADIUS = 2.0f;

class WanderSteering : public virtual SeekSteering
{
public:
	WanderSteering() :SeekSteering() {};
	WanderSteering(
		const UnitID& ownerID,
		const Vector2D& targetLoc,
		const UnitID& targetID = INVALID_UNIT_ID,
		float wanderRadius = MINIMUM_WANDER_RADIUS);

private:
	float mMinimumWanderRadius = MINIMUM_WANDER_RADIUS;

protected:
	void setMinimumWanderRadius(float minimumWanderRadius);
	const float getMinimumWanderRadius() const { return mMinimumWanderRadius; };

	Vector2D getRandomPosition();

	virtual Steering* getSteering();
};

