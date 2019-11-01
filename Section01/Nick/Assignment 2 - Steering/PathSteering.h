#pragma once

class PathSteering :
	public ArriveSteering, public FaceSteering
{
public:
	PathSteering(
		const UnitID& ownerID,
		const Vector2D& targetLoc,
		const UnitID& targetID = INVALID_UNIT_ID,
		float targetRadius = MINIMUM_RADIUS,
		float slowRadius = MINIMUM_SLOW_RADIUS,
		float timeToTarget = MINIMUM_TIME,
		float viewAngle = MINIMUM_VIEW_ANGLE,
		float outerViewAngle = MINIMUM_OUTER_ANGLE,
		float timeToView = MINIMUM_TIME_TO_VIEW);

	void setPath(Path path);
	void newPath(Vector2D destination);

protected:
	virtual Steering* getSteering();

private:
	Path mPath;
	int pathIndex = 0;
};