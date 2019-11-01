/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// DeanLib
#include "Trackable.h"

// Project
#include "GameMessage.h"

GameMessage::GameMessage(MessageType type)
	:mType(type)
	,mSubmittedTime(0)
	,mScheduledTime(0)
{
}

GameMessage::~GameMessage()
{
}