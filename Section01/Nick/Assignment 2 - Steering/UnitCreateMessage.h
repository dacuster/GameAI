/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class UnitCreateMessage :public GameMessage
{
public:
	UnitCreateMessage(const Sprite& _sprite, Steering::SteeringType _steeringType, int _count = 1);
	~UnitCreateMessage();

	void process();

private:
	Sprite mSprite;
	Steering::SteeringType mSteeringType;
	int mCreateCount = 1;
};