/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Node;

class Path:public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode( int index ) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode( Node* pNode );
	unsigned int getNumNodes() const { return mNodes.size(); };

	void addNode( Node* pNode );

	// Set path to given path.
	void setPath(std::vector<Node*>* pPath);

	void clear();

private:
	std::vector<Node*> mNodes;

};