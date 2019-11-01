/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

// C++ Library
#include <string>

// Dean Library
#include "Trackable.h"

class DebugContent : public Trackable
{
public:
	DebugContent(){};
	virtual ~DebugContent(){};

	virtual std::string getDebugString() = 0;
};