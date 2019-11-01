/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <cassert>

// DeanLib
#include "Trackable.h"
#include "CircularQueue.h"

#include "Timer.h"
#include "PerformanceTracker.h"

// GraphicsLib

#include "Defines.h"

// Project
#include "GameMessageManager.h"

#include "Game.h"
#include "GameMessage.h"

GameMessageManager::GameMessageManager(Uint32 size)
{
	mMessages = new CircularQueue<GameMessage *>(size);
}

GameMessageManager::~GameMessageManager()
{
	GameMessage* pMessage;
	while( mMessages->popFront(pMessage))
	{
		delete pMessage;
	}

	delete mMessages;
}

void GameMessageManager::processMessagesForThisframe()
{
	double currentTime = gpGame->getCurrentTime();
	GameMessage* pMessage;

	while(mMessages->popFront(pMessage))
	{
		if( pMessage->getScheduledTime() <= currentTime )
		{
			pMessage->process();
			delete pMessage;
		}
		else
		{
			//not time to process yet - push to back
			mMessages->pushBack(pMessage);
		}
	}
}

void GameMessageManager::addMessage( GameMessage* pMessage, int delay )
{
	double currentTime = gpGame->getCurrentTime();

	//set frame numbers
	pMessage->mSubmittedTime = currentTime;
	pMessage->mScheduledTime = currentTime + delay;

	//put it in the message list
	bool success = mMessages->pushBack( pMessage );
	assert(success);
}