/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

// DeanLib
#include "Trackable.h"
#include "Timer.h"
#include "PerformanceTracker.h"
#include "CircularQueue.h"
#include "MemoryTracker.h"
#include "DataRepository.h"
#include "Vector2D.h"

// GraphicsLib
#include "EventSystem.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Defines.h"

// Project
#include "Game.h"

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv)
{
	EventSystem::initInstance();

	gpPerformanceTracker = new PerformanceTracker;
	gpPerformanceTracker->startTracking("init");

	//create the global game object
	gpGame = new Game;
	//init the game
	bool goodGame = gpGame->init();
	if (!goodGame)
	{
		fprintf(stderr, "failed to initialize Game object!\n");
		return -1;
	}

	gpPerformanceTracker->stopTracking("init");
	cout << "initialization took:" << gpPerformanceTracker->getElapsedTime("init") << "ms\n";

	gpGame->doLoop();

	gpGame->cleanup();
	delete gpGame;
	gpGame = NULL;

	delete gpPerformanceTracker;

	EventSystem::cleanupInstance();

	MemoryTracker::getInstance()->reportAllocations( cout );
	system("pause");

	return 0;
}