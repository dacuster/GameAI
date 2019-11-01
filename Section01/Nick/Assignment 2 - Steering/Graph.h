/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Connection;

class Graph : public Trackable
{
public:
	Graph();
	virtual ~Graph();

	virtual void init();
	std::vector<Connection*> getConnections( const Node& from );
	std::vector<Connection*> getConnections( const NODE_ID& fromId );
	Node* getNode( int index );
	int getSize() { return mNodes.size(); }

protected:
	//a vector of Node pointers
	std::vector<Node*> mNodes;
	//a vector of Connection pointers
	std::vector<Connection*> mConnections;
	//a map of Connection&'s vectors indexed on Node id
	std::map< NODE_ID, std::vector<Connection*> > mConnectionMap;
};