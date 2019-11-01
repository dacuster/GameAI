/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 340 <Section 01>										**
**		Assignment: pa 4											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

class Node;

typedef std::pair<Node*, float> nodeDistancePair;

// Check that both nodes are the same.
inline bool operator==(const nodeDistancePair& left, const nodeDistancePair& right) { return (left.first == right.first); }

// Compare the second value of the pair.
inline bool operator< (const nodeDistancePair& left, const nodeDistancePair& right) { return  (left.second < right.second); }
inline bool operator> (const nodeDistancePair& left, const nodeDistancePair& right) { return  (right < left ); }
inline bool operator<=(const nodeDistancePair& left, const nodeDistancePair& right) { return !(left  > right); }
inline bool operator>=(const nodeDistancePair& left, const nodeDistancePair& right) { return !(left  < right); }

class CompareDistance
{
public:
	CompareDistance() {}
	bool operator()(const nodeDistancePair* left, const nodeDistancePair* right);
};

class PriorityQueueHack : public Trackable
{
public:
	// Constructor.
	PriorityQueueHack() { }

	// Destructor.
	~PriorityQueueHack() { clear(); }

	// Push element to the queue. True if value was updated or element is new. False if value is the same.
	bool push(nodeDistancePair* element);
	
	// Remove the first element in the queue.
	void pop();

	// Get the first element in the queue.
	nodeDistancePair* top();

	// Get the first element in the queue and remove it.
	nodeDistancePair* popTop();

	// Clear the queue.
	void clear();

	// Check whether the queue is empty.
	bool empty() { return mQueue.empty(); }

private:
	// Priority queue of node distance pairs.
	std::priority_queue<nodeDistancePair*, std::vector<nodeDistancePair*>, CompareDistance> mQueue;

	// Map to find nodes quickly to adjust their values.
	std::map<Node*, nodeDistancePair*> mMap;
};