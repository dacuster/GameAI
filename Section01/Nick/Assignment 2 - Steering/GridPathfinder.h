/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
//class PathfindingDebugContent;
class Grid;

enum PathfindingType
{
	INVALID = -1,
	DEPTH_FIRST_SEARCH,
	DIJKSTRA,
	A_STAR
};

class GridPathfinder : public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual Path findPath( Node* pFrom, Node* pTo ) = 0;

	PathfindingType getType() const { return mType; }
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
protected:
	std::vector<Node*> mVisitedNodes;
	Path mPath;
	GridVisualizer* mpVisualizer;
#endif

	PathfindingType mType = DEPTH_FIRST_SEARCH;

	double mTimeElapsed;
};