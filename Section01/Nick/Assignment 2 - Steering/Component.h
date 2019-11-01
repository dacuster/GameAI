/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

#include <limits>

// DeanLib
#include "Trackable.h"
#include "DeanLibDefines.h"


typedef Uint32 ComponentID;
const Uint32 INVALID_COMPONENT_ID = UINT_MAX;

class Component : public Trackable
{
public:
	Component(const ComponentID& id) :mID(id){};
	virtual ~Component(){};

	inline ComponentID getID(){ return mID; };

private:
	ComponentID mID;
};