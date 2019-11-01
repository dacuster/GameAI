/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class SwitchPathfindingMessage : public GameMessage
{
public:
	SwitchPathfindingMessage(const PathfindingType type);
	~SwitchPathfindingMessage();

	void process();

private:
	PathfindingType mType = INVALID;
};
