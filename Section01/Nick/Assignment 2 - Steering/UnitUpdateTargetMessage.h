/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class UnitUpdateTargetMessage :public GameMessage
{
public:
	UnitUpdateTargetMessage(const Vector2D& _position, const UnitID& _id);
	~UnitUpdateTargetMessage();

	void process();

private:
	Vector2D mPosition;
	UnitID mId;
};