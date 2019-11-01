/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Graph;
class Path;
class Node;

#define VISUALIZE_PATH 1

class Pathfinder:public Trackable
{
public:
	Pathfinder( Graph* pGraph );
	virtual ~Pathfinder();

	virtual Path findPath( Node* pFrom, Node* pTo ) = 0;

protected:
	Graph* mpGraph;
	
};