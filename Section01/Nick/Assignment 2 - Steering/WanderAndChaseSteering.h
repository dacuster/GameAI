/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

const float MINIMUM_CHASE_RADIUS = 40.0f;

class WanderAndChaseSteering
	: public WanderSteering, public ArriveSteering, public FaceSteering
{
public:
	WanderAndChaseSteering(
		const UnitID& ownerID,
		const Vector2D& targetLoc,
		const UnitID& targetID = INVALID_UNIT_ID,
		float chaseRadius = MINIMUM_CHASE_RADIUS,
		float wanderRadius = MINIMUM_WANDER_RADIUS,
		float targetRadius = MINIMUM_RADIUS,
		float slowRadius = MINIMUM_SLOW_RADIUS,
		float timeToTarget = MINIMUM_TIME,
		float viewAngle = MINIMUM_VIEW_ANGLE,
		float outerViewAngle = MINIMUM_OUTER_ANGLE,
		float timeToView = MINIMUM_TIME_TO_VIEW);

private:
	float mChaseRadius = MINIMUM_CHASE_RADIUS;

protected:
	virtual Steering* getSteering();
};

