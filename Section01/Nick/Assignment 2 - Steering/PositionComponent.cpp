/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// DeanLib
#include "Trackable.h"
#include "Vector2D.h"

// GraphicsLib

#include "GraphicsSystem.h"

// Project
#include "Component.h"
#include "PositionComponent.h"

//#include "Game.h"

void PositionComponent::wrapCoords()
{
	if (mWrap)
	{
		float width = (float)GraphicsSystem::getDisplayWidth();
		float height = (float)GraphicsSystem::getDisplayHeight();

		float x = mData.pos.getX();
		float y = mData.pos.getY();

		if (x < 0.0f)
		{
			mData.pos.setX(width);
		}
		else if (x > width)
		{
			mData.pos.setX(0.0f);
		}

		if (y < 0.0f)
		{
			mData.pos.setY(height);
		}
		else if (y > height)
		{
			mData.pos.setY(0.0f);
		}
	}
}

void PositionComponent::updateFacing()
{
	mData.facing = fmodf(mData.facing, 2 * M_PI);

	return;
}

void PositionComponent::updateDirection()
{
	mData.direction = Vector2D(cos(mData.facing), -sin(mData.facing));

	return;
}
