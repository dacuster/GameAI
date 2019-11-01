/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class UnitDestroyMessage : public GameMessage
{
public:
	UnitDestroyMessage();
	~UnitDestroyMessage();

	void process();
};