/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

const float MINIMUM_VIEW_ANGLE = 1.0f;
const float MINIMUM_OUTER_ANGLE = 5.0f;
const float MINIMUM_TIME_TO_VIEW = 0.001;

class FaceSteering
	: public virtual Steering
{
public:
	FaceSteering() : Steering() {};
	FaceSteering(
		  const UnitID& ownerID
		, const Vector2D& targetLoc
		, const UnitID& targetID = INVALID_UNIT_ID
		, bool shouldFace = true
		, float viewAngle = MINIMUM_VIEW_ANGLE
		, float outerViewAngle = MINIMUM_OUTER_ANGLE
		, float timeToView = MINIMUM_TIME_TO_VIEW);

private:
	float mViewAngle = MINIMUM_VIEW_ANGLE;
	float mOuterViewAngle = MINIMUM_OUTER_ANGLE;
	float mTimeToView = MINIMUM_TIME_TO_VIEW;

protected:
	void radiansToDegrees(float& angle) { angle *= (180.0f / (float)M_PI); };

	void setViewAngle(float viewAngle);
	const float getViewAngle() const { return mViewAngle; };

	void setOuterViewAngle(float outerViewAngle);
	const float getOuterViewAngle() const { return mOuterViewAngle; };

	void setTimeToView(float timeToView);
	const float getTimeToView() const { return mTimeToView; };

	virtual Steering* getSteering();
};

