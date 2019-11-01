/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <vector>

#include <cassert>
#include <map>
#include <iostream>


// Dean Library
#include "Trackable.h"

#include "Vector2D.h"


// Graphics Library

#include "Color.h"


// Game Library
#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"

#include "Node.h"
#include "Graph.h"
#include "GridGraph.h"
#include "GridVisualizer.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

float lerp(int value, int start, int end)
{
	//returns float representing how far value is between start and end
	assert(start <= end);

	float lerpVal = 0.0f;

	if (start <= end)
	{
		int range = end - start;
		lerpVal = value / (float)range;
	}
	return lerpVal;
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest )
{
	delete mpVisualizer;
	mpVisualizer = new GridVisualizer( pGrid );
	static Color pathColor( 0, 129, 128 );
	static Color visitedColor( 0, 128, 0 );
	static Color startColor = Color(1, 255, 128);
	static Color stopColor = Color(128, 128, 255);

	unsigned int numNodes = mPath.getNumNodes();
	if(numNodes > 0 )
	{
		Color currentPathColor = pathColor;

		for( unsigned int i=0; i< numNodes; i++ )
		{
			mpVisualizer->addColor( mPath.peekNode(i)->getId(), currentPathColor );
			float lerpVal = lerp(i, 0, numNodes);
			currentPathColor = Color((int)(255 * (1.0f - lerpVal)), currentPathColor.getG(), currentPathColor.getB());
		}

		mpVisualizer->addColor( mPath.peekNode(0)->getId(), startColor );
		mpVisualizer->addColor( mPath.peekNode(numNodes-1)->getId(), stopColor );
	}

	mpVisualizer->draw(*pDest);
}
#endif