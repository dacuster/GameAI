/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <iostream>

#include <vector>
#include <map>


// Dean Library
#include "Trackable.h"
#include "Vector2D.h"

#include "MultiDimensionalArray.h"


// Common Library

#include "Grid.h"


// Game Library
#include "Node.h"
#include "Graph.h"
#include "GridGraph.h"

#include "Connection.h"


GridGraph::GridGraph( Grid* pGrid )
:Graph()
,mpGrid(pGrid)
{
}

GridGraph::~GridGraph()
{
}

void GridGraph::init()
{
	static float sqrt2 = sqrt(2.0f);

	if( mpGrid != NULL )
	{
		int numGridIndices = mpGrid->getGridWidth() * mpGrid->getGridHeight();

		//size the node vector
		mNodes.resize( numGridIndices, NULL );

		float cellHeight = mpGrid->getCellSize().getY();
		
		//go through all elements of the grid and make Nodes for them - also add them to Node vector
		for( int i=0; i<numGridIndices; i++ )
		{
			//create a Node for this location
			Node* pNode = new Node( i );

			std::div_t divResult = std::div(i, (int)cellHeight);
			pNode->setPosition(Vector2D(divResult.rem, divResult.quot));

			//add to NodeVector
			mNodes[i] = pNode;
		}

		//go through all elements of the grid - get adjacencies and create connections for each
		for( int i=0; i<numGridIndices; i++ )
		{
			//get the Node for this location
			Node* pFromNode = mNodes[i];

			//get all the adjacencies
			std::vector<int> adjacencies = mpGrid->getAdjacentIndices( i );

			//create a vector of Connections
			std::vector<Connection*> connections;

			//go through all adjacent indices, get the nodes for them, create connections, and add to connections map
			for( unsigned int adjIndex = 0; adjIndex < adjacencies.size(); adjIndex++ )
			{
				// Get the value of the node.
				int nodeValue = mpGrid->getValueAtIndex(adjacencies[adjIndex]);

				//check for blocking terrain
				if( nodeValue != BLOCKING_VALUE )
				{
					Node* pToNode = mNodes[ adjacencies[adjIndex] ];//find to node

					float cost = nodeValue > BLOCKING_VALUE ? nodeValue * 1.5f : 1.0f;
					if (mpGrid->areCellsDiagonal(pFromNode->getId(), pToNode->getId()))
						cost *= sqrt2;
					Connection* pConnection = new Connection( pFromNode, pToNode, cost );//create a connection

					//add connection to connection vectors
					mConnections.push_back( pConnection );
					connections.push_back( pConnection );
				}
			}

			//put temp connection vector into map
			mConnectionMap[i] = connections;
		}
	}
}
