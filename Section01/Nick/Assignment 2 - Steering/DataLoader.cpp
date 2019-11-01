/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#include <string>

#include <fstream>
#include <sstream>

// DeanLib
#include "Trackable.h"
#include "DataRepository.h"

// Project
#include "DataLoader.h"

DataLoader::DataLoader(const std::string& filename, DataRepository* pRepository)
{
	std::ifstream input( filename );
	if( input.good() )
	{
		while( !input.eof() )
		{
			std::string line;
			std::getline( input, line);
			std::stringstream sstream( line );
			std::string id;
			sstream >> id;

			if( id == "screen_size" )
			{
				UINT width, height;
				sstream >> width >> height;
				pRepository->addEntry( DataKeyEnum::SCREEN_WIDTH, width );
				pRepository->addEntry( DataKeyEnum::SCREEN_HEIGHT, height );
			}
			else if (id == "target_fps")
			{
				UINT fps;
				sstream >> fps;
				pRepository->addEntry(DataKeyEnum::TARGET_FPS, fps);
			}
			else if (id == "max_units")
			{
				UINT max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_UNITS, max);
			}
			else if (id == "unit_max_acc")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_ACC, max);
			}
			else if (id == "unit_max_speed")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_SPEED, max);
			}
			else if (id == "unit_max_rot_acc")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_ROT_ACC, max);
			}
			else if (id == "unit_max_rot_vel")
			{
				float max;
				sstream >> max;
				pRepository->addEntry(DataKeyEnum::MAX_ROT_VEL, max);
			}
			else if (id == "default_asset_directory")
			{
				std::string directory;
				sstream >> directory;
				pRepository->addEntry(DataKeyEnum::DEFAULT_ASSET_DIRECTORY, directory);
			}
			else if (id == "arrow_icon")
			{
				std::string arrowIcon;
				sstream >> arrowIcon;
				pRepository->addEntry(DataKeyEnum::ARROW_ICON, arrowIcon);
			}
			else if (id == "enemy_arrow_icon")
			{
				std::string enemyArrowIcon;
				sstream >> enemyArrowIcon;
				pRepository->addEntry(DataKeyEnum::ENEMY_ARROW_ICON, enemyArrowIcon);
			}
			else if (id == "target_icon")
			{
				std::string targetIcon;
				sstream >> targetIcon;
				pRepository->addEntry(DataKeyEnum::TARGET_ICON, targetIcon);
			}
			else if (id == "background_image")
			{
				std::string backgroundImage;
				sstream >> backgroundImage;
				pRepository->addEntry(DataKeyEnum::BACKGROUND_IMAGE, backgroundImage);
			}
			else if (id == "courrier_font")
			{
				std::string courrierFont;
				sstream >> courrierFont;
				pRepository->addEntry(DataKeyEnum::COURRIER_FONT, courrierFont);
			}
			else if (id == "font_size")
			{
				int fontSize;
				sstream >> fontSize;
				pRepository->addEntry(DataKeyEnum::FONT_SIZE, fontSize);
			}
			else if (id == "arrive_radius")
			{
				float arriveRadius;
				sstream >> arriveRadius;
				pRepository->addEntry(DataKeyEnum::ARRIVE_RADIUS, arriveRadius);
			}
			else if (id == "arrive_slow_radius")
			{
				float arriveSlowRadius;
				sstream >> arriveSlowRadius;
				pRepository->addEntry(DataKeyEnum::ARRIVE_SLOW_RADIUS, arriveSlowRadius);
			}
			else if (id == "arrive_time")
			{
				float arriveTime;
				sstream >> arriveTime;
				pRepository->addEntry(DataKeyEnum::ARRIVE_TIME, arriveTime);
			}
			else if (id == "view_angle")
			{
				float viewAngle;
				sstream >> viewAngle;
				pRepository->addEntry(DataKeyEnum::VIEW_ANGLE, viewAngle);
			}
			else if (id == "outer_view_angle")
			{
				float outerViewAngle;
				sstream >> outerViewAngle;
				pRepository->addEntry(DataKeyEnum::OUTER_VIEW_ANGLE, outerViewAngle);
			}
			else if (id == "time_to_view")
			{
				float timeToView;
				sstream >> timeToView;
				pRepository->addEntry(DataKeyEnum::TIME_TO_VIEW, timeToView);
			}
			else if (id == "wander_arrive_radius")
			{
				float wanderArriveRadius;
				sstream >> wanderArriveRadius;
				pRepository->addEntry(DataKeyEnum::WANDER_ARRIVE_RADIUS, wanderArriveRadius);
			}
			else if (id == "chase_radius")
			{
				float chaseRadius;
				sstream >> chaseRadius;
				pRepository->addEntry(DataKeyEnum::CHASE_RADIUS, chaseRadius);
			}
			else if (id == "create_unit_count")
			{
				int createUnitCount;
				sstream >> createUnitCount;
				pRepository->addEntry(DataKeyEnum::CREATE_UNIT_COUNT, createUnitCount);
			}
			else
			{
			std::cout << "Unknown tag:" << id << std::endl;
			}
		}
	}
}