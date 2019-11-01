/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once



class Path;
class Graph;

class DepthFirstPathfinder:public GridPathfinder
{
public:
	DepthFirstPathfinder( Graph* pGraph );
	~DepthFirstPathfinder();

	Path findPath( Node* pFrom, Node* pTo );//make sure to delete the path when you are done!

private:
};

