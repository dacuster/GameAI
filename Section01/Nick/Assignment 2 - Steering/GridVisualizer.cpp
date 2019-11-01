// C++ Library
#include <vector>
#include <map>

// DeanLib Library
#include "Trackable.h"

#include "Vector2D.h"
#include "MultiDimensionalArray.h"
#include "Timer.h"
#include "Defines.h"

// Graphics Library

#include "Color.h"
#include "GraphicsSystem.h"
#include "System.h"

// Common Library
#include "GridVisualizer.h"

#include "Grid.h"
#include "Game.h"


GridVisualizer::GridVisualizer( Grid* pGrid )
:mpGrid(pGrid)
,mDirty(true)
{
}

GridVisualizer::~GridVisualizer()
{
}

void GridVisualizer::refresh()
{
	const Color& black = BLACK_COLOR;
	const Color& green = Color(36, 112, 21);
	const Color& gray = Color(94, 94, 94);

	if( mDirty )
	{
		//remove old entries first
		removeAllEntriesOfColor(black);
		removeAllEntriesOfColor(green);
		removeAllEntriesOfColor(gray);

		int size = mpGrid->getGridWidth() * mpGrid->getGridHeight();
		//get any non-zero squares and send them to the visualizer
		for( int i=0; i<size; i++ )
		{
			if (mpGrid->getValueAtIndex(i) == BLOCKING_VALUE)
			{
				addColor(i, black);
			}
			else if (mpGrid->getValueAtIndex(i) == MOUNTAIN_VALUE)
			{
				addColor(i, gray);
			}
			else if (mpGrid->getValueAtIndex(i) == SWAMP_VALUE)
			{
				addColor(i, green);
			}
		}
	}
	mDirty = false;
}

void GridVisualizer::addColor( int index, const Color& color )
{
	//set dirty flag
	mDirty = true;

	//find the existing entry in the map (if it exists)
	auto iter = mColormap.find( color );

	if( iter != mColormap.end() )//found the existing entry
	{
		iter->second.push_back( index );
	}
	else
	{
		//create a vector to put in the map
		std::vector<int> colorVector;
		colorVector.push_back( index );

		//put the vector into the map
		mColormap[color] = colorVector;
	}
}

void GridVisualizer::removeAllEntriesOfColor( const Color& color )
{
	//find the existing entry in the map (if it exists)
	auto iter = mColormap.find( color );
	
	if( iter != mColormap.end() )
	{
		mColormap.erase( iter );
	}
}

void GridVisualizer::draw( GraphicsBuffer& dest )
{
	if( mDirty )
	{
		refresh();
	}

	int gridHeight = mpGrid->getGridHeight();
	int gridWidth = mpGrid->getGridWidth();
	int numSquares = gridWidth * gridHeight;
	Vector2D cellSize = mpGrid->getCellSize();
	int xSize = (int)cellSize.getX();
	int ySize = (int)cellSize.getY();

	GraphicsSystem* pGraphicsSystem = gpGame->getGraphicsSystem();

	for( auto iter = mColormap.begin(); iter != mColormap.end(); ++iter )
	{
		std::vector<int> theIndices = iter->second;

		for( unsigned int i=0; i<theIndices.size(); i++ )
		{
			Vector2D ulPos = mpGrid->getULCornerOfCell( theIndices[i] );
			//pGraphicsSystem->renderFilledRect(*pGraphicsSystem->getBackBuffer(), ulPos, xSize, ySize, iter->first);
		}
	}
}