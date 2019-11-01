/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

const float MINIMUM_RADIUS = 2.0f;
const float MINIMUM_SLOW_RADIUS = 4.0f;
const float MINIMUM_TIME = 0.001f;

class ArriveSteering : public virtual SeekSteering
{
public:
	ArriveSteering() : SeekSteering() {};
	ArriveSteering(
		const UnitID& ownerID,
		const Vector2D& targetLoc,
		const UnitID& targetID = INVALID_UNIT_ID,
		bool shouldDistance = false,
		float targetRadius = MINIMUM_RADIUS,
		float slowRadius = MINIMUM_SLOW_RADIUS,
		float timeToTarget = MINIMUM_TIME);

private:
	float mTargetRadius = MINIMUM_RADIUS;
	float mSlowRadius = MINIMUM_SLOW_RADIUS;
	float mTimeToTarget = MINIMUM_TIME;

protected:
	void setTargetRadius(float targetRadius);
	const float getTargetRadius() const { return mTargetRadius; };

	void setSlowRadius(float slowRadius);
	const float getSlowRadius() const { return mSlowRadius; };

	void setTimeToTarget(float timeToTarget);
	const float getTimeToTarget() const { return mTimeToTarget; };

	virtual Steering* getSteering();
};