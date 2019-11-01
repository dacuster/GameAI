#pragma once

class PathSteering : public Steering
{
public:
	PathSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID);

	void setPath(Path path);
	void newPath(Vector2D destination);

protected:
	virtual Steering* getSteering();

private:
	Path mpPath;
	int pathIndex = 0;
};