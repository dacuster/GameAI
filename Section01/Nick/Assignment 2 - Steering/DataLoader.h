/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class DataRepository;

class DataLoader : public Trackable
{
public:
	DataLoader( const std::string& filename, DataRepository* pDepository );
	~DataLoader(){};
};

//class only exists to hold a class level enum
class DataKeyEnum
{
public:
	enum DataKeyVals
	{
		TARGET_FPS,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		MAX_UNITS,
		MAX_ACC,
		MAX_SPEED,
		MAX_ROT_ACC,
		MAX_ROT_VEL,
		DEFAULT_ASSET_DIRECTORY,
		ARROW_ICON,
		ENEMY_ARROW_ICON,
		TARGET_ICON,
		COURRIER_FONT,
		BACKGROUND_IMAGE,
		FONT_SIZE,
		ARRIVE_RADIUS,
		ARRIVE_SLOW_RADIUS,
		ARRIVE_TIME,
		VIEW_ANGLE,
		OUTER_VIEW_ANGLE,
		TIME_TO_VIEW,
		WANDER_ARRIVE_RADIUS,
		CHASE_RADIUS,
		CREATE_UNIT_COUNT
	};
};