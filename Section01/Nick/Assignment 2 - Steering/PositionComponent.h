/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

struct PositionData : public Trackable
{
	PositionData() :pos(ZERO_VECTOR2D), facing(0.0f), direction(ZERO_VECTOR2D){};
	PositionData(const Vector2D& thePos, float theFacing) :pos(thePos), facing(theFacing), direction(Vector2D(cos(theFacing), sin(theFacing))) {};

	Vector2D pos;
	Vector2D direction;
	float facing;
};

class PositionComponent : public Component
{
public:
	PositionComponent(const ComponentID& id, bool shouldWrap = true) :Component(id), mWrap(shouldWrap) {};
	~PositionComponent() {};
	
	//getters and setters
	const Vector2D& getPosition() const { return mData.pos; };
	void setPosition(const Vector2D& pos) { mData.pos = pos; wrapCoords(); };
	void modPosition(const Vector2D& mod) { mData.pos += mod; wrapCoords(); };
	float getFacing() const { return mData.facing; };
	void setFacing(float facing) { mData.facing = facing; updateFacing(); updateDirection(); };
	Vector2D getDirection() const { return mData.direction; };
	void modFacing(float mod) { mData.facing += mod; updateFacing(); updateDirection(); };
	const PositionData& getData() const { return mData; };
	void setData(const PositionData& data) { mData = data; wrapCoords(); };
	void modData(const PositionData& data) { mData.pos += data.pos; mData.facing += data.facing; updateFacing(); wrapCoords(); updateDirection(); };

	static const PositionData& getZeroPositionData() { static PositionData data; return data; };

private:
	PositionData mData;
	bool mWrap;//should we wrap around the screen?

	void wrapCoords();
	void updateFacing();
	void updateDirection();

	friend class ComponentManager;
};