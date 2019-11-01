/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>

// DeanLib
#include "Trackable.h"
#include "PerformanceTracker.h"
#include "DataRepository.h"
#include "Vector2D.h"
#include "Timer.h"

#include "DeanLibDefines.h"
#include "MemoryPool.h"
#include "CircularQueue.h"

// GraphicsLib
#include "Defines.h"

#include "System.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "FontManager.h"
#include "GraphicsBufferManager.h"
#include "InputSystem.h"
#include "Sprite.h"
#include "SpriteManager.h"

// Project
#include "Game.h"

#include "Component.h"
#include "DataLoader.h"
#include "PhysicsComponent.h"
#include "Steering.h"
#include "PositionComponent.h"
#include "SteeringComponent.h"
#include "Unit.h"
#include "GameMessageManager.h"
#include "GameMessage.h"
#include "UnitManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitCreateMessage.h"
#include "UnitDestroyMessage.h"
#include "ComponentManager.h"

Game* gpGame = NULL;

Game::Game()
	:Trackable("game class")
	,mpSystem(NULL)
	,mpGraphicsBufferManager(NULL)
	,mpSpriteManager(NULL)
	,mpFontManager(NULL)
	,mpLoopTimer(NULL)
	,mpMasterTimer(NULL)
	,mpFont(NULL)
	,mShouldExit(false)
	,mBackgroundBufferID("")
	,mpMessageManager(NULL)
	,mpComponentManager(NULL)
	,mpUnitManager(NULL)
	,mpRepository(NULL)
	,mTimeLastFrame(0.0f)
{
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	mShouldExit = false;

	//create Timers
	mpLoopTimer = new Timer;
	mpMasterTimer = new Timer;

	mpRepository = new DataRepository;
	DataLoader loader("data.txt", mpRepository);

	//create and init GraphicsSystem
	mpSystem = new System();
	bool goodGraphics = mpSystem->init( mpRepository->getEntry(DataKeyEnum::SCREEN_WIDTH).getUIntVal(), mpRepository->getEntry(DataKeyEnum::SCREEN_HEIGHT).getUIntVal());
	if(!goodGraphics) 
	{
		fprintf(stderr, "failed to initialize GraphicsSystem object!\n");
		return false;
	}

	mpGraphicsBufferManager = new GraphicsBufferManager(mpSystem->getGraphicsSystem());
	mpSpriteManager = new SpriteManager;
	mpFontManager = new FontManager;

	mpMessageManager = new GameMessageManager();

	UINT maxUnits = mpRepository->getEntry(DataKeyEnum::MAX_UNITS).getUIntVal();
	mpComponentManager = new ComponentManager(maxUnits);
	mpUnitManager = new UnitManager(maxUnits);

	//load buffers
	GraphicsBuffer* pBuff;

	std::string defaultDirectory = mpRepository->getEntry(DataKeyEnum::DEFAULT_ASSET_DIRECTORY).getStringVal();

	pBuff = mpGraphicsBufferManager->loadBuffer(mBackgroundBufferID, defaultDirectory + mpRepository->getEntry(DataKeyEnum::BACKGROUND_IMAGE).getStringVal());
	pBuff = mpGraphicsBufferManager->loadBuffer(mPlayerIconBufferID, defaultDirectory + mpRepository->getEntry(DataKeyEnum::ARROW_ICON).getStringVal());
	pBuff = mpGraphicsBufferManager->loadBuffer(mEnemyIconBufferID, defaultDirectory + mpRepository->getEntry(DataKeyEnum::ENEMY_ARROW_ICON).getStringVal());
	pBuff = mpGraphicsBufferManager->loadBuffer(mTargetBufferID, defaultDirectory + mpRepository->getEntry(DataKeyEnum::TARGET_ICON).getStringVal());

	//load Font
	mpFont = mpFontManager->createAndManageFont(COUR_24_FONT_ID, defaultDirectory + mpRepository->getEntry(DataKeyEnum::COURRIER_FONT).getStringVal(), mpRepository->getEntry(DataKeyEnum::FONT_SIZE).getIntVal());
	
	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( mBackgroundBufferID );
	if( pBackGroundBuffer != NULL )
	{

		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, (float)pBackGroundBuffer->getWidth(), (float)pBackGroundBuffer->getHeight() );
	}
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer( mPlayerIconBufferID );
	Sprite* pArrowSprite = NULL;
	if( pPlayerBuffer != NULL )
	{
		pArrowSprite = mpSpriteManager->createAndManageSprite( PLAYER_ICON_SPRITE_ID, pPlayerBuffer, 0, 0, (float)pPlayerBuffer->getWidth(), (float)pPlayerBuffer->getHeight() );
	}
	GraphicsBuffer* pAIBuffer = mpGraphicsBufferManager->getBuffer(mEnemyIconBufferID);
	Sprite* pEnemyArrow = NULL;
	if (pAIBuffer != NULL)
	{
		pEnemyArrow = mpSpriteManager->createAndManageSprite(AI_ICON_SPRITE_ID, pAIBuffer, 0, 0, (float)pAIBuffer->getWidth(), (float)pAIBuffer->getHeight());
	}

	GraphicsBuffer* pTargetBuffer = mpGraphicsBufferManager->getBuffer(mTargetBufferID);
	if (pTargetBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(TARGET_SPRITE_ID, pTargetBuffer, 0, 0, (float)pTargetBuffer->getWidth(), (float)pTargetBuffer->getHeight());
	}

	//setup units
	Unit* pUnit = NULL;

	if (pArrowSprite)
	{
		pUnit = mpUnitManager->createPlayerUnit(*pArrowSprite, false, PositionData(Vector2D(GraphicsSystem::getDisplayWidth() / 2.0f, GraphicsSystem::getDisplayHeight() / 2.0f), 0.0f));
		pUnit->setShowTarget(true);
		pUnit->setSteering(Steering::ARRIVE_AND_FACE, Vector2D((int)GraphicsSystem::getDisplayWidth(), (int)GraphicsSystem::getDisplayHeight()));
	}

	mTargetFPS = mpRepository->getEntry(DataKeyEnum::TARGET_FPS).getUIntVal();
	mTargetElapsedTime = 1000.0f / mTargetFPS;

	return true;
}

void Game::cleanup()
{
	//delete the timers
	delete mpLoopTimer;
	mpLoopTimer = NULL;
	delete mpMasterTimer;
	mpMasterTimer = NULL;

	delete mpFontManager;
	mpFontManager = NULL;

	delete mpRepository;
	mpRepository = NULL;

	mpFont = NULL;

	//delete the graphics system
	delete mpSystem;
	mpSystem = NULL;

	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = NULL;
	delete mpSpriteManager;
	mpSpriteManager = NULL;
	delete mpMessageManager;
	mpMessageManager = NULL;
	delete mpUnitManager;
	mpUnitManager = NULL;
	delete mpComponentManager;
	mpComponentManager = NULL;
}

void Game::doLoop()
{
	//game loop
	while (!mShouldExit)
	{
		gpPerformanceTracker->clearTracker("loop");
		gpPerformanceTracker->startTracking("loop");

		gpGame->beginLoop();

		gpPerformanceTracker->clearTracker("process");
		gpPerformanceTracker->startTracking("process");

		gpGame->processLoop();

		gpPerformanceTracker->stopTracking("process");

		gpGame->endLoop();

		gpPerformanceTracker->stopTracking("loop");
		std::cout << "loop took:" << gpPerformanceTracker->getElapsedTime("loop") << "ms    ";
		std::cout << "processing took:" << gpPerformanceTracker->getElapsedTime("process") << "ms\n";
		mTimeLastFrame = (float)gpPerformanceTracker->getElapsedTime("loop");
	}
}

void Game::beginLoop()
{
	mpLoopTimer->start();
}

void Game::processLoop()
{
	InputSystem* pInputSystem = mpSystem->getInputSystem();

	float dt = (mTargetElapsedTime * mTimeMult) / 1000.0f;
	mpUnitManager->updateAll(dt);
	mpComponentManager->update(dt);
	pInputSystem->update(dt);

	Sprite* pBackgroundSprite = mpSpriteManager->getSprite(BACKGROUND_SPRITE_ID);
	GraphicsSystem::draw(Vector2D(0, 0), *pBackgroundSprite);

	//draw units
	mpUnitManager->drawAll();

	if (mDrawDebugData)
	{
		drawDebugData();
	}

	mpSystem->getGraphicsSystem()->flip();

	Vector2D pos = pInputSystem->getCurrentMousePos();

	mpMessageManager->processMessagesForThisframe();

	if (pInputSystem->isMouseButtonPressed(InputSystem::LEFT))
	{
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::M_KEY))
	{
		int count = getDataRepository()->getEntry(DataKeyEnum::CREATE_UNIT_COUNT).getIntVal();
		GameMessage* pMessage = new UnitCreateMessage(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), Steering::WANDER_AND_CHASE, count);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	
	if (pInputSystem->isKeyPressed(InputSystem::X_KEY))
	{
		GameMessage* pMessage = new UnitDestroyMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if(pInputSystem->isKeyPressed(InputSystem::ESCAPE_KEY))
	{
		mShouldExit = true;
	}

	if (pInputSystem->isKeyPressed(InputSystem::UP_KEY))
	{
		// Initialize an invalid steering type.
		Steering::SteeringType steeringType = Steering::INVALID_TYPE;

		// Set steering based on 'F' key pressed state.
		if (pInputSystem->isKeyPressed(InputSystem::F_KEY))
		{
			steeringType = Steering::FLEE;
		}
		else
		{
			steeringType = Steering::ARRIVE;
		}

		GameMessage* pMessage = new UnitCreateMessage(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), steeringType);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}
	else if (pInputSystem->isKeyPressed(InputSystem::DOWN_KEY))
	{
		GameMessage* pMessage = new UnitDestroyMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::A_KEY))
	{
		GameMessage* pMessage = new UnitCreateMessage(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), Steering::WANDER_AND_CHASE);
		MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

	if (pInputSystem->isKeyPressed(InputSystem::LEFT_KEY))
	{
		mTimeMult -= 0.1f;
		if (mTimeMult < 0.0f)
			mTimeMult = 0.0f;
	}
	else if (pInputSystem->isKeyPressed(InputSystem::RIGHT_KEY))
	{
		mTimeMult += 0.1f;
	}
	else if (pInputSystem->isKeyPressed(InputSystem::SPACE_KEY))
	{
		mTimeMult = 1.0f;
	}

	if (pInputSystem->isKeyPressed(InputSystem::D_KEY))
	{
		mDrawDebugData = true;
	}
	else
	{
		mDrawDebugData = false;
	}
}

void Game::endLoop()
{
	mpLoopTimer->sleepUntilElapsed( mTargetElapsedTime );
}

void Game::drawDebugData()
{
	InputSystem* pInputSystem = mpSystem->getInputSystem();

	Vector2D pos = pInputSystem->getCurrentMousePos();

	//create mouse text
	std::stringstream textStream;
	textStream << pos;

	//write text at mouse position
	GraphicsSystem::writeText(pos, *mpFont, BLACK_COLOR, textStream.str(), Font::RIGHT);

	textStream.str("");
	textStream.clear();

	//write out current number of Units
	Uint32 numUnits = mpUnitManager->getNumUnits();
	textStream << "Units:" << numUnits;
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth(), 0), *mpFont, BLACK_COLOR, textStream.str(), Font::RIGHT);

	textStream.str("");
	textStream.clear();

	//write out current fps
	int fps = (int)((1000.0f / mTimeLastFrame) + .5f);//+.5f does rounding
	textStream << "FPS:" << fps;
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() / 2, 0), *mpFont, BLACK_COLOR, textStream.str(), Font::CENTER);

	textStream.str("");
	textStream.clear();

	//write out time multiple
	textStream << "time mult:" << mTimeMult;
	GraphicsSystem::writeText(Vector2D(GraphicsSystem::getDisplayWidth() / 4, 0), *mpFont, BLACK_COLOR, textStream.str(), Font::CENTER);
}

GraphicsSystem* Game::getGraphicsSystem() const
{
	return mpSystem->getGraphicsSystem();
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

float genRandomFloat()
{
	float r = (float)rand()/(float)RAND_MAX;
	return r;
}