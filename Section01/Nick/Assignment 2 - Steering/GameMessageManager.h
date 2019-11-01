/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class GameMessage;

class GameMessageManager: public Trackable
{
public:
	explicit GameMessageManager(Uint32 size=64);
	~GameMessageManager();

	void addMessage( GameMessage* pMessage, int delay );//note - message manager will now "own" the message and will delete it at its pleasure
	void processMessagesForThisframe();

private:
	CircularQueue<GameMessage*>* mMessages;
};