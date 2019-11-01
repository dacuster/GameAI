/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

// C++ Library
#include <vector>

#include <map>
#include <queue>
#include <iostream>


// Dean Library
#include "Trackable.h"

#include "Timer.h"
#include "Defines.h"
#include "PerformanceTracker.h"
#include "Vector2D.h"


// Graphics Library

#include "System.h"


// Common Library

#include "Game.h"


// Game Library
#include "Pathfinder.h"
#include "Path.h"
#include "GridPathfinder.h"
#include "AStarPathfinder.h"

#include "Node.h"
#include "Graph.h"
#include "Connection.h"
#include "GridGraph.h"
#include "PriorityQueueHack.h"


AStarPathfinder::AStarPathfinder(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
	mType = A_STAR;
}

AStarPathfinder::~AStarPathfinder()
{
}

Path AStarPathfinder::findPath(Node* pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	// List of previous nodes to key nodes.
	std::map<Node*, Node*> previousNode;

	// Map of visited nodes.
	std::map<Node*, bool> visitedNodes;

	// Is target accessible and found.
	bool foundTargetNode = false;

#ifdef VISUALIZE_PATH
	mPath.clear();
	mVisitedNodes.clear();
	//mVisitedNodes.push_back(pFrom);
#endif

	// Create priority queue.
	PriorityQueueHack nodeQueue;

	nodeDistancePair* pPair = new nodeDistancePair(std::make_pair(pFrom, calculateHValue(*pFrom, *pTo)));

	// Initialize the queue with the source at a distance of 0.
	nodeQueue.push(pPair);

	// Set the distance of all nodes to infinite.
	for (int currentNode = 0; currentNode < mpGraph->getSize(); currentNode++)
	{
		// Get the node with id(currentNode) from the graph.
		Node* pCurrentNode = mpGraph->getNode(currentNode);

		// Set the previous node of the current node to null.
		previousNode.insert(std::make_pair(pCurrentNode, nullptr));

		// Set all the visited nodes to false.
		visitedNodes.insert(std::make_pair(pCurrentNode, false));
	}

	Path path;

	Node* pCurrentNode = nullptr;

	nodeDistancePair* pCurrentNodeDistancePair;

	while (!nodeQueue.empty())
	{
		// Get lowest distance node from the front of the queue.
		pCurrentNodeDistancePair = nodeQueue.popTop();
		// Extract the node from the pair.
		pCurrentNode = pCurrentNodeDistancePair->first;

		// Found shortest path to target. No need to keep checking.
		if (pCurrentNode == pTo)
		{
			foundTargetNode = true;
			break;
		}

		// Checking node now.
		visitedNodes[pCurrentNode] = true;

		// Get the connections for the current node.
		std::vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		// Iterate through all the connections to calculate the distance to travel there. Update or add their values to the queue.
		for (unsigned int i = 0; i < connections.size(); i++)
		{
			// Get the current connection in the iteration.
			Connection* pConnection = connections[i];

			// Get the node attached to the connection.
			Node* pToNode = pConnection->getToNode();

			// Node has been visited. Go to the next connection.
			if (visitedNodes[pToNode])
			{
				continue;
			}

			// Cost to go to connected node from source.
			float cost = pCurrentNodeDistancePair->second + pConnection->getCost() + calculateHValue(*pCurrentNode, *pTo);

			// Add node to the queue or update existing node cost pair.
			if (nodeQueue.push(new nodeDistancePair(std::make_pair(pConnection->getToNode(), cost))))
			{
				// Update the path to the connected node.
				previousNode[pToNode] = pCurrentNode;
			}
		}
	}

	// Cannot reach target. Return empty path.
	if (!foundTargetNode)
	{
		return path;
	}

	std::vector<Node*>* pReversePath = new std::vector<Node*>();

	// Traverse the path backwards. (Target node is pCurrentNode on first iteration)
	while (pCurrentNode != nullptr)
	{
		// Add the current node to the reverse path.
		pReversePath->insert(pReversePath->begin(), pCurrentNode);

		// Get the previous node in the path.
		pCurrentNode = previousNode[pCurrentNode];
	}

	// Add the node to the path.
	path.setPath(pReversePath);

#ifdef VISUALIZE_PATH
	mVisitedNodes = *pReversePath;
#endif

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

#ifdef VISUALIZE_PATH
	mPath = path;
#endif
	return path;

}

float AStarPathfinder::calculateHValue(const Node& source, const Node& destination)
{
	// Calculate the difference in x and y to the destination.
	float differenceX = std::fabsf(source.getPositionX() - destination.getPositionX());
	float differenceY = std::fabsf(source.getPositionY() - destination.getPositionY());
	
	// Return the larger of the two values.
	return std::fmaxf(differenceX, differenceY);
}
