/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <fstream>
#include <vector>
#include <list>

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
#include "MultiDimensionalArray.h"

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
#include "Grid.h"
#include "GridVisualizer.h"
#include "Node.h"
#include "Graph.h"
#include "GridGraph.h"
#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"
#include "DepthFirstPathfinder.h"
#include "DebugContent.h"
#include "PathfindingDebugContent.h"
#include "DebugDisplay.h"
#include "PathToMessage.h"
#include "SwitchPathfindingMessage.h"

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
	,mpGrid(NULL)
	,mpGridGraph(NULL)
	,mpPathfinder(NULL)
	,mpDebugDisplay(NULL)
	,mpGridVisualizer(NULL)
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

	GraphicsSystem* pGraphicsSystem = getGraphicsSystem();

	//create and load the Grid, GridBuffer, and GridVisualizer
	mpGrid = new Grid(pGraphicsSystem->getDisplayWidth(), pGraphicsSystem->getDisplayHeight(), GRID_SIZE_X, GRID_SIZE_Y);
	mpGridVisualizer = new GridVisualizer(mpGrid);
	std::ifstream theStream(gFileName);
	mpGrid->load(theStream);

	//create the GridGraph for pathfinding
	mpGridGraph = new GridGraph(mpGrid);
	//init the nodes and connections
	mpGridGraph->init();

	// Create a default pathfinder.
	mpPathfinder = new DepthFirstPathfinder(mpGridGraph);

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

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent(mpPathfinder);
	mpDebugDisplay = new DebugDisplay(Vector2D(0, 12), pContent);


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

	delete mpGrid;
	mpGrid = NULL;

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpGridGraph;
	mpGridGraph = NULL;

	delete mpPathfinder;
	mpPathfinder = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;
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

	GraphicsSystem* pGraphicsSystem = getGraphicsSystem();
	//get back buffer
	GraphicsBuffer* pBackBuffer = pGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw(*pBackBuffer);
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
	mpPathfinder->drawVisualization(mpGrid, pBackBuffer);
#endif


	float dt = (mTargetElapsedTime * mTimeMult) / 1000.0f;
	mpUnitManager->updateAll(dt);
	mpComponentManager->update(dt);
	pInputSystem->update(dt);

	Sprite* pBackgroundSprite = mpSpriteManager->getSprite(BACKGROUND_SPRITE_ID);
	GraphicsSystem::draw(Vector2D(0, 0), *pBackgroundSprite);

	//draw units
	mpUnitManager->drawAll();

	mpDebugDisplay->draw(pBackBuffer);

	if (mDrawDebugData)
	{
		drawDebugData();
	}

	mpSystem->getGraphicsSystem()->flip();

	Vector2D pos = pInputSystem->getCurrentMousePos();

	MESSAGE_MANAGER->processMessagesForThisframe();

	// TODO: Add path to message for mouse clicks.
	if (pInputSystem->isMouseButtonPressed(InputSystem::LEFT) && !mMousePressedLeft)
	{
		mMousePressedLeft = true;

		static Vector2D lastPos(0.0f, 0.0f);
		Vector2D pos = pInputSystem->getCurrentMousePos();
		if ((lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY()) && mpGrid->getValueAtPixelXY((int)pos.getX(), (int)pos.getY()) != BLOCKING_VALUE)
		{
			std::unordered_map<UnitID, Unit*> unitMap = mpUnitManager->getAllUnits();

			for (std::unordered_map<UnitID, Unit*>::iterator iterator = unitMap.begin(); iterator != unitMap.end(); ++iterator)
			{
				Vector2D position = iterator->second->getPositionComponent()->getPosition();
				GameMessage* pMessage = new PathToMessage(position, pos, iterator->first);
				MESSAGE_MANAGER->addMessage(pMessage, 0);
			}

			lastPos = pos;
		}
	}
	else if (!pInputSystem->isMouseButtonPressed(InputSystem::LEFT))
	{
		mMousePressedLeft = false;
	}

	if(pInputSystem->isKeyPressed(InputSystem::ESCAPE_KEY) && !mKeyPressedEscape)
	{
		mKeyPressedEscape = true;
		mShouldExit = true;
	}
	else if (!pInputSystem->isKeyPressed(InputSystem::ESCAPE_KEY))
	{
		mKeyPressedEscape = false;
	}

	if (pInputSystem->isKeyPressed(InputSystem::S_KEY) && !mKeyPressedS)
	{
		mKeyPressedS = true;

		GameMessage* pDestroyMessage = new UnitDestroyMessage();
		MESSAGE_MANAGER->addMessage(pDestroyMessage, 0);
		
		GameMessage* pCreateMessage = new UnitCreateMessage(*mpSpriteManager->getSprite(AI_ICON_SPRITE_ID), Steering::FOLLOW_PATH, 10);
		MESSAGE_MANAGER->addMessage(pCreateMessage, 0);
	}
	else if (!pInputSystem->isKeyPressed(InputSystem::S_KEY))
	{
		mKeyPressedS = false;
	}

	if (pInputSystem->isKeyPressed(InputSystem::D_KEY) && !mKeyPressedD)
	{
		mKeyPressedD = true;
		mDrawDebugData = !mDrawDebugData;
	}
	else if (!pInputSystem->isKeyPressed(InputSystem::D_KEY))
	{
		mKeyPressedD = false;
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

void Game::switchPathfinder(GridPathfinder* pPathfinder)
{
	delete mpPathfinder;

	mpPathfinder = pPathfinder;

	return;
}