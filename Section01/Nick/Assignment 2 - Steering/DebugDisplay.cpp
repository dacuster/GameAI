/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <string>


// Dean Library
#include "Trackable.h"
#include "Vector2D.h"

#include "Timer.h"
#include "Defines.h"


// Graphics Library

#include "Color.h"
#include "System.h"
#include "GraphicsSystem.h"
#include "FontManager.h"
#include "Font.h"


// Game Library
#include "DebugDisplay.h"

#include "DebugContent.h"
#include "Game.h"


DebugDisplay::DebugDisplay( const Vector2D& pos, DebugContent* pContent )
	:mPos(pos)
	,mpContent(pContent)
{
}

DebugDisplay::~DebugDisplay()
{
	delete mpContent;
}

void DebugDisplay::draw( GraphicsBuffer* pTarget )
{
	std::string toDisplay = mpContent->getDebugString();
	//gpGame->getGraphicsSystem()->writeText(*pTarget, mPos, *gpGame->getFontManager()->getFont(COUR_24_FONT_ID), RED_COLOR, toDisplay);

}

void DebugDisplay::updateContent(DebugContent* pContent)
{
	// Delete the old content.
	delete mpContent;

	// Assign the new content to the member content.
	mpContent = pContent;

	return;
}
