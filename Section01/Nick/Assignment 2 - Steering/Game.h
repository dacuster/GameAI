/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class System;
class GraphicsSystem;
class GraphicsBuffer;
class Font;
class FontManager;
class GraphicsBufferManager;
class SpriteManager;
class GameMessageManager;
class Timer;
class ComponentManager;
class UnitManager;
class DataRepository;
class PerformanceTracker;
// Pathfinding
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;

const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_ICON_SPRITE_ID = 1;
const IDType AI_ICON_SPRITE_ID = 2;
const IDType TARGET_SPRITE_ID = 3;

const IDType COUR_24_FONT_ID = 0;
const int GRID_SIZE_X = 32;
const int GRID_SIZE_Y = 32;
const std::string gFileName = "..\\pathgrid.txt";

class Game:public Trackable
{
public:
	Game();
	~Game();

	bool init();//returns true if no errors, false otherwise
	void cleanup();

	//game loop
	void doLoop();

	inline System* getSystem() const { return mpSystem; };
	inline GraphicsSystem* getGraphicsSystem() const;
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline FontManager* getFontManager() const { return mpFontManager; };
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline ComponentManager* getComponentManager() { return mpComponentManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline DataRepository* getDataRepository() { return mpRepository; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };

	// Pathfinding
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid() { return mpGrid; };
	inline GridGraph* getGridGraph() { return mpGridGraph; };
	inline DebugDisplay* getDebugDisplay() { return mpDebugDisplay; };
	void switchPathfinder(GridPathfinder* pPathfinder);

private:
	System* mpSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	FontManager* mpFontManager;
	GameMessageManager* mpMessageManager;
	ComponentManager* mpComponentManager;
	UnitManager* mpUnitManager;
	DataRepository* mpRepository;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	Font* mpFont;
	float mTimeLastFrame;
	float mTimeMult = 1.0f;
	bool mDrawDebugData = false;
	bool mShouldExit;
	UINT mTargetFPS=0;
	float mTargetElapsedTime = 0.0f;

	// Pathfinding
	Grid* mpGrid;
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph;
	DebugDisplay* mpDebugDisplay;
	GridPathfinder* mpPathfinder;

	//should be somewhere else
	GraphicsBufferID mBackgroundBufferID = "woods";
	GraphicsBufferID mPlayerIconBufferID = "player";
	GraphicsBufferID mEnemyIconBufferID = "enemy";
	GraphicsBufferID mTargetBufferID = "target";

	void beginLoop();
	void processLoop();
	void endLoop();

	void drawDebugData();

	bool mKeyPressedS = false;
	bool mKeyPressedD = false;
	bool mKeyPressedEscape = false;
	bool mMousePressedLeft = false;

};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge

extern Game* gpGame;
extern PerformanceTracker* gpPerformanceTracker;

